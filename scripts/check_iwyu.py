#!/usr/bin/env python3
"""Check source codes with include-what-you-use.
"""

import asyncio
import pathlib
import random
import typing
import multiprocessing

import click
import tqdm

CLANG_INCLUDE_OPTION = [
    "-isystem",
    "/usr/lib/llvm-19/include/c++/v1/",
]

ROOT_DIR = pathlib.Path(__file__).absolute().parent.parent
IWYU_MAPPING_PATH = ROOT_DIR / "iwyu_mappings.imp"

IS_SUCCESS = True


class IwyuProcessError(RuntimeError):
    pass


def remove_correct_lines(target: str) -> str:
    result = ""
    prev_line_removed = False
    for line in target.splitlines():
        remove_this_line = False
        if "has correct #includes/fwd-decls)" in line:
            remove_this_line = True
        if prev_line_removed and line == "":
            remove_this_line = True

        if remove_this_line:
            prev_line_removed = True
        else:
            prev_line_removed = False
            result = result + line + "\n"

    return result


async def apply_iwyu_to_file(
    filepath: str,
    build_dir: str,
    tqdm_obj: tqdm.tqdm,
    limiter: asyncio.Semaphore,
    stop_on_error: bool,
):
    global IS_SUCCESS

    async with limiter:
        command = (
            ["iwyu_tool.py", "-p", ".", filepath, "--"]
            + CLANG_INCLUDE_OPTION
            + ["-Xiwyu", "--error"]
            + ["-Xiwyu", f"--mapping_file={str(IWYU_MAPPING_PATH)}"]
            + ["-Xiwyu", "--no_fwd_decls"]
            + ["-Xiwyu", "--check_also=**/stat_bench/**/*.h"]
        )
        process = await asyncio.create_subprocess_exec(
            *command,
            stdout=asyncio.subprocess.PIPE,
            stderr=asyncio.subprocess.PIPE,
            cwd=build_dir,
        )
        try:
            stdout, stderr = await process.communicate()
        except:
            process.kill()
            await process.communicate()
            raise

        if process.returncode == 0:
            tqdm_obj.write(click.style(f"> {filepath}: OK", fg="green"))
            tqdm_obj.update()
        else:
            console = stdout.decode("utf8") + "\n" + stderr.decode("utf8")
            console = remove_correct_lines(console)
            tqdm_obj.write(click.style(f"> {filepath}: NG", fg="red") + "\n" + console)
            IS_SUCCESS = False
            if stop_on_error:
                raise IwyuProcessError(f"Error in {filepath}.")
            tqdm_obj.update()


def filter_iwyu_process_error(exc):
    if isinstance(exc, IwyuProcessError):
        return None
    else:
        return exc


async def apply_iwyu_to_files(
    filepaths: list[str],
    build_dir: str,
    num_jobs: int,
    stop_on_error: bool,
):
    global IS_SUCCESS

    tqdm_obj = tqdm.tqdm(total=len(filepaths), unit="file")
    limiter = asyncio.Semaphore(num_jobs)
    tasks: typing.List[asyncio.Task] = []
    try:
        for filepath in filepaths:
            tasks.append(
                asyncio.create_task(
                    apply_iwyu_to_file(
                        filepath=filepath,
                        build_dir=build_dir,
                        tqdm_obj=tqdm_obj,
                        limiter=limiter,
                        stop_on_error=stop_on_error,
                    )
                )
            )
        await asyncio.gather(*tasks)
    except IwyuProcessError:
        IS_SUCCESS = False
        for task in tasks:
            task.cancel()
    finally:
        tqdm_obj.close()


def get_files_in(path: pathlib.Path) -> list[str]:
    filepaths: list[str] = []
    for child in path.iterdir():
        if child.is_file():
            filepaths.append(str(child))
        elif child.is_dir():
            filepaths = filepaths + get_files_in(child)

    return filepaths


@click.command()
@click.option("--build_dir", "-b", required=True, help="Build directory.")
@click.option("--num_jobs", "-j", default=1, help="Number of concurrent jobs.")
@click.argument("file_or_directory_paths", nargs=-1)
def check_iwyu(file_or_directory_paths: list[str], build_dir: str, num_jobs: int):
    """Check source codes with include-what-you-use."""

    global IS_SUCCESS

    filepaths: list[str] = []
    for file_or_directory_path in file_or_directory_paths:
        path = pathlib.Path(file_or_directory_path).absolute()
        if path.is_file():
            filepaths.append(str(path))
        elif path.is_dir():
            filepaths = filepaths + get_files_in(path)

    filepaths = [
        filepath
        for filepath in filepaths
        if filepath.endswith(".cpp") and not filepath.endswith("unity_source.cpp")
    ]

    # Check different files first.
    random.seed()
    random.shuffle(filepaths)

    # Currently, stop on error always.
    stop_on_error = True

    asyncio.run(apply_iwyu_to_files(filepaths, build_dir, num_jobs, stop_on_error))

    if not IS_SUCCESS:
        click.echo(click.style("Some errors occurred.", fg="red"))
        subprocesses = multiprocessing.active_children()
        for subprocess in subprocesses:
            subprocess.kill()


if __name__ == "__main__":
    check_iwyu()

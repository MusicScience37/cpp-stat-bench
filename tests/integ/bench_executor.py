"""Function to execute benchmarks."""

import pathlib
import shutil
import subprocess
import typing

import approvaltests
import approvaltests.approvals
import approvaltests.scrubbers
import pytest

from .scrubbers import scrub_console


class BenchExecutor:
    def __init__(
        self,
        request: pytest.FixtureRequest,
        temp_test_dir: pathlib.Path,
    ) -> None:
        self._test_name = request.node.nodeid.split("::", 1)[1].replace("::", ".")
        self._temp_test_dir = temp_test_dir

    @property
    def test_name(self) -> str:
        return self._test_name

    @property
    def temp_test_dir(self) -> pathlib.Path:
        return self._temp_test_dir

    def execute(
        self,
        bench_bin_path: pathlib.Path,
        *additional_args: str,
        samples: typing.Optional[int] = 3,
        mean_samples: typing.Optional[int] = 2,
        min_sample_duration: float = 0.001,
        min_warming_up_iterations: int = 1,
        min_warming_up_duration_sec: float = 0.001,
        cwd: typing.Optional[str] = None,
        verify: bool = True,
    ) -> subprocess.CompletedProcess[str]:
        args: typing.List[str] = []
        if samples is not None:
            args = args + ["--samples", str(samples)]
        if mean_samples is not None:
            args = args + ["--mean_samples", str(mean_samples)]
        if min_sample_duration is not None:
            args = args + ["--min_sample_duration", str(min_sample_duration)]
        if min_warming_up_iterations is not None:
            args = args + [
                "--min_warming_up_iterations",
                str(min_warming_up_iterations),
            ]
        if min_warming_up_duration_sec is not None:
            args = args + [
                "--min_warming_up_duration_sec",
                str(min_warming_up_duration_sec),
            ]
        args = args + list(additional_args)

        command = [str(bench_bin_path)] + args

        if not cwd:
            cwd = self._temp_test_dir

        result = subprocess.run(
            command,
            check=False,
            cwd=cwd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            encoding="utf8",
        )

        if verify:
            approvaltests.verify(
                f"""exit_code:
{result.returncode}
stdout:
{result.stdout}
stderr:
{result.stderr}
""",
                options=approvaltests.Options().with_scrubber(scrub_console),
            )

        return result

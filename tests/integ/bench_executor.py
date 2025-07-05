"""Function to execute benchmarks."""

import pathlib
import subprocess
import typing

import approvaltests
import approvaltests.approvals
import approvaltests.scrubbers
import pytest

from .scrubbers import scrub_console


class BenchExecutor:
    """Class to execute benchmarks.

    Args:
        request (pytest.FixtureRequest): An instance of pytest.FixtureRequest.
        temp_test_dir (pathlib.Path): The temporary directory for tests.
    """

    def __init__(
        self,
        request: pytest.FixtureRequest,
        temp_test_dir: pathlib.Path,
    ) -> None:
        self._test_name = request.node.nodeid.split("::", 1)[1].replace("::", ".")
        self._temp_test_dir = temp_test_dir

    @property
    def test_name(self) -> str:
        """Get the test name."""
        return self._test_name

    @property
    def temp_test_dir(self) -> pathlib.Path:
        """Get the temporary directory for tests."""
        return self._temp_test_dir

    def execute(
        self,
        bench_bin_path: pathlib.Path,
        *additional_args: str,
        samples: typing.Optional[int] = 3,
        min_sample_duration: float = 0.001,
        min_warming_up_iterations: int = 1,
        min_warming_up_duration_sec: float = 0.001,
        cwd: typing.Optional[str] = None,
        verify: bool = True,
    ) -> subprocess.CompletedProcess[str]:
        """Execute a benchmark.

        Args:
            bench_bin_path (pathlib.Path): The path to the binary of the benchmark.
            additional_args (str): Additional arguments to pass to the benchmark.
            samples (typing.Optional[int], optional): The number of samples.
                Defaults to 3.
            min_sample_duration (float, optional): The minimum duration of a sample.
                Defaults to 0.001.
            min_warming_up_iterations (int, optional): The minimum number of iterations
                for warming up. Defaults to 1.
            min_warming_up_duration_sec (float, optional): The minimum duration of
                warming up. Defaults to 0.001.
            cwd (typing.Optional[str], optional): Current working directory.
                Defaults to None.
            verify (bool, optional): Verify outputs using ApprovalTests.
                Defaults to True.

        Returns:
            subprocess.CompletedProcess[str]: The result of execution.
        """
        args: typing.List[str] = []
        if samples is not None:
            args = args + ["--samples", str(samples)]
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
            cwd = str(self._temp_test_dir)

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

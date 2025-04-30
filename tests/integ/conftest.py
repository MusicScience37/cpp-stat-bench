"""Configuration of pytest."""

import pathlib

import approvaltests
import approvaltests.reporters
import pytest
from approvaltests.reporters.reporter_that_automatically_approves import (
    ReporterThatAutomaticallyApproves,
)

from .bench_executor import BenchExecutor


def pytest_addoption(parser: pytest.Parser) -> None:
    """Add options to pytest."""
    parser.addoption(
        "--build", action="store", required=True, help="Build directory of CMake."
    )


@pytest.fixture(scope="session", autouse=True)
def configure_approvaltests():
    """Configure approvaltests library."""
    approvaltests.set_default_reporter(ReporterThatAutomaticallyApproves())


@pytest.fixture
def build_dir(pytestconfig: pytest.Config) -> pathlib.Path:
    """Get the build directory."""
    return pathlib.Path(str(pytestconfig.getoption("build"))).absolute()


@pytest.fixture
def temp_test_dir(build_dir: pathlib.Path) -> pathlib.Path:
    """Get the temporary directory for tests."""
    return build_dir / "temp_test"


@pytest.fixture
def bench_executor(
    request: pytest.FixtureRequest, temp_test_dir: pathlib.Path
) -> BenchExecutor:
    """Get the executor of benchmarks."""
    return BenchExecutor(request=request, temp_test_dir=temp_test_dir)


@pytest.fixture
def bin_dir(build_dir: pathlib.Path) -> pathlib.Path:
    """Get the bin directory."""
    return build_dir / "bin"


@pytest.fixture
def simple_benchmark(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_simple_benchmark."""
    return bin_dir / "stat_bench_test_integ_simple_benchmark"


@pytest.fixture
def groups_and_cases(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_groups_and_cases."""
    return bin_dir / "stat_bench_test_integ_groups_and_cases"


@pytest.fixture
def error_in_benchmark(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_error_in_benchmark."""
    return bin_dir / "stat_bench_test_integ_error_in_benchmark"


@pytest.fixture
def parametrized_benchmark(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_parametrized_benchmark."""
    return bin_dir / "stat_bench_test_integ_parametrized_benchmark"


@pytest.fixture
def duplicate_cases(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_duplicate_cases."""
    return bin_dir / "stat_bench_test_integ_duplicate_cases"


@pytest.fixture
def escaped_names(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_escaped_names."""
    return bin_dir / "stat_bench_test_integ_escaped_names"


@pytest.fixture
def subplots(bin_dir: pathlib.Path) -> pathlib.Path:
    """Get the path of executable stat_bench_test_integ_subplots."""
    return bin_dir / "stat_bench_test_integ_subplots"

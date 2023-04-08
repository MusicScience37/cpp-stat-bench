"""Configuration of pytest."""

import pathlib

import approvaltests
import approvaltests.reporters
from approvaltests.reporters.reporter_that_automatically_approves import (
    ReporterThatAutomaticallyApproves,
)
import pytest

from .bench_executor import BenchExecutor


def pytest_addoption(parser: pytest.Parser) -> None:
    parser.addoption(
        "--build", action="store", required=True, help="Build directory of CMake."
    )


@pytest.fixture(scope="session", autouse=True)
def configure_approvaltests():
    """Configure approvaltests library."""

    approvaltests.set_default_reporter(ReporterThatAutomaticallyApproves())


@pytest.fixture
def build_dir(pytestconfig: pytest.Config) -> pathlib.Path:
    return pathlib.Path(str(pytestconfig.getoption("build"))).absolute()


@pytest.fixture
def temp_test_dir(build_dir: pathlib.Path) -> pathlib.Path:
    return build_dir / "temp_test"


@pytest.fixture
def bench_executor(
    request: pytest.FixtureRequest, temp_test_dir: pathlib.Path
) -> BenchExecutor:
    return BenchExecutor(request=request, temp_test_dir=temp_test_dir)


@pytest.fixture
def bin_dir(build_dir: pathlib.Path) -> pathlib.Path:
    return build_dir / "bin"


@pytest.fixture
def groups_and_cases(bin_dir: pathlib.Path) -> pathlib.Path:
    return bin_dir / "stat_bench_test_integ_groups_and_cases"

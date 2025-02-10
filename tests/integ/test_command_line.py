"""Test of command line options not checked in other tests."""

import pathlib

from .bench_executor import BenchExecutor


class TestCommandLine:
    """Test of command line options not checked in other tests."""

    def test_help(
        self, bench_executor: BenchExecutor, simple_benchmark: pathlib.Path
    ) -> None:
        """Test of help option."""
        bench_executor.execute(simple_benchmark, "--help")

    def test_short_help(
        self, bench_executor: BenchExecutor, simple_benchmark: pathlib.Path
    ) -> None:
        """Test of short help option."""
        bench_executor.execute(simple_benchmark, "-h")

    def test_invalid_option(
        self, bench_executor: BenchExecutor, simple_benchmark: pathlib.Path
    ) -> None:
        """Test of an invalid option."""
        bench_executor.execute(simple_benchmark, "--any")

"""Test of errors in benchmarks."""

import pathlib

from .bench_executor import BenchExecutor


class TestErrorsInBenchmarks:
    """Test of errors in benchmarks."""

    def test_error_in_benchmark(
        self, bench_executor: BenchExecutor, error_in_benchmark: pathlib.Path
    ) -> None:
        """Test of an error in a benchmark."""
        bench_executor.execute(error_in_benchmark)

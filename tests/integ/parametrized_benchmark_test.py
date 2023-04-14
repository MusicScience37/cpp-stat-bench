"""Test of parametrized benchmarks."""

import pathlib

from .bench_executor import BenchExecutor


class TestParametrizedBenchmarks:
    """Test of parametrized benchmarks."""

    def test_parametrized_benchmark(
        self, bench_executor: BenchExecutor, parametrized_benchmark: pathlib.Path
    ) -> None:
        """Test of a parametrized benchmark."""
        result = bench_executor.execute(parametrized_benchmark, verify=True)

        assert result.returncode == 0

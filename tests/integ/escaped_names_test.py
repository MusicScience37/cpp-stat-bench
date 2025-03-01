"""Test of names which must be escaped."""

import pathlib

from .bench_executor import BenchExecutor


class TestEscapedNames:
    """Test of names which must be escaped."""

    def test_escaped_names(
        self, bench_executor: BenchExecutor, escaped_names: pathlib.Path
    ):
        """Test of names which must be escaped."""
        result = bench_executor.execute(
            escaped_names, "--plot", bench_executor.test_name, verify=False
        )

        assert result.returncode == 0
        plot_dir = bench_executor.temp_test_dir / bench_executor.test_name
        assert plot_dir.exists()
        expected_group_name = (
            r"Group%20for%20Test%20%3C1%3E%20%E3%83%86%E3%82%B9%E3%83%88"
        )
        assert (plot_dir / expected_group_name).exists()

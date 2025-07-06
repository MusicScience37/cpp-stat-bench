"""Test of custom measurement."""

import pathlib

from .bench_executor import BenchExecutor


class TestCustomMeasurement:
    """Test of custom measurement."""

    def test_custom_measurement(
        self, bench_executor: BenchExecutor, custom_measurement: pathlib.Path
    ):
        """Test of custom measurement."""
        result = bench_executor.execute(custom_measurement)

        assert result.returncode == 0

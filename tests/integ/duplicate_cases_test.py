"""Test of duplicate cases."""

import pathlib

from .bench_executor import BenchExecutor


class TestDuplicateCases:
    """Test of duplicate cases."""

    def test_duplicate_cases(
        self, bench_executor: BenchExecutor, duplicate_cases: pathlib.Path
    ) -> None:
        """Test of duplicate cases."""
        bench_executor.execute(duplicate_cases)

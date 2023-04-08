"""Test of groups and cases."""

import pathlib

from .bench_executor import BenchExecutor


class TestGroupsAndCases:
    """Test of groups and cases."""

    def test_execute_all(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to execute all benchmarks."""
        bench_executor.execute(groups_and_cases)

    def test_include(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to include some benchmarks using glob."""
        bench_executor.execute(groups_and_cases, "--include", "Group1/*")

    def test_exclude(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to exclude some benchmarks using glob."""
        bench_executor.execute(groups_and_cases, "--exclude", "Group1/*")

    def test_include_and_exclude(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to include and exclude some benchmarks using glob."""
        bench_executor.execute(
            groups_and_cases, "--include", "Group1/*", "--exclude", "*/Case2"
        )

    def test_include_regex(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to include some benchmarks using regex."""
        bench_executor.execute(groups_and_cases, "--include_regex", "Group1/.*")

    def test_exclude_regex(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to exclude some benchmarks using regex."""
        bench_executor.execute(groups_and_cases, "--exclude_regex", "Group1/.*")

    def test_include_and_exclude_regex(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to include and exclude some benchmarks using regex."""
        bench_executor.execute(
            groups_and_cases,
            "--include_regex",
            "Group1/.*",
            "--exclude_regex",
            ".*/Case2",
        )

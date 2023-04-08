"""Test of reporters."""


import pathlib
from .bench_executor import BenchExecutor


class TestPlot:
    """Test of plotting."""

    def test_plot(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test to plot."""
        result = bench_executor.execute(
            groups_and_cases, "--plot", bench_executor.test_name, verify=False
        )

        assert result.returncode == 0
        plot_dir = bench_executor.temp_test_dir / bench_executor.test_name
        assert plot_dir.exists()
        assert (plot_dir / "Group1").exists()
        assert (plot_dir / "Group1" / "ProcessingTime.html").exists()
        assert (plot_dir / "Group1" / "ProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group1" / "ProcessingTime_violin.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime_violin.html").exists()
        assert (plot_dir / "Group2").exists()
        assert (plot_dir / "Group2" / "ProcessingTime.html").exists()
        assert (plot_dir / "Group2" / "ProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group2" / "ProcessingTime_violin.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime_violin.html").exists()


class TestJson:
    """Test of JSON output."""

    def test_json(
        self, bench_executor: BenchExecutor, groups_and_cases: pathlib.Path
    ) -> None:
        """Test of JSON output."""
        result = bench_executor.execute(
            groups_and_cases, "--json", f"{bench_executor.test_name}.json", verify=False
        )

        assert result.returncode == 0
        assert (
            bench_executor.temp_test_dir / f"{bench_executor.test_name}.json"
        ).exists()
        # TODO: Test of data structure.

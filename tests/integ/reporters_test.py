"""Test of reporters."""

import gzip
import json
import pathlib
import typing

import fastjsonschema
import msgpack
import pytest

from .bench_executor import BenchExecutor

THIS_DIR = pathlib.Path(__file__).absolute().parent
SCHEMAS_DIR = THIS_DIR.parent.parent / "schemas"
CURRENT_SCHEMA_FILE = SCHEMAS_DIR / "data_file_schema_v3.json"


@pytest.fixture
def data_file_schema_validate():
    """Function to validate data file schema."""
    with open(str(CURRENT_SCHEMA_FILE), mode="r", encoding="utf-8") as file:
        data = json.load(file)
    return fastjsonschema.compile(data)


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
        assert (plot_dir / "Group1" / "ProcessingTime_samples.html").exists()
        assert (plot_dir / "Group1" / "ProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group1" / "ProcessingTime_violin.html").exists()
        assert (plot_dir / "Group1" / "ProcessingTime_box.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime_samples.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime_violin.html").exists()
        assert (plot_dir / "Group1" / "MeanProcessingTime_box.html").exists()
        assert (plot_dir / "Group2").exists()
        assert (plot_dir / "Group2" / "ProcessingTime_samples.html").exists()
        assert (plot_dir / "Group2" / "ProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group2" / "ProcessingTime_violin.html").exists()
        assert (plot_dir / "Group2" / "ProcessingTime_box.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime_samples.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime_cdf.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime_violin.html").exists()
        assert (plot_dir / "Group2" / "MeanProcessingTime_box.html").exists()

    def test_plot_with_parameter(
        self, bench_executor: BenchExecutor, parametrized_benchmark: pathlib.Path
    ) -> None:
        """Test to plot with parameter."""
        result = bench_executor.execute(
            parametrized_benchmark, "--plot", bench_executor.test_name, verify=False
        )

        assert result.returncode == 0
        plot_dir = bench_executor.temp_test_dir / bench_executor.test_name
        assert plot_dir.exists()
        assert (plot_dir / "FibonacciParametrized").exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_samples.html"
        ).exists()
        assert (plot_dir / "FibonacciParametrized" / "ProcessingTime_cdf.html").exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_violin.html"
        ).exists()
        assert (plot_dir / "FibonacciParametrized" / "ProcessingTime_box.html").exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_by_number.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_by_number_violin.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_by_number_box.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_result_by_number.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "ProcessingTime_to_result_by_number.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_samples.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_cdf.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_violin.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_box.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_by_number.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "MeanProcessingTime_by_number_violin.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_by_number_box.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "MeanProcessingTime_result_by_number.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "MeanProcessingTime_to_result_by_number.html"
        ).exists()
        assert (plot_dir / "VectorPushBackParametrized").exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_samples.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_cdf.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_violin.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_box.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "ProcessingTime_throughput_stat_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "ProcessingTime_processed_numbers_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "ProcessingTime_to_throughput_stat_by_size.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_samples.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_cdf.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_violin.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_box.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "MeanProcessingTime_throughput_stat_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "MeanProcessingTime_processed_numbers_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "MeanProcessingTime_to_throughput_stat_by_size.html"
        ).exists()

    def test_plot_with_large_samples(
        self, bench_executor: BenchExecutor, parametrized_benchmark: pathlib.Path
    ) -> None:
        """Test to plot with parameter."""
        result = bench_executor.execute(
            parametrized_benchmark,
            "--plot",
            bench_executor.test_name,
            samples=10000,
            verify=False,
        )

        assert result.returncode == 0
        plot_dir = bench_executor.temp_test_dir / bench_executor.test_name
        assert plot_dir.exists()
        assert (plot_dir / "FibonacciParametrized").exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_samples.html"
        ).exists()
        assert (plot_dir / "FibonacciParametrized" / "ProcessingTime_cdf.html").exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_violin.html"
        ).exists()
        assert (plot_dir / "FibonacciParametrized" / "ProcessingTime_box.html").exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_by_number.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_by_number_violin.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_by_number_box.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "ProcessingTime_result_by_number.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "ProcessingTime_to_result_by_number.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_samples.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_cdf.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_violin.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_box.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_by_number.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "MeanProcessingTime_by_number_violin.html"
        ).exists()
        assert (
            plot_dir / "FibonacciParametrized" / "MeanProcessingTime_by_number_box.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "MeanProcessingTime_result_by_number.html"
        ).exists()
        assert (
            plot_dir
            / "FibonacciParametrized"
            / "MeanProcessingTime_to_result_by_number.html"
        ).exists()
        assert (plot_dir / "VectorPushBackParametrized").exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_samples.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_cdf.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_violin.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_box.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "ProcessingTime_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "ProcessingTime_throughput_stat_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "ProcessingTime_processed_numbers_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "ProcessingTime_to_throughput_stat_by_size.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_samples.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_cdf.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_violin.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_box.html"
        ).exists()
        assert (
            plot_dir / "VectorPushBackParametrized" / "MeanProcessingTime_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "MeanProcessingTime_throughput_stat_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "MeanProcessingTime_processed_numbers_by_size.html"
        ).exists()
        assert (
            plot_dir
            / "VectorPushBackParametrized"
            / "MeanProcessingTime_to_throughput_stat_by_size.html"
        ).exists()

    def test_plot_with_subplots(
        self, bench_executor: BenchExecutor, subplots: pathlib.Path
    ) -> None:
        """Test to plot with subplots."""
        result = bench_executor.execute(
            subplots, "--plot", bench_executor.test_name, verify=False
        )

        assert result.returncode == 0
        plot_dir = bench_executor.temp_test_dir / bench_executor.test_name
        assert plot_dir.exists()
        assert (plot_dir / "BinomialSeries").exists()
        assert (
            plot_dir / "BinomialSeries" / "ProcessingTime"
            "_by_Absolute%2520Value%2520of%2520x_box_by_Exponent_by_Sign.html"
        ).exists()
        assert (
            plot_dir / "BinomialSeries" / "MeanProcessingTime"
            "_by_Absolute%2520Value%2520of%2520x_box_by_Exponent_by_Sign.html"
        ).exists()
        assert (
            plot_dir / "BinomialSeries" / "ProcessingTime_Error%2520Rate"
            "_by_Absolute%2520Value%2520of%2520x_by_Exponent_by_Sign.html"
        ).exists()
        assert (
            plot_dir / "BinomialSeries" / "MeanProcessingTime_Error%2520Rate"
            "_by_Absolute%2520Value%2520of%2520x_by_Exponent_by_Sign.html"
        ).exists()


class TestJson:
    """Test of JSON output."""

    def test_json(
        self,
        bench_executor: BenchExecutor,
        parametrized_benchmark: pathlib.Path,
        data_file_schema_validate: typing.Callable,
    ) -> None:
        """Test of JSON output."""
        result = bench_executor.execute(
            parametrized_benchmark,
            "--json",
            f"{bench_executor.test_name}.json",
            verify=False,
        )

        assert result.returncode == 0
        data_path = bench_executor.temp_test_dir / f"{bench_executor.test_name}.json"
        assert data_path.exists()
        with open(data_path, mode="r", encoding="utf-8") as data_file:
            data = json.load(data_file)
        data_file_schema_validate(data)


class TestMsgPack:
    """Test of MsgPack output."""

    def test_msgpack(
        self,
        bench_executor: BenchExecutor,
        parametrized_benchmark: pathlib.Path,
        data_file_schema_validate: typing.Callable,
    ) -> None:
        """Test of MsgPack output."""
        result = bench_executor.execute(
            parametrized_benchmark,
            "--msgpack",
            f"{bench_executor.test_name}.data",
            verify=False,
        )
        assert result.returncode == 0
        data_path = bench_executor.temp_test_dir / f"{bench_executor.test_name}.data"
        assert data_path.exists()
        with open(data_path, mode="rb") as data_file:
            data = msgpack.unpack(data_file)
        data_file_schema_validate(data)


class TestCompressedMsgPack:
    """Test of compressed MsgPack output."""

    def test_compressed_msgpack(
        self,
        bench_executor: BenchExecutor,
        parametrized_benchmark: pathlib.Path,
        data_file_schema_validate: typing.Callable,
    ) -> None:
        """Test of compressed MsgPack output."""
        result = bench_executor.execute(
            parametrized_benchmark,
            "--compressed-msgpack",
            f"{bench_executor.test_name}.data.gz",
            verify=False,
        )
        assert result.returncode == 0
        data_path = bench_executor.temp_test_dir / f"{bench_executor.test_name}.data.gz"
        assert data_path.exists()
        with gzip.open(data_path, mode="rb") as data_file:
            data = msgpack.unpack(data_file)
        data_file_schema_validate(data)

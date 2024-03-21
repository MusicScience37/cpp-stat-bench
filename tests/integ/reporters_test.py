"""Test of reporters."""

import gzip
import json
import msgpack
import pathlib
import typing

import fastjsonschema
import pytest
from .bench_executor import BenchExecutor


THIS_DIR = pathlib.Path(__file__).absolute().parent
SCHEMAS_DIR = THIS_DIR.parent.parent / "schemas"
CURRENT_SCHEMA_FILE = SCHEMAS_DIR / "data_file_schema_v3.json"


@pytest.fixture
def data_file_schema_validate():
    with open(str(CURRENT_SCHEMA_FILE), mode="r") as file:
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
        with open(data_path, mode="r") as data_file:
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

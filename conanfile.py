from conans import ConanFile


class CppStatBenchConan(ConanFile):
    name = "cpp_stat_bench"
    version = "0.0.0"
    description = "Benchmark library with statistics for C++."
    homepage = "https://gitlab.com/MusicScience37/cpp-stat-bench"
    url = "https://gitlab.com/MusicScience37/cpp-stat-bench.git"
    license = "Apache-2.0"
    author = "Kenta Kabashima (kenta_program37@hotmail.co.jp)"
    topics = ("Benchmark")
    settings = None
    options = {
        "requirements_for_tests": [True, False],
    }
    default_options = {
        "requirements_for_tests": True,
    }
    exports_sources = "include/*"
    no_copy_source = True
    generators = "cmake", "cmake_find_package"

    def requirements(self):
        pass

    def build_requirements(self):
        if self.options.requirements_for_tests:
            self.build_requires(
                "catch2/3.0.0@MusicScience37+conan-extra-packages/stable")
            self.build_requires("trompeloeil/41")

    def package(self):
        self.copy("*.h")

    def package_info(self):
        self.info.header_only()

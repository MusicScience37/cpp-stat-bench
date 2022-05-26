from conans import ConanFile, CMake


class CppStatBenchConan(ConanFile):
    name = "cpp_stat_bench"
    version = "0.5.0"
    description = "Benchmark library with statistics for C++."
    homepage = "https://gitlab.com/MusicScience37/cpp-stat-bench"
    url = "https://gitlab.com/MusicScience37/cpp-stat-bench.git"
    license = "Apache-2.0"
    author = "Kenta Kabashima (kenta_program37@hotmail.co.jp)"
    topics = "Benchmark"
    settings = "os", "compiler", "build_type", "arch"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "requirements_for_tests": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "requirements_for_tests": False,
    }
    exports_sources = (
        "include/*",
        "src/*",
        "CMakeLists.txt",
        "CTestCustom.cmake",
        "cmake/*",
    )
    no_copy_source = True
    generators = "cmake", "cmake_find_package"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC
        if self.options.shared:
            raise ValueError("Shared library is not supported.")

    def requirements(self):
        self.requires("fmt/8.1.1")
        self.requires("lyra/1.6.0")
        self.requires("nlohmann_json/3.10.5")

    def build_requirements(self):
        if self.options.requirements_for_tests:
            self.build_requires(
                "catch2/3.0.1@MusicScience37+conan-extra-packages/stable"
            )
            self.build_requires("trompeloeil/42")
            self.build_requires("approvaltests.cpp/10.12.2")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include/stat_bench", src="include/stat_bench")
        self.copy("*stat_bench.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so*", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.components["stat_bench"].libs = ["stat_bench"]
        self.cpp_info.components["stat_bench"].requires = [
            "fmt::fmt",
            "lyra::lyra",
            "nlohmann_json::nlohmann_json",
        ]
        if self.settings.os in ["Linux", "FreeBSD"]:
            self.cpp_info.components["stat_bench"].system_libs = ["pthread"]

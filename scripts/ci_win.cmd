call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2022\\BuildTools\\VC\\Auxiliary\\Build\\vcvarsall.bat" x86_x64

cmake .. ^
    -G Ninja ^
    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache ^
    -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DSTAT_BENCH_TESTING:BOOL=ON ^
    -DSTAT_BENCH_ENABLE_BENCH=ON ^
    -DSTAT_BENCH_TEST_BENCHMARKS=ON ^
    -DSTAT_BENCH_BUILD_EXAMPLES=ON ^
    -DSTAT_BENCH_TEST_EXAMPLES=ON ^
    -DSTAT_BENCH_WRITE_JUNIT:BOOL=ON

cmake --build . --config Release --parallel

ctest -V --build-config Release

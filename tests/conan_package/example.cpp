// TODO: Write here.

#include <iostream>

#include "stat_bench/clock/system_clock.h"

auto main() -> int {
    std::cout << stat_bench::clock::SystemClock::now().to_string() << std::endl;
    return 0;
}

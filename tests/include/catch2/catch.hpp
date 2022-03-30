#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>

namespace Catch {

struct TestEventListenerBase : public EventListenerBase {
    using EventListenerBase::EventListenerBase;
};

}  // namespace Catch

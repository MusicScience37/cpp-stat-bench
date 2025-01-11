#include <memory>
#include <regex>
#include <string>
#include <string_view>

#include <fmt/format.h>

#define APPROVALS_CATCH
#include <ApprovalTests.hpp>

// NOLINTNEXTLINE: Usage of external library.
static const auto directory_config =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approvals");

// NOLINTNEXTLINE: Usage of external library.
static const auto default_options =
    ApprovalTests::Approvals::useAsDefaultReporter(
        // To automate tests, interactive reporters cannot be used.
        std::make_shared<ApprovalTests::AutoApproveReporter>());

class CustomNamer final : public ApprovalTests::ApprovalNamer {
public:
    // NOLINTNEXTLINE: Usage of external library.
    auto getApprovedFile(std::string extensionWithDot) const
        -> std::string override {
        return get_file(extensionWithDot, "approved");
    }

    // NOLINTNEXTLINE: Usage of external library.
    auto getReceivedFile(std::string extensionWithDot) const
        -> std::string override {
        return get_file(extensionWithDot, "received");
    }

private:
    [[nodiscard]] auto get_file(std::string_view extension_with_dot,
        std::string_view approval_or_received) const -> std::string {
        return fmt::format("{}/{}/{}.{}.{}", namer_.getTestSourceDirectory(),
            namer_.getApprovalsSubdirectory(),
            get_shorter_test_name(namer_.getTestName()), approval_or_received,
            extension_with_dot.substr(1));
    }

    static auto get_shorter_test_name(const std::string& origin)
        -> std::string {
        static std::regex target{R"(stat_bench__([^_]+__)*)"};
        static std::string format;
        return std::regex_replace(origin, target, format);
    }

    ApprovalTests::ApprovalTestNamer namer_;
};

// NOLINTNEXTLINE: Usage of external library.
static const auto default_namer_change =
    ApprovalTests::Approvals::useAsDefaultNamer(
        [] { return std::make_shared<CustomNamer>(); });

#include <memory>

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

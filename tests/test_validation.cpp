// test_validation.cpp
// Unit tests for the validation rules and for ReportValidator, including the proof of OCP.

#include "support/Fakes.hpp"
#include "validation/ReportValidator.hpp"
#include "validation/rules/DescriptionLengthRule.hpp"
#include "validation/rules/DescriptionRequiredRule.hpp"
#include "validation/rules/ServiceAreaRule.hpp"

#include <doctest/doctest.h>

#include <algorithm>
#include <cctype>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;
using namespace civicdesk;
using namespace civicdesk::testing;

namespace {

/// Runs a single rule against a draft.
ValidationResult check(const IValidationRule& rule, const ReportDraft& draft) {
    ValidationResult result;
    rule.check(draft, result);
    return result;
}

/// A rule that exists only in this test file. The validator was written long before it
/// and still runs it, which is the whole point of the Open/Closed Principle.
class NoShoutingRule final : public IValidationRule {
public:
    void check(const ReportDraft& draft, ValidationResult& result) const override {
        const bool hasLetters = ranges::any_of(draft.description, [](unsigned char c) { return isalpha(c) != 0; });
        const bool hasLowercase = ranges::any_of(draft.description, [](unsigned char c) { return islower(c) != 0; });
        if (hasLetters && !hasLowercase) {
            result.addError("Please don't write the description in capital letters only.");
        }
    }
};

}  // namespace

TEST_SUITE("validation rules") {
    TEST_CASE("ServiceAreaRule accepts a location inside the area and refuses one outside") {
        const ServiceAreaRule rule{kMoldova};

        CHECK(check(rule, potholeDraft(kChisinau)).ok());

        const ValidationResult outside = check(rule, potholeDraft(kBucharest));
        REQUIRE(outside.errors().size() == 1);
        CHECK(outside.errors().front() == "The location is outside the service area.");
    }

    TEST_CASE("DescriptionLengthRule accepts a description up to the limit and refuses a longer one") {
        const DescriptionLengthRule rule{10};
        ReportDraft draft = potholeDraft();

        draft.description = string(10, 'a');
        CHECK(check(rule, draft).ok());

        draft.description = string(11, 'a');
        const ValidationResult tooLong = check(rule, draft);
        REQUIRE(tooLong.errors().size() == 1);
        CHECK(tooLong.errors().front() == "The description can have at most 10 characters.");
    }

    TEST_CASE("DescriptionRequiredRule asks for a description only in its own category") {
        const DescriptionRequiredRule rule{Category::Other};

        SUBCASE("a blank description in that category is refused") {
            const ReportDraft draft{.category = Category::Other, .description = " \t\n", .location = kChisinau};

            const ValidationResult result = check(rule, draft);
            REQUIRE(result.errors().size() == 1);
            CHECK(result.errors().front() == "A report in the category \"Other\" needs a description.");
        }

        SUBCASE("a real description in that category is accepted") {
            const ReportDraft draft{.category = Category::Other, .description = "Broken bench", .location = kChisinau};

            CHECK(check(rule, draft).ok());
        }

        SUBCASE("other categories may leave the description empty") {
            const ReportDraft draft{.category = Category::Pothole, .description = "", .location = kChisinau};

            CHECK(check(rule, draft).ok());
        }
    }
}

TEST_SUITE("ReportValidator") {
    TEST_CASE("a validator without rules accepts every draft") {
        const ReportValidator validator;

        CHECK(validator.validate(potholeDraft(kBucharest)).ok());
    }

    TEST_CASE("a valid draft passes every rule") {
        ReportValidator validator;
        validator.addRule(make_unique<ServiceAreaRule>(kMoldova))
            .addRule(make_unique<DescriptionLengthRule>(1000));

        CHECK(validator.ruleCount() == 2);
        CHECK(validator.validate(potholeDraft()).ok());
    }

    TEST_CASE("every broken rule is reported, in the order the rules were added") {
        ReportValidator validator;
        validator.addRule(make_unique<ServiceAreaRule>(kMoldova))
            .addRule(make_unique<DescriptionLengthRule>(5));

        const ValidationResult result = validator.validate(potholeDraft(kBucharest));

        REQUIRE(result.errors().size() == 2);
        CHECK(result.errors()[0] == "The location is outside the service area.");
        CHECK(result.errors()[1] == "The description can have at most 5 characters.");
    }

    TEST_CASE("a rule the validator has never heard of plugs in without changing it (OCP)") {
        ReportValidator validator;
        validator.addRule(make_unique<ServiceAreaRule>(kMoldova)).addRule(make_unique<NoShoutingRule>());

        ReportDraft draft = potholeDraft();
        CHECK(validator.validate(draft).ok());

        draft.description = "FIX THIS NOW";
        const ValidationResult result = validator.validate(draft);
        REQUIRE(result.errors().size() == 1);
        CHECK(result.errors().front() == "Please don't write the description in capital letters only.");
    }

    TEST_CASE("a null rule is refused") {
        ReportValidator validator;

        CHECK_THROWS_AS(validator.addRule(nullptr), invalid_argument);
        CHECK(validator.ruleCount() == 0);
    }
}

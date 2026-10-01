#include "specification/Specifications.hpp"
#include "support/Fakes.hpp"

#include <doctest/doctest.h>

#include <memory>
#include <stdexcept>

using namespace civicdesk;
using namespace civicdesk::testing;

TEST_SUITE("specifications") {
    TEST_CASE("AnyReport matches every report") {
        CHECK(AnyReport{}.isSatisfiedBy(makeReport()));
    }

    TEST_CASE("HasCategory matches only its category") {
        const Report pothole = makeReport("R-0001", Category::Pothole);

        CHECK(HasCategory{Category::Pothole}.isSatisfiedBy(pothole));
        CHECK_FALSE(HasCategory{Category::Garbage}.isSatisfiedBy(pothole));
    }

    TEST_CASE("HasStatus matches only its status") {
        Report report = makeReport();
        report.transitionTo(Status::InProgress);

        CHECK(HasStatus{Status::InProgress}.isSatisfiedBy(report));
        CHECK_FALSE(HasStatus{Status::New}.isSatisfiedBy(report));
    }

    TEST_CASE("IsOpen matches a report until it is closed") {
        Report report = makeReport();
        CHECK(IsOpen{}.isSatisfiedBy(report));

        report.transitionTo(Status::InProgress);
        CHECK(IsOpen{}.isSatisfiedBy(report));

        report.transitionTo(Status::Resolved);
        CHECK_FALSE(IsOpen{}.isSatisfiedBy(report));
    }

    TEST_CASE("WithinRadius matches reports inside the circle") {
        // 0.0001 degrees of latitude is about 11 m.
        const GeoPoint elevenMetersNorth{.latitude = kChisinau.latitude + 0.0001, .longitude = kChisinau.longitude};
        const Report report = makeReport("R-0001", Category::Pothole, elevenMetersNorth);

        CHECK(WithinRadius{kChisinau, 25.0}.isSatisfiedBy(report));
        CHECK_FALSE(WithinRadius{kChisinau, 5.0}.isSatisfiedBy(report));
    }

    TEST_CASE("AllOf matches only when every part matches") {
        const Report openPothole = makeReport("R-0001", Category::Pothole);

        AllOf openPotholes;
        openPotholes.add(std::make_unique<HasCategory>(Category::Pothole)).add(std::make_unique<IsOpen>());
        CHECK(openPotholes.isSatisfiedBy(openPothole));

        AllOf openGarbage;
        openGarbage.add(std::make_unique<HasCategory>(Category::Garbage)).add(std::make_unique<IsOpen>());
        CHECK_FALSE(openGarbage.isSatisfiedBy(openPothole));
    }

    TEST_CASE("AllOf without parts matches everything") {
        CHECK(AllOf{}.isSatisfiedBy(makeReport()));
    }

    TEST_CASE("AllOf refuses a null part") {
        AllOf specification;

        CHECK_THROWS_AS(specification.add(nullptr), std::invalid_argument);
    }
}

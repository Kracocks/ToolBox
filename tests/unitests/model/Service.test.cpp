//
// Created by kracocks on 16/01/25.
//

#include <catch2/catch_all.hpp>

#include "Service.h"

TEST_CASE("Test the constructors of Service", "[service]") {
    const std::string serviceName = "service";
    const model::Service* service1{new model::Service{0, "test"}};
    const model::Service* service2{new model::Service{1, serviceName}};

    REQUIRE(service1 != nullptr);
    REQUIRE(service2 != nullptr);

	delete service1;
	delete service2;
}

TEST_CASE("Test the getter of Service", "[service]") {
    const model::Service service{0, "test"};

    REQUIRE(service.name == "test");
    REQUIRE(service.name != "test1");
}

TEST_CASE("Test the setters of Service", "[service]") {
    model::Service service{0, "test"};
    REQUIRE(service.name == "test");

    service.name = "test2";
    REQUIRE(service.name == "test2");
}

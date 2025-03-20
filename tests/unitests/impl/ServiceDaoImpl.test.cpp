//
// Created by kracocks on 17/02/25.
//

#include <catch2/catch_all.hpp>

#include "ServiceDaoImpl.h"
#include "impl/IdentifiantDaoImpl.h"

TEST_CASE("Test the DAO of ServiceDaoImpl", "[servicedaoimpl]") {
	impl::ServiceDaoImpl serviceDao {};

	std::vector all_before_insert {serviceDao.findAll()};

	model::Service service {0, "//service1"};
	serviceDao.insert(service);
	serviceDao.insert(model::Service {0, "//service2"});
	serviceDao.insert(model::Service {0, "/:service3"});

	std::vector all_after_insert {serviceDao.findAll()};

	CHECK(serviceDao.findByName("/").size() == 3);
	CHECK(serviceDao.findByName("//").size() == 2);
	CHECK(serviceDao.findByName("/:").size() == 1);

	CHECK((all_before_insert.size() + 3) == all_after_insert.size());

	CHECK((all_after_insert.size() - all_before_insert.size()) == 3);
	serviceDao.remove(all_after_insert[all_after_insert.size() - 1]);

	all_after_insert = serviceDao.findAll();
	CHECK((all_after_insert.size() - all_before_insert.size()) == 2);
	serviceDao.remove(all_after_insert[all_after_insert.size() - 1]);

	all_after_insert = serviceDao.findAll();
	CHECK((all_after_insert.size() - all_before_insert.size()) == 1);
	serviceDao.remove(all_after_insert[all_after_insert.size() - 1]);

	all_after_insert = serviceDao.findAll();
	CHECK((all_after_insert.size() - all_before_insert.size()) == 0);
}
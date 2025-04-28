//
// Created by kracocks on 17/02/25.
//

#include <catch2/catch_all.hpp>
#include "impl/IdentifiantDaoImpl.h"

TEST_CASE("Test the DAO of IdentifiantDaoImpl", "[identifiantdaoimpl]") {
	impl::IdentifiantDaoImpl identifiantDao {};

	std::vector all_before_insert {identifiantDao.findAll()};

	// {
	// 	model::Login login1 {0, "//test@test.com", "1234", false};
	// 	model::Login login2 {0, "//test@test.com", "1234", false};
	// 	model::Login login3 {0, "//test@test.com", "1234", false};
	// 	identifiantDao.insert(login1);
	// 	identifiantDao.insert(login2);
	// 	identifiantDao.insert(login3);
	// }

	std::vector all_after_insert {identifiantDao.findAll()};

	CHECK(identifiantDao.findByEmail("/").size() == 3);
	CHECK(identifiantDao.findByEmail("//").size() == 2);
	CHECK(identifiantDao.findByEmail("/:").size() == 1);

	CHECK((all_before_insert.size() + 3) == all_after_insert.size());

	CHECK((all_after_insert.size() - all_before_insert.size()) == 3);
	identifiantDao.remove(all_after_insert[all_after_insert.size() - 1]);

	all_after_insert = identifiantDao.findAll();
	CHECK((all_after_insert.size() - all_before_insert.size()) == 2);
	identifiantDao.remove(all_after_insert[all_after_insert.size() - 1]);

	all_after_insert = identifiantDao.findAll();
	CHECK((all_after_insert.size() - all_before_insert.size()) == 1);
	identifiantDao.remove(all_after_insert[all_after_insert.size() - 1]);

	all_after_insert = identifiantDao.findAll();
	CHECK((all_after_insert.size() - all_before_insert.size()) == 0);
}

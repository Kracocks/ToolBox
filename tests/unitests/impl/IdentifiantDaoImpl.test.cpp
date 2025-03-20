//
// Created by kracocks on 17/02/25.
//

#include <catch2/catch_all.hpp>
#include "impl/IdentifiantDaoImpl.h"

TEST_CASE("Test the DAO of IdentifiantDaoImpl", "[identifiantdaoimpl]") {
	impl::IdentifiantDaoImpl identifiantDao {};

	std::vector all_before_insert {identifiantDao.findAll()};

	model::Identifiant<> login {0, "//test@test.com", "1234", false};
	identifiantDao.insert(login);
	identifiantDao.insert(model::Identifiant<>
		{0, "//test@test.com", "1234", false});
	identifiantDao.insert(model::Identifiant<>
		{0, "/:truc@test.com", "1234", false});

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
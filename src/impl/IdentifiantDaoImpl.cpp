//
// Created by kracocks on 24/01/25.
//

#include "IdentifiantDaoImpl.h"
#include "../model/Login.h"
#include "../model/Service.h"
#include <iostream>
#include <ostream>

namespace impl {
	IdentifiantDaoImpl::IdentifiantDaoImpl(): m_connector(bd::Connector::getInstance("")) {}

	model::Login IdentifiantDaoImpl::find(const int& id) {
		model::Login ident {-1, -1, "", ""};
    	sqlite3 *bd = m_connector.getDB();
		const std::string sql {"SELECT * from LOGIN where login_id = ?;"};
    	sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get LOGIN with id" << id << sqlite3_errmsg(bd) << std::endl;
    		return ident;
    	}

    	sqlite3_bind_int(stmt, 1, id);
    	if (sqlite3_step(stmt) == SQLITE_ROW) {
			ident.id = sqlite3_column_int(stmt, 0);
			ident.email = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			ident.password = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			ident.service_id = sqlite3_column_int(stmt, 3);
    		sqlite3_finalize(stmt);
    		return ident;
    	}

    	sqlite3_finalize(stmt);
    	std::cerr << "No LOGIN with id" << id << std::endl;
    	return ident;
    }

	std::vector<model::Login> IdentifiantDaoImpl::findAll() {
		std::vector<model::Login> logins;
    	std::vector<model::Service> services;
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "SELECT login_id, email, password, service_id "
								"FROM LOGIN;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v3(bd, sql.c_str(), -1, SQLITE_PREPARE_PERSISTENT, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
			return logins;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
			model::Login login = model::Login(
            	sqlite3_column_int(stmt, 0),
				sqlite3_column_int(stmt, 3),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
			logins.push_back(login);
        }

        sqlite3_finalize(stmt);
		return logins;
    }

	std::vector<model::Login> IdentifiantDaoImpl::findByEmail(std::string &&email) {
		std::vector<model::Login> logins;
        sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT login_id, email, password, service_id "
								"FROM LOGIN "
								"where email LIKE ?;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all LOGIN by email : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
			return logins;
        }
    	sqlite3_bind_text(stmt, 1, (email + '%').c_str(), -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
			model::Login login = model::Login(
				sqlite3_column_int(stmt, 0),
				sqlite3_column_int(stmt, 3),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
			logins.push_back(login);
        }

        sqlite3_finalize(stmt);
		return logins;
    }

	std::vector<model::Login> IdentifiantDaoImpl::findByEmail(const std::string &email) {
		std::vector<model::Login> logins;
        sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT login_id, email, password, service_id "
								"FROM LOGIN "
								"where email LIKE ?;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all LOGIN by email : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
			return logins;
        }
    	sqlite3_bind_text(stmt, 1, (email + '%').c_str(), -1, SQLITE_TRANSIENT);

    	while (sqlite3_step(stmt) == SQLITE_ROW) {
			model::Login login = model::Login(
				sqlite3_column_int(stmt, 0),
				sqlite3_column_int(stmt, 3),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
			logins.push_back(login);
    	}

        sqlite3_finalize(stmt);
		return logins;
    }

	std::vector<model::Login> IdentifiantDaoImpl::findByService(const int &service_id) {
		std::vector<model::Login> logins;
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT login_id, email, password, service_id "
    							"FROM SERVICE natural join LOGIN "
    							"where service_id = ?";
    	sqlite3_stmt *stmt;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get all LOGIN by service with id " << service_id << " : \n" << sqlite3_errmsg(bd) << std::endl;
    		if (stmt) sqlite3_finalize(stmt);
			return logins;
    	}
    	sqlite3_bind_int(stmt, 1, service_id);

    	while (sqlite3_step(stmt) == SQLITE_ROW) {
			model::Login login = model::Login(
				sqlite3_column_int(stmt, 0),
				sqlite3_column_int(stmt, 3),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
			logins.push_back(login);
    	}
		return logins;
    }

	model::Login IdentifiantDaoImpl::insert(model::Login &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql_log = "INSERT INTO LOGIN(login_id, email, password, service_id) values (?, ?, ?, ?);";
        sqlite3_stmt *stmt_login = nullptr;

		item.id = -1;

        if (sqlite3_prepare_v2(bd, sql_log.c_str(), -1, &stmt_login, nullptr) != SQLITE_OK) {
        	std::cerr << "Error preparing statement to insert LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
			item.email = sqlite3_errmsg(bd);
        	if (stmt_login) sqlite3_finalize(stmt_login);
        	return item;
        }
		const int id = getLastId();
		sqlite3_bind_int(stmt_login, 1, id);
		sqlite3_bind_text(stmt_login, 2, item.email.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt_login, 3, item.password.c_str(), -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(stmt_login, 4, item.service_id);

    	if (sqlite3_step(stmt_login) != SQLITE_DONE) {
    		std::cerr << "Error insert LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt_login);
    		return item;
    	}

		item.id = id;
    	sqlite3_finalize(stmt_login);
    	std::cout << "inserted LOGIN" << std::endl;
    	return item;
    }

	model::Login IdentifiantDaoImpl::update(const int &id, const model::Login &newItem) {
		sqlite3 *bd = m_connector.getDB();
    	const std::string sql = {"UPDATE LOGIN SET email = ?, password = ? where login_id = ?;"};
    	sqlite3_stmt *stmt;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to update LOGIN\n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt);
			return {-1, -1, "", ""};
    	}
    	sqlite3_bind_int(stmt, 1, getLastId());
		sqlite3_bind_text(stmt, 2, newItem.password.c_str(), -1, SQLITE_TRANSIENT);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error updating LOGIN\n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt);
			return {-1, -1, "", ""};
    	}

    	sqlite3_finalize(stmt);
		return {-1, -1, "", ""};
    }

	void IdentifiantDaoImpl::remove(const model::Login &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "DELETE FROM LOGIN where login_id = ?";
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error preparing statement to delete LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
        	return;
        }
		sqlite3_bind_int(stmt, 1, item.id);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error delete LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt);
    		return;
    	}

    	std::cout << "removed LOGIN" << std::endl;
    	sqlite3_finalize(stmt);
    }

	int IdentifiantDaoImpl::getLastId() const {
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"select min(login_id)+1 from LOGIN "
								"where login_id+1 not in (select login_id from LOGIN) "
								"and exists (select 1 from LOGIN where login_id = 0);"};
    	sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get smallest id that doesn't exist" << std::endl;
    		sqlite3_finalize(stmt);
    		return -1;
    	}

    	if (sqlite3_step(stmt) == SQLITE_ROW) {
    		return sqlite3_column_int(stmt, 0);
    	}
    	sqlite3_finalize(stmt);
    	return 0;
    }
} // impl

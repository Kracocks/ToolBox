//
// Created by kracocks on 24/01/25.
//

#include "IdentifiantDaoImpl.h"
#include "../model/Service.h"
#include <iostream>
#include <ostream>

namespace impl {
    IdentifiantDaoImpl::IdentifiantDaoImpl(): m_connector(bd::Connector::getInstance()) {}

	model::Identifiant<> IdentifiantDaoImpl::find(const int& id) {
	    model::Identifiant<> ident {-1, "", "", false};
    	sqlite3 *bd = m_connector.getDB();
		const std::string sql {"SELECT * from LOGIN where login_id = ?;"};
    	sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get LOGIN with id" << id << sqlite3_errmsg(bd) << std::endl;
    		return ident;
    	}

    	sqlite3_bind_int(stmt, 1, id);
    	if (sqlite3_step(stmt) == SQLITE_ROW) {
    		ident.setID(sqlite3_column_int(stmt, 0));
    		ident.setEmail(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)));
    		ident.setPassword(reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)));
    		sqlite3_finalize(stmt);
    		return ident;
    	}

    	sqlite3_finalize(stmt);
    	std::cerr << "No LOGIN with id" << id << std::endl;
    	return ident;
    }

    std::vector<model::Identifiant<>> IdentifiantDaoImpl::findAll() {
        std::vector<model::Identifiant<>> identifiants;
    	std::vector<model::Service> services;
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "SELECT login_id, email, password "
								"FROM LOGIN;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v3(bd, sql.c_str(), -1, SQLITE_PREPARE_PERSISTENT, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
            return identifiants;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            model::Identifiant<> identifiant = model::Identifiant<>(
            	sqlite3_column_int(stmt, 0),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)),
            	false);
        	identifiants.push_back(identifiant);
        }

        sqlite3_finalize(stmt);
        return identifiants;
    }

    std::vector<model::Identifiant<>> IdentifiantDaoImpl::findByEmail(std::string &&email) {
        std::vector<model::Identifiant<>> identifiants;
        sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT login_id, email, password "
								"FROM LOGIN "
								"where email LIKE ?;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all LOGIN by email : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
            return identifiants;
        }
    	sqlite3_bind_text(stmt, 1, (email + '%').c_str(), -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            model::Identifiant<> identifiant = model::Identifiant<>(
				sqlite3_column_int(stmt, 0),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)),
            	false);
        	identifiants.push_back(identifiant);
        }

        sqlite3_finalize(stmt);
        return identifiants;
    }

    std::vector<model::Identifiant<>> IdentifiantDaoImpl::findByEmail(const std::string &email) {
        std::vector<model::Identifiant<>> identifiants;
        sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT login_id, email, password "
								"FROM LOGIN "
								"where email LIKE ?;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all LOGIN by email : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
            return identifiants;
        }
    	sqlite3_bind_text(stmt, 1, (email + '%').c_str(), -1, SQLITE_TRANSIENT);

    	while (sqlite3_step(stmt) == SQLITE_ROW) {
    		model::Identifiant<> identifiant = model::Identifiant<>(
				sqlite3_column_int(stmt, 0),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)),
				false);
    		identifiants.push_back(identifiant);
    	}

        sqlite3_finalize(stmt);
        return identifiants;
    }

	std::vector<model::Identifiant<>> IdentifiantDaoImpl::findByService(const int &service_id) {
	    std::vector<model::Identifiant<>> identifiants;
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT login_id, email, password "
    							"FROM SERVICE natural join LOGIN "
    							"where service_id = ?";
    	sqlite3_stmt *stmt;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get all LOGIN by service with id " << service_id << " : \n" << sqlite3_errmsg(bd) << std::endl;
    		if (stmt) sqlite3_finalize(stmt);
    		return identifiants;
    	}
    	sqlite3_bind_int(stmt, 1, service_id);

    	while (sqlite3_step(stmt) == SQLITE_ROW) {
			model::Identifiant<> identifiant = model::Identifiant<>(
				sqlite3_column_int(stmt, 0),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)),
				false);
    		identifiants.push_back(identifiant);
    	}
    	return identifiants;
    }

    model::Identifiant<> IdentifiantDaoImpl::insert(const int &service_id, model::Identifiant<> &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql_log = "INSERT INTO LOGIN(login_id, email, password, service_id) values (?, ?, ?, ?);";
        sqlite3_stmt *stmt_login = nullptr;

        if (sqlite3_prepare_v2(bd, sql_log.c_str(), -1, &stmt_login, nullptr) != SQLITE_OK) {
        	std::cerr << "Error preparing statement to insert LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt_login) sqlite3_finalize(stmt_login);
        	return item;
        }
    	sqlite3_bind_int(stmt_login, 1, getLastId());
    	sqlite3_bind_text(stmt_login, 2, item.getEmail().c_str(), -1, SQLITE_TRANSIENT);
    	sqlite3_bind_text(stmt_login, 3, item.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    	sqlite3_bind_int(stmt_login, 4, service_id);

    	if (sqlite3_step(stmt_login) != SQLITE_DONE) {
    		std::cerr << "Error insert LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt_login);
    		return item;
    	}

    	sqlite3_finalize(stmt_login);
    	std::cout << "inserted LOGIN" << std::endl;
    	return item;
    }

	model::Identifiant<> IdentifiantDaoImpl::update(const int &id, const model::Identifiant<> &newItem) {
		sqlite3 *bd = m_connector.getDB();
    	const std::string sql = {"UPDATE LOGIN SET email = ?, password = ? where login_id = ?;"};
    	sqlite3_stmt *stmt;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to update LOGIN\n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt);
    		return {-1, "", "", false};
    	}
    	sqlite3_bind_int(stmt, 1, getLastId());
    	sqlite3_bind_text(stmt, 2, newItem.getPassword().c_str(), -1, SQLITE_TRANSIENT);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error updating LOGIN\n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt);
    		return {-1, "", "", false};
    	}

    	sqlite3_finalize(stmt);
    	return {-1, "", "", false};
    }

	void IdentifiantDaoImpl::addService(const int &service_id, const model::Identifiant<> &item) {
	    sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"INSERT INTO USE(email, service_id) values(?, ?);"};
    	sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to insert USE : \n" << sqlite3_errmsg(bd) << std::endl;
    		if (stmt) sqlite3_finalize(stmt);
    		return;
    	}

    	sqlite3_bind_text(stmt, 1, item.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    	sqlite3_bind_int(stmt, 2, service_id);
    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error insert USE : \n" << sqlite3_errmsg(bd) << std::endl;
    		sqlite3_finalize(stmt);
    		return;
    	}

    	sqlite3_finalize(stmt);
    	std::cout << "added " << service_id << " to " << item.getId() << std::endl;
    }

    void IdentifiantDaoImpl::remove(const model::Identifiant<> &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "DELETE FROM LOGIN where login_id = ?";
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Error preparing statement to delete LOGIN : \n" << sqlite3_errmsg(bd) << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
        	return;
        }
    	sqlite3_bind_int(stmt, 1, item.getId());

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
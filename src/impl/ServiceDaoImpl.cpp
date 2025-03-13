//
// Created by kracocks on 25/01/25.
//

#include "ServiceDaoImpl.h"

#include <iostream>
#include <memory>

namespace impl {
    ServiceDaoImpl::ServiceDaoImpl(): m_connector(bd::Connector::getInstance()) {}

	model::Service ServiceDaoImpl::find(const int &id) {
    	model::Service service {};
    	service.id = -1;
    	sqlite3 *bd = m_connector.getDB();
		const std::string sql = "SELECT * FROM Service WHERE id = ?";
    	sqlite3_stmt *stmt;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get SERVICE with id" << id << "\n" << sqlite3_errmsg(bd) << "\n";
    		return service;
    	}

    	sqlite3_bind_int(stmt, 1, id);
    	if (sqlite3_step(stmt) == SQLITE_ROW) {
    		service.id = sqlite3_column_int(stmt, 0);
			service.name = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    		sqlite3_finalize(stmt);
    		return service;
    	}

    	sqlite3_finalize(stmt);
    	std::cerr << "No SERVICE with id" << id << "\n";
    	return service;
    }

    std::vector<model::Service> ServiceDaoImpl::findAll() {
        std::vector<model::Service> services {};
        sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT SERVICE.service_id, SERVICE.name, LOGIN.login_id, LOGIN.email, LOGIN.password "
								"FROM SERVICE LEFT JOIN USE LEFT JOIN LOGIN;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v3(bd, sql.c_str(), -1, SQLITE_PREPARE_PERSISTENT, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all SERVICE\n" << sqlite3_errmsg(bd) << "\n" << std::endl;
            return services;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
        	model::Service service;
        	service.id = -1;
        	const int service_id {sqlite3_column_int(stmt, 0)};
        	for (model::Service &serv : services) {
        		if (serv.id == service_id) {
        			service = serv;
        		}
        	}
        	if (service.id == -1) {
        		service = model::Service {
        			service_id,
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1))
				};
        		services.push_back(service);
        	}
			const unsigned char *email = sqlite3_column_text(stmt, 3);
        	const unsigned char *password = sqlite3_column_text(stmt, 4);
			if ((email || password)) {
        		model::Identifiant<> login {
        			sqlite3_column_int(stmt, 2),
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)),
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)),
					false
				};
				service.identifiants.push_back(login);
        	}
        }

        sqlite3_finalize(stmt);
        return services;
    }

	std::vector<model::Service> ServiceDaoImpl::findByName(std::string &&name) {
    	std::vector<model::Service> services;
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT SERVICE.service_id, SERVICE.name, LOGIN.login_id, LOGIN.email, LOGIN.password "
								"FROM SERVICE LEFT JOIN USE LEFT JOIN LOGIN "
								"where name LIKE ?;";
    	sqlite3_stmt *stmt;

    	int status = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
    	if (status != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get all SERVICE by email : \n" << sqlite3_errmsg(bd) << std::endl;
    		if (stmt) sqlite3_finalize(stmt);
    		return services;
    	}
    	sqlite3_bind_text(stmt, 1, (name + '%').c_str(), -1, SQLITE_TRANSIENT);

    	while (sqlite3_step(stmt) == SQLITE_ROW) {
    		model::Service service;
    		service.id = -1;
    		const int service_id {sqlite3_column_int(stmt, 0)};
    		for (model::Service &serv : services) {
    			if (serv.id == service_id) {
    				service = serv;
    			}
    		}
    		if (service.id == -1) {
    			service = model::Service {
    				service_id,
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1))
				};
    			services.push_back(service);
    		}
    		const unsigned char *email = sqlite3_column_text(stmt, 3);
    		const unsigned char *password = sqlite3_column_text(stmt, 4);
    		if ((email || password)) {
    			model::Identifiant<> login {
    				sqlite3_column_int(stmt, 2),
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)),
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)),
					false
				};
    			service.identifiants.push_back(login);
    		}
    	}

    	sqlite3_finalize(stmt);
    	return services;
    }

	std::vector<model::Service> ServiceDaoImpl::findByName(const std::string &name) {
    	std::vector<model::Service> services;
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "SELECT SERVICE.service_id, SERVICE.name, LOGIN.login_id, LOGIN.email, LOGIN.password "
								"FROM SERVICE LEFT JOIN USE LEFT JOIN LOGIN "
								"where name LIKE ?;";
    	sqlite3_stmt *stmt;

    	int status = sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr);
    	if (status != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get all SERVICE by email : \n" << sqlite3_errmsg(bd) << std::endl;
    		if (stmt) sqlite3_finalize(stmt);
    		return services;
    	}
    	sqlite3_bind_text(stmt, 1, (name + '%').c_str(), -1, SQLITE_TRANSIENT);

    	while (sqlite3_step(stmt) == SQLITE_ROW) {
    		model::Service service;
    		service.id = -1;
    		const int service_id {sqlite3_column_int(stmt, 0)};
    		for (model::Service &serv : services) {
    			if (serv.id == service_id) {
    				service = serv;
    			}
    		}
    		if (service.id == -1) {
    			service = model::Service {
    				service_id,
					reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1))
				};
    			services.push_back(service);
    		}
    		const unsigned char *email = sqlite3_column_text(stmt, 3);
    		const unsigned char *password = sqlite3_column_text(stmt, 4);
    		if ((email || password)) {
    			model::Identifiant<> login {
    				sqlite3_column_int(stmt, 2),
					reinterpret_cast<const char *>(email),
					reinterpret_cast<const char *>(password),
					false
				};
    			service.identifiants.push_back(login);
    		}
    	}

    	sqlite3_finalize(stmt);
    	return services;
	}

	void ServiceDaoImpl::addLogin(const int &service_id, const model::Identifiant<> &item) {
	    sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"INSERT INTO USE(login_id, email, service_id) values (?, ?, ?);"};
    	sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to insert LOGIN to SERVICE" << std::endl;
    		sqlite3_finalize(stmt);
    		return;
    	}
    	sqlite3_bind_int(stmt, 1, item.getId());
    	sqlite3_bind_text(stmt, 2, item.getEmail().c_str(), -1, SQLITE_TRANSIENT);
    	sqlite3_bind_int(stmt, 3, service_id);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error inserting LOGIN to SERVICE" << std::endl;
    		sqlite3_finalize(stmt);
    		return;
    	}

    	std::cout << "inserted LOGIN to SERVICE " << service_id << std::endl;
    	sqlite3_finalize(stmt);
    }

    model::Service ServiceDaoImpl::insert(model::Service &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "INSERT INTO SERVICE(service_id, name) values (?, ?);";
        sqlite3_stmt *stmt;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
			std::cerr << "Error preparing statement to insert SERVICE" << std::endl;
			sqlite3_finalize(stmt);
			return item;
		}
		const int id = getLastId();
    	sqlite3_bind_int(stmt, 1, id);
    	sqlite3_bind_text(stmt, 2, item.name.c_str(), -1, SQLITE_STATIC);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error inserting SERVICE" << std::endl;
    		sqlite3_finalize(stmt);
    		return item;
    	}

    	item.id = id;
    	std::cout << "inserted SERVICE" << std::endl;
    	sqlite3_finalize(stmt);
    	return item;
    }

	model::Service ServiceDaoImpl::update(const int& id, const model::Service& newItem) {
	    sqlite3 *bd = m_connector.getDB();
    	const std::string sql = "UPDATE SERVICE SET name = ? WHERE id = ?;";
    	sqlite3_stmt *stmt;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to update SERVICE" << std::endl;
    		sqlite3_finalize(stmt);
    		return {-1, ""};
    	}
    	sqlite3_bind_int(stmt, 1, id);
    	sqlite3_bind_text(stmt, 2, newItem.name.c_str(), -1, SQLITE_TRANSIENT);

		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cerr << "Error updating SERVICE" << sqlite3_errmsg(bd) << std::endl;
			if (stmt) sqlite3_finalize(stmt);
			return {-1, ""};
		}

    	sqlite3_finalize(stmt);
    	return newItem;
    }

    void ServiceDaoImpl::remove(const model::Service &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "DELETE FROM SERVICE where service_id = ?;";
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        	std::cerr << "Error preparing statement to remove SERVICE" << std::endl;
        	sqlite3_finalize(stmt);
        	return;
        }
    	sqlite3_bind_text(stmt, 1, std::to_string(item.id).c_str(), -1, SQLITE_STATIC);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error removing SERVICE" << std::endl;
    		sqlite3_finalize(stmt);
    		return;
    	}

    	std::cout << "removed SERVICE" << std::endl;
    	sqlite3_finalize(stmt);
    }

	int ServiceDaoImpl::getLastId() const {
	    sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"select min(service_id)+1 from SERVICE "
								"where service_id+1 not in (select service_id from SERVICE) "
								"and exists (select 1 from SERVICE where service_id = 0);"};
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
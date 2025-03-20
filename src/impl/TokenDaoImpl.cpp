//
// Created by kracocks on 25/01/25.
//

#include "TokenDaoImpl.h"

#include <iostream>

namespace impl {
    TokenDaoImpl::TokenDaoImpl(): m_connector(bd::Connector::getInstance()) {}

	model::Token TokenDaoImpl::find(const int &id) {
		model::Token token {-1, "", "Could not get token with id "+id, ""};
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"select token_id, value, description, expired_at from TOKEN where token_id = ?"};
		sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to get TOKEN with id " << id << "\n" << sqlite3_errmsg(bd) << std::endl;
    		return token;
    	}

    	sqlite3_bind_int(stmt, 1, id);
    	if (sqlite3_step(stmt) == SQLITE_ROW) {
    		token.id = sqlite3_column_int(stmt, 0);
    		token.value = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    		token.description = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    		token.expired_at = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
    		sqlite3_finalize(stmt);
    		return token;
    	}

    	sqlite3_finalize(stmt);
    	std::cerr << "No such TOKEN with id " << id << std::endl;
    	return token;
    }

    std::vector<model::Token> TokenDaoImpl::findAll() {
        std::vector<model::Token> tokens;
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "SELECT token_id, value, description, expired_at FROM TOKEN;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v3(bd, sql.c_str(), -1, SQLITE_PREPARE_PERSISTENT, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all TOKEN" << std::endl;
            return tokens;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            model::Token token{
            	sqlite3_column_int(stmt, 0),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)),
				reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3))};
            tokens.push_back(token);
        }

        sqlite3_finalize(stmt);

        return tokens;
    }

    model::Token TokenDaoImpl::insert(const int &login_id, model::Token &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "INSERT INTO TOKEN(token_id, login_id, value, description, expired_at) values (?, ?, ?, ?, ?);";
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        	std::cerr << "Error preparing statement to insert TOKEN" << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
        	return {-1, "", "could not insert token", ""};
        }
    	sqlite3_bind_int(stmt, 1, getLastId());
    	sqlite3_bind_int(stmt, 2, login_id);
    	sqlite3_bind_text(stmt, 3, item.value.c_str(), -1, SQLITE_STATIC);
    	sqlite3_bind_text(stmt, 3, item.description.c_str(), -1, SQLITE_STATIC);
    	sqlite3_bind_text(stmt, 3, item.expired_at.c_str(), -1, SQLITE_STATIC);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error inserting TOKEN" << std::endl;
    		sqlite3_finalize(stmt);
    		return {-1, "", "could not insert token", ""};
    	}

    	std::cout << "inserted TOKEN" << std::endl;
    	sqlite3_finalize(stmt);
    	return item;
    }

	model::Token TokenDaoImpl::update(const int &id, const model::Token &newItem) {
	    sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"update TOKEN set value = ?, description = ?, expired_at = ? where token_id = ?;"};
    	sqlite3_stmt *stmt = nullptr;

    	if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    		std::cerr << "Error preparing statement to update TOKEN" << std::endl;
    		if (stmt) sqlite3_finalize(stmt);
    		return {-1, "", "could not update token", ""};
    	}
    	sqlite3_bind_text(stmt, 1, newItem.value.c_str(), -1, SQLITE_STATIC);
    	sqlite3_bind_text(stmt, 2, newItem.description.c_str(), -1, SQLITE_STATIC);
    	sqlite3_bind_text(stmt, 3, newItem.expired_at.c_str(), -1, SQLITE_STATIC);
    	sqlite3_bind_int(stmt, 4, newItem.id);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error updating TOKEN" << std::endl;
    		sqlite3_finalize(stmt);
    		return {-1, "", "could not update token", ""};
    	}

    	sqlite3_finalize(stmt);
    	std::cout << "updated TOKEN" << std::endl;
    	return newItem;

    }

    void TokenDaoImpl::remove(const model::Token &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "DELETE FROM TOKEN where token_id = ?;";
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        	std::cerr << "Error preparing statement to remove TOKEN" << std::endl;
        	sqlite3_finalize(stmt);
        	return;
        }
    	sqlite3_bind_int(stmt, 1, item.id);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error removing TOKEN" << std::endl;
    		sqlite3_finalize(stmt);
    		return;
    	}

    	std::cout << "removed TOKEN" << std::endl;
    	sqlite3_finalize(stmt);
    }

	int TokenDaoImpl::getLastId() const{
    	sqlite3 *bd = m_connector.getDB();
    	const std::string sql {"select min(token_id)+1 from TOKEN "
								"where token_id+1 not in (select token_id from TOKEN) "
								"and exists (select 1 from TOKEN where token_id = 0);"};
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
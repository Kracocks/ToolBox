//
// Created by kracocks on 25/01/25.
//

#include "TokenDaoImpl.h"

#include <iostream>

namespace impl {
    TokenDaoImpl::TokenDaoImpl(): m_connector(bd::Connector::getInstance()) {}

    std::vector<model::Token> TokenDaoImpl::findAll() {
        std::vector<model::Token> tokens;
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "SELECT token_id, token_group_id, value FROM TOKEN;";
        sqlite3_stmt *stmt;

        int status = sqlite3_prepare_v3(bd, sql.c_str(), -1, SQLITE_PREPARE_PERSISTENT, &stmt, nullptr);
        if (status != SQLITE_OK) {
            std::cerr << "Error preparing statement to get all TOKEN" << std::endl;
            return tokens;
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            model::Token token{
            	sqlite3_column_int(stmt, 0),
            	sqlite3_column_int(stmt, 1),
            	reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2))};
            tokens.push_back(token);
        }

        sqlite3_finalize(stmt);

        return tokens;
    }

    std::vector<model::Token> TokenDaoImpl::findByValue(std::string &&value) {
        // When I first made this method I didn't think enough about how it is stupid
    	// But now that I noticed it I will let this because this is funny
        return std::vector<model::Token>{};
    }

    std::vector<model::Token> TokenDaoImpl::findByValue(const std::string &value) {
    	return std::vector<model::Token>{};
    }

    model::Token TokenDaoImpl::insert(model::Token &item) {
        sqlite3 *bd = m_connector.getDB();
        const std::string sql = "INSERT INTO TOKEN(token_group_id, value) values (?, ?);";
        sqlite3_stmt *stmt = nullptr;

        if (sqlite3_prepare_v2(bd, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        	std::cerr << "Error preparing statement to insert TOKEN" << std::endl;
        	if (stmt) sqlite3_finalize(stmt);
        	return {-1, -1, ""};
        }
    	sqlite3_bind_int(stmt, 1, item.tgroup_id);
    	sqlite3_bind_text(stmt, 2, item.value.c_str(), -1, SQLITE_STATIC);

    	if (sqlite3_step(stmt) != SQLITE_DONE) {
    		std::cerr << "Error inserting TOKEN" << std::endl;
    		sqlite3_finalize(stmt);
    		return {-1, -1, ""};
    	}

    	std::cout << "inserted TOKEN" << std::endl;
    	sqlite3_finalize(stmt);
    	return item;
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

} // impl
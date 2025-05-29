#include <iostream>
#define SQLITE_HAS_CODEC
#include <sqlite3.h>

#include "Connector.h"

#include <fstream>
#include <sstream>

namespace bd {
    // Protected
    Connector *Connector::m_connector = nullptr;

    Connector::Connector(const std::string& dbFilePath, const std::string& key) {
        if (dbFilePath.empty()) {
            std::cerr << "Database path is empty\n";
            return;
        }

        // Open database
        int res = sqlite3_open(dbFilePath.c_str(), &m_bd);
        if (res != SQLITE_OK) {
            std::cerr << "Error while opening database : "
                      << sqlite3_errmsg(m_bd) << std::endl;
            if (m_bd) sqlite3_close(m_bd);
            m_bd = nullptr;
            return;
        }

        // Define database key
		char* err_msg = nullptr;
		res = sqlite3_key(m_bd, key.c_str(), key.length());
		// std::string pragma_key = "PRAGMA key = '" + key + "';";
		// res = sqlite3_exec(m_bd, pragma_key.c_str(), nullptr, nullptr, &err_msg);
        if (res != SQLITE_OK) {
			std::cerr << "Error when applying database key : "
					  << sqlite3_errmsg(m_bd) << std::endl;
            sqlite3_close(m_bd);
            m_bd = nullptr;
            return;
        }

    	std::ifstream schemaFile("data/creation.sql");
    	if (schemaFile) {
    		std::ostringstream buffer;
    		buffer << schemaFile.rdbuf();
    		std::string sql = buffer.str();
    		res = sqlite3_exec(m_bd, sql.c_str(), nullptr, nullptr, &err_msg);
    		if (res != SQLITE_OK) {
    			std::cerr << "Error when executing SQL file : " << err_msg << std::endl;
    			sqlite3_free(err_msg);
				sqlite3_close(m_bd);
				m_bd = nullptr;
    		}
    	} else {
    		std::cerr << "Cannot load creation.sql file" << std::endl;
    	}
    }

    // Public
    Connector::~Connector() {
        if (m_bd) {
            sqlite3_close(m_bd);
            m_bd = nullptr;
        }
        if (m_connector) {
            delete m_connector;
            m_connector = nullptr;
        }
	}

    sqlite3 *Connector::getDB() const {
        return m_bd;
    }

	Connector &Connector::getInstance(const std::string& password) {
		if (m_connector == nullptr)
			m_connector = new Connector("data/passwords.sqlite", password);
        return *m_connector;
    }

	void Connector::close() {
		m_connector = nullptr;
	}
} // bd

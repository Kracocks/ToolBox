

#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <sqlcipher/sqlite3.h>
#include <string>

namespace bd {

    class Connector {
    protected:
        sqlite3 *m_bd{};
        static Connector *m_connector;

        Connector(const std::string &dbFilePath, const std::string &key);

    public:
        Connector(Connector &other) = delete;
        void operator=(const Connector &) = delete;

        ~Connector();
		static Connector &getInstance(const std::string& password);
        [[nodiscard]] sqlite3 *getDB() const;
    };

} // bd

#endif //CONNECTOR_H

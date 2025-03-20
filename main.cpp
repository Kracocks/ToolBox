#include <iostream>

#include "src/model/Identifiant.h"
#include "src/bd/Connector.h"

int main() {
	model::Identifiant<> ident(-1, "model", "test", true);
    std::cout << ident.getEmail() << std::endl;

    const std::string db_path = "data/passwords.sqlite";
    const std::string db_key = std::getenv("DB_KEY");

    bd::Connector& db = bd::Connector::getInstance();
    if (db.getDB()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cerr << "Failed to open db" << std::endl;
        return 1;
    }
    return 0;
}

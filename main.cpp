#include <iostream>
#include <map>

#include "src/bd/Connector.h"
#include "src/impl/ServiceDaoImpl.h"
#include "src/model/Encrypt.h"

// GLOBAL VARIABLE
std::map<std::string, std::string> commands;
std::string title {"TOOLBOX"};
std::string choice {};

std::string operator*(const std::string& s, const int &n) {
	std::string result {};
	result.reserve(s.size() * n);
	for (int i = 0; i < n; i++) {
		result += s;
	}
	return result;
}

void showTitle(const std::string &title) {
	std::cout << "+-" + (std::string("-") * (title.length())) << "-+" << std::endl
				  << "| " << title << " |" << std::endl
				  << "+-" + (std::string("-") * (title.length())) << "-+" << std::endl;
}

void showCommands() {
	showTitle("OPTIONS");
	std::cout << "Here are all the available options : " << std::endl;
	for (const std::pair<std::string, std::string> &command: commands) {
		std::cout << " - " << command.first << " -> " << command.second << std::endl;
	}
}

// Pages

void gotoPwdManager() {
	commands.erase("pwd_manager");
	commands["back"] = "Back to the precious page";
	commands["show"] = "Go to the page to show everything";

	while (choice != "quit" || choice != "back") {
		choice = "";

		showTitle("PASSWORD MANAGER");

		std::cout << "choice : " << std::endl;
		std::cin >> choice;

		if (choice == "show") {
			
		}
	}
	commands.erase("back");
	commands["pwd_manager"] = "Go to password manager";
}

int main() {
	if (!model::Encrypt::generateKeyPair()) {
		std::cerr << "Failed to generate key pair" << std::endl;
		return 2;
	}

    bd::Connector& db = bd::Connector::getInstance();
    if (db.getDB()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cerr << "Failed to open db" << std::endl;
        return 1;
    }

	commands["quit"] = "Leave the app";
	commands["help"] = "Show all available commands";
	commands["pwd_manager"] = "Show version information";

	while (choice != "q") {
		showTitle(title);

		std::cout << "choice : ";
		std::cin >> choice;

		if (!commands.contains(choice)) {
			std::cout << choice << " : option not found." << std::endl
					  << "'help' for more info" << std::endl;
		} else if (choice == "help") {
			showCommands();
		}
	}

    return 0;
}

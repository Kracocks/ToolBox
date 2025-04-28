#include "Login.h"

#include <iostream>

namespace model {
	void Login::display() const {
		std::cout << email << "\n" << password << "\n";
	}

	bool Login::operator==(const Login &other) const{
		return email == other.email && password == other.password;
	}
}

#ifndef LOGIN_H
#define LOGIN_H
#include <string>

namespace model {
	struct Login {
		int id;
		int service_id;
		std::string email;
		std::string password;

		void display() const;

		bool operator==(const Login &other) const;
	};
}

#endif // LOGIN_H

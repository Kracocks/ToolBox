//
// Created by kracocks on 12/01/25.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <string>

namespace model {
	struct Token {
		int id;
		int login_id;
		std::string value;
		std::string description;
		std::string expired_at;

		void display() const;

		bool operator==(const Token &other) const;
	};
} // model

#endif //TOKEN_H

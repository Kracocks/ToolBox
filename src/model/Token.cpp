//
// Created by kracocks on 12/01/25.
//

#include "Token.h"

#include <iostream>

namespace model {
    void Token::display() const {
	    std::cout << description << "\n" << value << " expires at" << expired_at << "\n";
    }

	bool Token::operator==(const Token &other) const {
	    return  (id == other.id) &&
	    		(value == other.value) &&
	    		(description == other.description) &&
	    		(expired_at == other.expired_at);
    }
} // model

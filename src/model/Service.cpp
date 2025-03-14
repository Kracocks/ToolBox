//
// Created by kracocks on 11/01/25.
//

#include "Service.h"
#include "Identifiant.h"

#include <iostream>

namespace model {
	void Service::display() const {
    	std::cout << "Service " << name << ((url.empty() ? "" : " at " + url)) << ":\nlogins :\n";
        for (const Identifiant<> &login : identifiants) {
        	std::cout << "\t";
            login.display();
        }
        std::cout << "\n";
    }
} // model
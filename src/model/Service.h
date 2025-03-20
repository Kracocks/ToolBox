//
// Created by kracocks on 11/01/25.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <string>
#include <vector>

#include "Identifiant.h"

namespace model {
	struct Service {
	    int id;
	    std::string name;
		std::string url;
	    std::vector<Identifiant<>> identifiants;

		void display() const;
	};
} // model

#endif //SERVICE_H

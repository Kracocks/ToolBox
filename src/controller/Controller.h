//
// Created by kracocks on 21/03/25.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include "../impl/ServiceDaoImpl.h"
#include "../impl/IdentifiantDaoImpl.h"
#include "../impl/TokenDaoImpl.h"

namespace controller {

	class Controller {
		private:
			impl::ServiceDaoImpl serviceDao;
			impl::IdentifiantDaoImpl identifiantDao;
			std::map<std::string, std::string> commands;

		public:
			Controller();
			~Controller();

			void handle();
	};

} // controller

#endif //CONTROLLER_H

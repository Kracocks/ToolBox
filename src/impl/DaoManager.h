//
// Created by kracocks on 21/03/25.
//

#ifndef DAOMANAGER_H
#define DAOMANAGER_H

#include "ServiceDaoImpl.h"
#include "IdentifiantDaoImpl.h"
#include "TokenDaoImpl.h"

namespace impl {

class DaoManager {
	private:
		ServiceDaoImpl services;
		IdentifiantDaoImpl logins;
		TokenDaoImpl tokens;
};

} // impl

#endif //DAOMANAGER_H

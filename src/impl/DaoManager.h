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
		ServiceDaoImpl m_services;
		IdentifiantDaoImpl m_logins;
		TokenDaoImpl m_tokens;

		public:
			DaoManager() = default;
			~DaoManager() = default;

			ServiceDaoImpl& getServices();
			IdentifiantDaoImpl& getLogins();
			TokenDaoImpl& getTokens();
	};

} // impl

#endif //DAOMANAGER_H

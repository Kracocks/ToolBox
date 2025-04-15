//
// Created by kracocks on 21/03/25.
//


#include "DaoManager.h"
#include "IdentifiantDaoImpl.h"
#include "ServiceDaoImpl.h"
#include "TokenDaoImpl.h"

namespace impl {
	impl::ServiceDaoImpl& DaoManager::getServices() {
		return m_services;
	}

	impl::IdentifiantDaoImpl& DaoManager::getLogins() {
		return m_logins;
	}

	impl::TokenDaoImpl& DaoManager::getTokens() {
		return m_tokens;
	}
} // impl

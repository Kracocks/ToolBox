//
// Created by kracocks on 25/01/25.
//

#ifndef TOKENDAOIMPL_H
#define TOKENDAOIMPL_H
#include "../bd/Connector.h"
#include "../bd/IGenericDao.h"
#include "../model/Token.h"

namespace impl {

    class TokenDaoImpl : public bd::IGenericDAO<model::Token> {
        bd::Connector &m_connector;

    public:
        explicit TokenDaoImpl();
        ~TokenDaoImpl() override = default;

    	model::Token find(const int & id) override;
        std::vector<model::Token> findAll() override;
        model::Token insert(model::Token &item) override;
    	model::Token update(const int& id, const model::Token &newItem) override;
        void remove(const model::Token &item) override;
    	[[nodiscard]] int getLastId() const;
    };

} // impl

#endif //TOKENDAOIMPL_H

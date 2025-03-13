//
// Created by kracocks on 24/01/25.
//

#ifndef IDENTIFIANTDAOIMPL_H
#define IDENTIFIANTDAOIMPL_H
#include <vector>
#include "../bd/Connector.h"
#include "../bd/IGenericDao.h"
#include "../model/Identifiant.h"

namespace impl {

    class IdentifiantDaoImpl : public bd::IGenericDAO<model::Identifiant<>> {
        bd::Connector &m_connector;

    public:
        explicit IdentifiantDaoImpl();

        ~IdentifiantDaoImpl() override = default;

    	model::Identifiant<> find(const int &id) override;
        std::vector<model::Identifiant<>> findAll() override;
        std::vector<model::Identifiant<>> findByEmail(std::string &&email);
        std::vector<model::Identifiant<>> findByEmail(const std::string &email);
        model::Identifiant<> insert(model::Identifiant<> &item) override;
    	model::Identifiant<> update(const int &id, const model::Identifiant<> &newItem) override;
    	void addService(const int &service, const model::Identifiant<> &login);
        void remove(const model::Identifiant<> &item) override;
    	[[nodiscard]] int getLastId() const;
    };

} // impl

#endif //IDENTIFIANTDAOIMPL_H

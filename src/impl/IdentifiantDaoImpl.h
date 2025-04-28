//
// Created by kracocks on 24/01/25.
//

#ifndef IDENTIFIANTDAOIMPL_H
#define IDENTIFIANTDAOIMPL_H
#include <vector>
#include "../bd/Connector.h"
#include "../bd/IGenericDao.h"
#include "../model/Login.h"

namespace impl {

	class IdentifiantDaoImpl : public bd::IGenericDAO<model::Login> {
        bd::Connector &m_connector;

    public:
        explicit IdentifiantDaoImpl();

        ~IdentifiantDaoImpl() override = default;

		model::Login find(const int &id) override;
		std::vector<model::Login> findAll() override;
		std::vector<model::Login> findByEmail(std::string &&email);
		std::vector<model::Login> findByEmail(const std::string &email);
		std::vector<model::Login> findByService(const int &service_id);
		model::Login insert(model::Login &item) override;
		model::Login update(const int &id, const model::Login &newItem) override;
		void remove(const model::Login &item) override;
    	[[nodiscard]] int getLastId() const;
    };

} // impl

#endif //IDENTIFIANTDAOIMPL_H

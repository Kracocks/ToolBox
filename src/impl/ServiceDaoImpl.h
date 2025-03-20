//
// Created by kracocks on 25/01/25.
//

#ifndef SERVICEDAOIMPL_H
#define SERVICEDAOIMPL_H
#include "../bd/Connector.h"
#include "../bd/IGenericDao.h"
#include "../model/Service.h"

namespace impl {

    class ServiceDaoImpl: public bd::IGenericDAO<model::Service> {
        bd::Connector &m_connector;

    public:
        explicit ServiceDaoImpl();

        ~ServiceDaoImpl() override = default;

    	model::Service find(const int &id) override;
        std::vector<model::Service> findAll() override;
        std::vector<model::Service> findByName(std::string &&name);
        std::vector<model::Service> findByName(const std::string &name);
    	void addLogin(const int &service_id, const model::Identifiant<> &item);
        model::Service insert(model::Service &item) override;
    	model::Service update(const int &id, const model::Service &newItem) override;
        void remove(const model::Service &item) override;
    	[[nodiscard]] int getLastId() const;
    };

} // impl

#endif //SERVICEDAOIMPL_H

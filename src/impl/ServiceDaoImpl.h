//
// Created by kracocks on 25/01/25.
//

#ifndef SERVICEDAOIMPL_H
#define SERVICEDAOIMPL_H
#include "../bd/Connector.h"
#include "../bd/IGenericDao.h"
#include "../model/Service.h"

namespace impl {

    class ServiceDaoImpl final: public bd::IGenericDAO<model::Service> {
        bd::Connector &m_connector;

    public:
        explicit ServiceDaoImpl();

        ~ServiceDaoImpl() override = default;

        std::vector<model::Service> findAll() override;
        std::vector<model::Service> findByName(std::string &&name);
        std::vector<model::Service> findByName(const std::string &name);
    	void addLogin(const int &service_id, const model::Identifiant<> &item);
        void insert(const model::Service &item) override;
        void remove(const model::Service &item) override;
    	[[nodiscard]] int getLastId() const;
    };

} // impl

#endif //SERVICEDAOIMPL_H

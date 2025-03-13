//
// Created by kracocks on 22/01/25.
//

#ifndef GENERICDAO_H
#define GENERICDAO_H

#include <vector>

namespace bd {

    template<class C>
    class IGenericDAO {
    public:
        virtual ~IGenericDAO() = default;

    	virtual C find(const int & id) = 0;
        virtual std::vector<C> findAll() = 0;
        virtual C insert(C& item) = 0;
    	virtual C update(const int& id, const C& newItem) = 0;
        virtual void remove(const C& item) = 0;
    };

} // bd

#endif //GENERICDAO_H

//
// Created by kracocks on 12/01/25.
//

#ifndef IDENTIFIANT_H
#define IDENTIFIANT_H
#include <algorithm>
#include <iostream>
#include <string>

namespace model {
	template <typename Int=int, typename Str=std::string>
    requires std::same_as<Int, int> &&
    		 std::same_as<Str, std::string>
    class Identifiant {
        Int m_id;
        Str m_email;
        Str m_password;
		Int m_service_id;

    public:
        Identifiant() = delete;

        /**
         * Create a login with an ID, an email and a password
         * @param id ID of the login
         * @param email Email of the login
         * @param password password of the login
         * @param service_id id of the service associated to the login
         */
		Identifiant(Int &&id, Str &&email, Str &&password, int service_id)
            : m_id(id),
              m_email(email),
              m_password(password),
			  m_service_id(service_id) {
        }

        /**
         * Get the ID of the login
         * @return ID of the login
         */
        [[nodiscard]] Int getId() const {return m_id;}

        /**
         * Get the email of the login
         * @return Email of the login
         */
        [[nodiscard]] Str getEmail() const {return m_email;}

        /**
         * Get the password of the login
         * @return Password of the login
         */
        [[nodiscard]] Str getPassword() const {return m_password;}

		/**
		 * Get the service id associated to the login
		 * @return Service id associated to the login
		 */
		int getServiceId() {
        	return m_service_id;
        }

        /**
         * Set the ID of the login
         * @param id New ID of the login
         */
		void setID(const int id) {m_id = std::move(id);}

        /**
         * Set the email of the login
         * @param email New email of the login
         */
        void setEmail(const Str &&email) {m_email = std::move(email);}

        /**
         * Set the password of the login
         * @param password New password of the login
         */
        void setPassword(const Str &&password) {m_password = std::move(password); }

		/**
		 * Change the service associated to the login
		 * @param service_id New service associated to the login
		 */
		void setServiceId(const Int &service_id) {m_service_id = service_id;}

        /**
         * Compare two logins
         * @param other Login to compare
         * @return True if the two objects are the same
         */
        bool operator==(const Identifiant &other) const {
			return m_email == other.m_email && m_password == other.m_password;
		}
	};

} // model

#endif //IDENTIFIANT_H

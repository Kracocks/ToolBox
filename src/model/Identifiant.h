//
// Created by kracocks on 12/01/25.
//

#ifndef IDENTIFIANT_H
#define IDENTIFIANT_H
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Encrypt.h"
#include "Token.h"

namespace model {
	template <typename Int=int, typename Str=std::string, typename Bool=bool, typename T=Token>
    requires std::same_as<Int, int> &&
    		 std::same_as<Str, std::string> &&
    		 std::same_as<Bool, bool> &&
    		 std::same_as<T, Token>
    class Identifiant {
        Int m_id;
        Str m_email;
        Str m_password;
		std::vector<T> m_tokens;

    public:
        Identifiant() = delete;

        /**
         * Create a login with an ID, an email and a password
         * @param id ID of the login
         * @param email Email of the login
         * @param password password of the login
         * @param shouldEncrypt encrypt the password if it needs to be encrypted
         */
        Identifiant(Int &&id, Str &&email, Str &&password, Bool &&shouldEncrypt)
            : m_id(std::forward<Int>(id)),
              m_email(std::forward<Str>(email)),
              m_password(std::forward<Str>(password)),
			  m_tokens({}) {
			if (shouldEncrypt) {
				std::string encrypted {};
				Encrypt::encrypt(email, &encrypted);
				password = encrypted;
			}
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
		 * Get the Tokens associated to the login
		 * @return Tokens associated to the login
		 */
		[[nodiscard]] std::vector<T> getTokens() const {return m_tokens;}

        /**
         * Set the ID of the login
         * @param id New ID of the login
         */
        void setID(const Int &&id) {m_id = std::move(id);}

        /**
         * Set the email of the login
         * @param email New email of the login
         */
        void setEmail(const Str &&email) {m_email = std::move(email);}

		/**
		 * Set the email of the login
		 * @param email New email of the login
		 */
		void setEmail(const Str &email) {m_email = std::move(email);}

        /**
         * Set the password of the login
         * @param password New password of the login
         */
        void setPassword(const Str &&password) {m_password = std::move(password);}

		/**
		 * Add a new token to the login
		 * @param token New token group to associate to the login
		 */
		void addTokenGroup(const T &&token) {m_tokens.push_back(token); }

		/**
		 * Remove a token associated to the login
		 * @param token Token associated to the login
		 */
		void removeTokenGroup(const T &&token) {
	        T it = std::find(m_tokens.begin(), m_tokens.end(), token);
        	if (it != m_tokens.end()) {
        		m_tokens.erase(it);
        	}
        }

    	void display() const {
	        std::cout << "Email : " <<  m_email << "\tPassword : " << m_password << "\n";
        	for (const T &token : m_tokens) {
        		std::cout << "\t";
        		token.display();
        	}
        }

        /**
         * Compare two logins
         * @param other Login to compare
         * @return True if the two objects are the same
         */
        bool operator==(const Identifiant &other) const {
            return m_email == other.m_email && m_password == other.m_password && m_tokens == other.m_tokens;
        }
    };

} // model

#endif //IDENTIFIANT_H

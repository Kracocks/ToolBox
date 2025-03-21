//
// Created by kracocks on 29/01/25.
//

#include "Encrypt.h"

#include <filesystem>
#include <iostream>
#include <openssl/pem.h>
#include <vector>
#include <sys/stat.h>

bool model::Encrypt::generateKeyPair() {
    const std::string privateKeyPath = std::string(getenv("HOME")) + "/.ToolBox/keys/private_key.pem";
    const std::string publicKeyPath = "./data/public_key.pem";

    if (std::filesystem::exists(privateKeyPath)) {
        std::cout << "Private key already exists. Checking public key...\n";

        if (!std::filesystem::exists(publicKeyPath)) {
            FILE *privateFile = fopen(privateKeyPath.c_str(), "r");
            if (!privateFile) {
                std::cerr << "Error: Can't open existing private key file\n";
                return false;
            }

            EVP_PKEY *pkey = PEM_read_PrivateKey(privateFile, nullptr, nullptr, nullptr);
            fclose(privateFile);
            if (!pkey) {
                std::cerr << "Error: Can't read private key\n";
                return false;
            }

            FILE *publicFile = fopen(publicKeyPath.c_str(), "wb");
            if (!publicFile) {
                std::cerr << "Error: Can't open public key file for writing\n";
                EVP_PKEY_free(pkey);
                return false;
            }

            if (!PEM_write_PUBKEY(publicFile, pkey)) {
                std::cerr << "Error: Can't write public key\n";
                fclose(publicFile);
                EVP_PKEY_free(pkey);
                return false;
            }

            fclose(publicFile);
            EVP_PKEY_free(pkey);

            std::cout << "Public key was missing and has been regenerated.\n";
        }

        return true;
    }

    std::filesystem::create_directories(std::string(getenv("HOME")) + "/.ToolBox/keys/");

    EVP_PKEY *pkey = nullptr;
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    if (!ctx) {
        std::cerr << "Error: Can't create the EVP_PKEY_CTX context\n";
        return false;
    }

    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cerr << "Error: Can't initialize the generation of the key\n";
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
        std::cerr << "Error: Can't define key size\n";
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        std::cerr << "Error: Failed generating RSA key\n";
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    FILE *privateFile = fopen(privateKeyPath.c_str(), "wb");
    if (!privateFile) {
        std::cerr << "Error: Can't open private_key.pem file\n";
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    if (!PEM_write_PrivateKey(privateFile, pkey, nullptr, nullptr, 0, nullptr, nullptr)) {
        std::cerr << "Error: Can't write private key\n";
        fclose(privateFile);
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    fclose(privateFile);

    chmod(privateKeyPath.c_str(), 0600);

    FILE *publicFile = fopen(publicKeyPath.c_str(), "wb");
    if (!publicFile) {
        std::cerr << "Error: Can't open public_key.pem file\n";
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    if (!PEM_write_PUBKEY(publicFile, pkey)) {
        std::cerr << "Error: Can't write public key\n";
        fclose(publicFile);
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }
    fclose(publicFile);

    std::cout << "RSA key pair generated successfully.\n";

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    return true;
}


bool model::Encrypt::encrypt(const std::string &input, std::string *output) {
    FILE *f = fopen("./data/public_key.pem", "r");
    if (!f) {
        std::cerr << "Error : Can't open public key, file might be missing. Please regenerate the public key\n";
        return false;
    }

    EVP_PKEY *pkey = PEM_read_PUBKEY(f, nullptr, nullptr, nullptr);
    fclose(f);
    if (!pkey) {
        std::cerr << "Error : Can't read public key\n";
        return false;
    }

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx || EVP_PKEY_encrypt_init(ctx) <= 0) {
        std::cerr << "Error : initialisation of encryption context\n";
        EVP_PKEY_free(pkey);
        return false;
    }

    size_t ciphertext_len = 0;
    if (EVP_PKEY_encrypt(ctx, nullptr, &ciphertext_len,
                         reinterpret_cast<const unsigned char *>(input.c_str()), input.length()) <= 0) {
        std::cerr << "Error : Failed to get the length of the encrypted text\n";
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    std::vector<unsigned char> ciphertext(ciphertext_len);
    if (EVP_PKEY_encrypt(ctx, ciphertext.data(), &ciphertext_len,
                         reinterpret_cast<const unsigned char *>(input.c_str()), input.length()) <= 0) {
        std::cerr << "Error : Failed to encrypt\n";
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    output->assign(reinterpret_cast<char *>(ciphertext.data()), ciphertext_len);

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    return true;
}

bool model::Encrypt::decrypt(const std::string &input, std::string *output) {
    FILE *f = fopen((std::string(getenv("HOME")) + "/.ToolBox/keys/private_key.pem").c_str(), "r");
    if (!f) {
        std::cerr << "Error : Can't open private key\n";
        return false;
    }

    EVP_PKEY *pkey = PEM_read_PrivateKey(f, nullptr, nullptr, nullptr);
    fclose(f);
    if (!pkey) {
        std::cerr << "Error : Can't read public key\n";
        return false;
    }

    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx || EVP_PKEY_decrypt_init(ctx) <= 0) {
        std::cerr << "Error : initialisation of decryption context\n";
        EVP_PKEY_free(pkey);
        return false;
    }

    size_t outlen = 0;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outlen,
                         reinterpret_cast<const unsigned char *>(input.data()), input.size()) <= 0) {
        std::cerr << "Error : Failed to get the length of the decrypted text\n";
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    std::vector<unsigned char> outbuf(outlen);
    if (EVP_PKEY_decrypt(ctx, outbuf.data(), &outlen,
                         reinterpret_cast<const unsigned char *>(input.data()), input.size()) <= 0) {
        std::cerr << "Error : Failed to decrypt\n";
        EVP_PKEY_free(pkey);
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

	output->assign(reinterpret_cast<char *>(outbuf.data()), outlen);

    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);

    return true;
}

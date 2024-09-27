#define _CRT_SECURE_NO_WARNINGS
#include <openssl/applink.c>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

class Client {
public:
    const int keySize = 16; // AES-128
    std::string name;
    std::vector<unsigned char> publicKey; // K'
    std::vector<unsigned char> sharedKey; // P
    std::vector<unsigned char> sessionKey; // K

    Client(std::string name);
    void syncSharedKey(Client&);
    std::vector<unsigned char> sendEpK();
    void receiveEpK(const std::vector<unsigned char>& EpK);
    std::vector<unsigned char> sendEp();
private:
    std::vector<unsigned char> encryptAES(const std::vector<unsigned char>& message, const std::vector<unsigned char>& key);
    std::vector<unsigned char> decryptAES(const std::vector<unsigned char>& encryptedMessage, const std::vector<unsigned char>& key);
};

Client::Client(std::string name) : name(name) {
    sharedKey.resize(keySize);
    publicKey.resize(keySize);
    sessionKey.resize(keySize);

    if (RAND_bytes(sharedKey.data(), sharedKey.size()) != 1) {
        std::cerr << "Error generating random shared key." << std::endl;
        abort();
    }

    if (RAND_bytes(publicKey.data(), publicKey.size()) != 1) {
        std::cerr << "Error generating random public key." << std::endl;
        abort();
    }

    if (RAND_bytes(sessionKey.data(), sessionKey.size()) != 1) {
        std::cerr << "Error generating random public key." << std::endl;
        abort();
    }
}

void Client::syncSharedKey(Client& client) {
    this->sharedKey = client.sharedKey;
}

std::vector<unsigned char> Client::sendEpK() {
    return encryptAES(publicKey, sharedKey);
}

void Client::receiveEpK(const std::vector<unsigned char>& EpK) {
    publicKey = decryptAES(EpK, sharedKey);
}

std::vector<unsigned char> Client::encryptAES(const std::vector<unsigned char>& message, const std::vector<unsigned char>& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create context." << std::endl;
        return {};
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, key.data(), nullptr) != 1) {
        handleErrors();
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    std::vector<unsigned char> output(message.size() + EVP_CIPHER_block_size(EVP_aes_128_ecb()));
    int len = 0;

    if (EVP_EncryptUpdate(ctx, output.data(), &len, message.data(), message.size()) != 1) {
        handleErrors();
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    int final_len = 0;
    if (EVP_EncryptFinal_ex(ctx, output.data() + len, &final_len) != 1) {
        handleErrors();
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    output.resize(len + final_len);
    EVP_CIPHER_CTX_free(ctx);
    return output;
}

std::vector<unsigned char> Client::decryptAES(const std::vector<unsigned char>& encryptedMessage, const std::vector<unsigned char>& key) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        std::cerr << "Failed to create context." << std::endl;
        return {};
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, key.data(), nullptr) != 1) {
        handleErrors();
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    std::vector<unsigned char> output(encryptedMessage.size());
    int len = 0;

    if (EVP_DecryptUpdate(ctx, output.data(), &len, encryptedMessage.data(), encryptedMessage.size()) != 1) {
        handleErrors();
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    int final_len = 0;
    if (EVP_DecryptFinal_ex(ctx, output.data() + len, &final_len) != 1) {
        handleErrors();
        EVP_CIPHER_CTX_free(ctx);
        return {};
    }

    output.resize(len + final_len);
    EVP_CIPHER_CTX_free(ctx);
    return output;
}

int main() {
    if (OPENSSL_init_crypto(0, nullptr) != 1) {
        std::cerr << "OpenSSL initialization failed." << std::endl;
        return 1;
    }

    Client server("Alice");
    Client client("Bob");
    client.syncSharedKey(server);
    client.receiveEpK(server.sendEpK());

    std::vector<unsigned char> temp = server.sendEpK();

    std::cout << "Encrypted Data: ";
    for (unsigned char byte : temp) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    std::cout << std::dec << std::endl;

    return 0;
}
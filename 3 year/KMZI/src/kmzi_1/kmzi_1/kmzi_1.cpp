#define _CRT_SECURE_NO_WARNINGS
#include <openssl/applink.c>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rc4.h>

#pragma warning(push)
#pragma warning(disable : 4996)

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

class Client {
public:
    std::string name;

    Client(std::string name);
    void syncSharedKey(Client&);
    std::vector<unsigned char> sendEpK();
    void receiveEpK(const std::vector<unsigned char>& EpK);
    std::vector<unsigned char> sendEpEkK();
    void receiveEpEkK(const std::vector<unsigned char>& EpEkK);
    std::vector<unsigned char> sendEkRa();
    std::vector<unsigned char> sendEkSa();
    void receiveEkRaSa(const std::vector<unsigned char>& Ra, const std::vector<unsigned char>& Sa);
    std::vector<unsigned char> sendEkRecRandM();
    bool receiveEkRaRbSb(const std::vector<unsigned char>& Ra, const std::vector<unsigned char>& Rb, const std::vector<unsigned char>& Sb);
    bool receiveEkRb(const std::vector<unsigned char>& Rb);
    std::vector<unsigned char> sendEkRb();

    void makeKey();

    std::vector<unsigned char> encrypt(std::string message);
    std::string decrypt(const std::vector<unsigned char>& cipher);

private:
    const int keySize = 16; // AES-128
    std::vector<unsigned char> publicKey; // K'
    std::vector<unsigned char> sharedKey; // P
    std::vector<unsigned char> sessionKey; // K
    std::vector<unsigned char> randomMessage; //Ra or Rb 
    std::vector<unsigned char> secretPart; //Sa or Sb 
    std::vector<unsigned char> recRandMessage;
    std::vector<unsigned char> recSecretMessage;

    void generateRandVec(std::vector<unsigned char>& vec);
    std::vector<unsigned char> encryptAES(const std::vector<unsigned char>& message, const std::vector<unsigned char>& key);
    std::vector<unsigned char> decryptAES(const std::vector<unsigned char>& encryptedMessage, const std::vector<unsigned char>& key);
};

void Client::generateRandVec(std::vector<unsigned char>& vec) {
    if (RAND_bytes(vec.data(), vec.size()) != 1) {
        std::cerr << "Error generating random vec." << std::endl;
        abort();
    }
}

Client::Client(std::string name) : name(name) {
    sharedKey.resize(keySize);
    publicKey.resize(keySize);
    sessionKey.resize(keySize);
    randomMessage.resize(keySize);
    secretPart.resize(keySize);
    recRandMessage.resize(keySize);
    recSecretMessage.resize(keySize);

    generateRandVec(sharedKey);
    generateRandVec(publicKey);
    generateRandVec(sessionKey);
    generateRandVec(randomMessage);
    generateRandVec(secretPart);
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

std::vector<unsigned char> Client::sendEpEkK() {
    return encryptAES(encryptAES(sessionKey, publicKey), sharedKey);
}

void Client::receiveEpEkK(const std::vector<unsigned char>& EpEkK) {
    sessionKey = decryptAES(decryptAES(EpEkK, sharedKey), publicKey);
}

std::vector<unsigned char> Client::sendEkRa() {
    return encryptAES(randomMessage, sessionKey);
}

std::vector<unsigned char> Client::sendEkSa() {
    return encryptAES(secretPart, sessionKey);
}

void Client::receiveEkRaSa(const std::vector<unsigned char>& Ra, const std::vector<unsigned char>& Sa) {
    recRandMessage = decryptAES(Ra, sessionKey);
    recSecretMessage = decryptAES(Sa, sessionKey);
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

std::vector<unsigned char> Client::sendEkRecRandM() {
    return encryptAES(recRandMessage, sessionKey);
}

bool Client::receiveEkRaRbSb(const std::vector<unsigned char>& Ra, const std::vector<unsigned char>& Rb, const std::vector<unsigned char>& Sb) {
    if (decryptAES(Ra, sessionKey) != randomMessage)
        return false;

    recRandMessage = decryptAES(Rb, sessionKey);
    recSecretMessage = decryptAES(Sb, sessionKey);
    return true;
}

bool Client::receiveEkRb(const std::vector<unsigned char>& Rb) {
    if (decryptAES(Rb, sessionKey) != randomMessage)
        return false;
    return true;
}

std::vector<unsigned char> Client::sendEkRb() {
    return encryptAES(recRandMessage, sessionKey);
}



void Client::makeKey() {
    for (size_t i = 0; i < secretPart.size(); ++i) 
        sessionKey[i] = secretPart[i] ^ recSecretMessage[i];
    
}


std::vector<unsigned char> Client::encrypt(std::string message) {
    RC4_KEY rc4Key;
    RC4_set_key(&rc4Key, sessionKey.size(), sessionKey.data());

    std::vector<unsigned char> plaintext(message.begin(), message.end());
    std::vector<unsigned char> ciphertext(plaintext.size());
    RC4(&rc4Key, plaintext.size(), plaintext.data(), ciphertext.data());

    return ciphertext;
}

std::string Client::decrypt(const std::vector<unsigned char>& ciphertext) {
    std::string tempstr(ciphertext.begin(), ciphertext.end());
    std::vector<unsigned char> temp = encrypt(tempstr);
    return std::string(temp.begin(), temp.end());
}



bool establishConection(Client& server, Client& client) {
    client.syncSharedKey(server);
    client.receiveEpK(server.sendEpK());
    server.receiveEpEkK(client.sendEpEkK());
    client.receiveEkRaSa(server.sendEkRa(), server.sendEkSa());
    if (!server.receiveEkRaRbSb(client.sendEkRecRandM(), client.sendEkRa(), client.sendEkSa()))
        return false;
    if (!client.receiveEkRb(server.sendEkRb()))
        return false;
    server.makeKey();
    client.makeKey();
    return true;
}



int main() {
    if (OPENSSL_init_crypto(0, nullptr) != 1) {
        std::cerr << "OpenSSL initialization failed." << std::endl;
        return 1;
    }

    Client server("Alice");
    Client client("Bob");
    
    if (establishConection(server, client)) {
        std::cout << "\nSuccesfull conection\n\n";
        std::cout << "Enter message to encrypt: ";
        std::string message, result;
        std::cin >> message;
        std::vector<unsigned char> ciphertext = server.encrypt(message);
        result = std::string(ciphertext.begin(), ciphertext.end());
        std::cout << "Encrypted text: " << result << "\n";
        result = client.decrypt(ciphertext);
        std::cout << "Decrypted text: " << result << "\n";
    }
    else {
        std::cerr << "Error with conection.\n";
    }
    return 0;
}
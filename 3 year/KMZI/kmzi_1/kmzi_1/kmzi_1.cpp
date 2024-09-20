#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <string.h>

class Client {
public:
    Client(const std::string& username, const std::string& password)
        : username(username), password(password) {}

    bool connect(Client& other) {
        // Этап 1: Генерация случайного числа
        unsigned char A[16];
        RAND_bytes(A, sizeof(A));

        // Этап 2: Хэширование пароля
        unsigned char passwordHash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)password.c_str(), password.size(), passwordHash);

        // Этап 3: Формирование общего ключа
        unsigned char K[16];
        for (int i = 0; i < sizeof(K); ++i) {
            K[i] = A[i] ^ passwordHash[i % SHA256_DIGEST_LENGTH];
        }

        // Этап 4: Отправка A и K другому клиенту
        std::cout << username << " connected to " << other.username << std::endl;
        other.receive(A, K);
        return true;
    }

    void receive(const unsigned char* A, const unsigned char* K) {
        // Этап 5: Подтверждение получения
        std::cout << username << " received A from other client." << std::endl;

        // Здесь можно добавить дополнительные шаги для завершения обмена ключами
        // Например, можно использовать K для шифрования сообщений
    }

    std::string encrypt(const std::string& plaintext, const unsigned char* K) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx, EVP_rc4(), NULL, K, NULL);

        std::string ciphertext;
        ciphertext.resize(plaintext.size() + EVP_CIPHER_block_size(EVP_rc4()));
        int len;

        EVP_EncryptUpdate(ctx, (unsigned char*)ciphertext.data(), &len, (unsigned char*)plaintext.data(), plaintext.size());
        ciphertext.resize(len);

        EVP_EncryptFinal_ex(ctx, (unsigned char*)ciphertext.data() + len, &len);
        ciphertext.resize(ciphertext.size() + len);

        EVP_CIPHER_CTX_free(ctx);
        return ciphertext;
    }

    std::string decrypt(const std::string& ciphertext, const unsigned char* K) {
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, EVP_rc4(), NULL, K, NULL);

        std::string plaintext;
        plaintext.resize(ciphertext.size());
        int len;

        EVP_DecryptUpdate(ctx, (unsigned char*)plaintext.data(), &len, (unsigned char*)ciphertext.data(), ciphertext.size());
        plaintext.resize(len);

        EVP_DecryptFinal_ex(ctx, (unsigned char*)plaintext.data() + len, &len);
        plaintext.resize(plaintext.size() + len);

        EVP_CIPHER_CTX_free(ctx);
        return plaintext;
    }

private:
    std::string username;
    std::string password;
};

int main() {
    Client clientA("Alice", "password123");
    Client clientB("Bob", "password456");

    if (clientA.connect(clientB)) {
        std::string message = "Hello, Bob!";
        unsigned char K[16]; // Здесь должен быть получен общий ключ K

        // Для примера используем K как нули (нужно заменить на правильный K)
        memset(K, 0, sizeof(K));

        std::string encryptedMessage = clientA.encrypt(message, K);
        std::string decryptedMessage = clientB.decrypt(encryptedMessage, K);

        std::cout << "Encrypted Message: " << encryptedMessage << std::endl;
        std::cout << "Decrypted Message: " << decryptedMessage << std::endl;
    }

    return 0;
}
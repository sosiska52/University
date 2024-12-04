//#include "Crypt.h"
//
//
//void handleErrors() {
//    ERR_print_errors_fp(stderr);
//    abort();
//}
//
//Client::Client(std::string name) : name(name) {
//    int flag = 0;
//    sharedKey = std::vector<unsigned char>(keySize);
//    publicKey = std::vector<unsigned char>(keySize);
//    flag += RAND_bytes(sharedKey.data(), sharedKey.size());
//    flag += RAND_bytes(publicKey.data(), publicKey.size());
//    if (flag != 2) {
//        std::cerr << "Error generating random key." << std::endl;
//    }
//}
//
//void Client::syncSharedKey(Client& client) {
//    this->sharedKey = client.sharedKey;
//}
//
//std::vector<unsigned char> Client::sendEpK() {
//
//    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
//    if (!ctx) {
//        std::cout << "Failed to create context." << std::endl;
//        return {}; // Возврат пустого вектора при ошибке
//    }
//
//    if (EVP_EncryptInit_ex(ctx, EVP_des_ecb(), nullptr, sharedKey.data(), nullptr) != 1) {
//        handleErrors();
//        EVP_CIPHER_CTX_free(ctx);
//        return {};
//    }
//
//    std::vector<unsigned char> output(publicKey.size() + EVP_CIPHER_block_size(EVP_des_ecb()));
//    int len = 0;
//
//    if (EVP_EncryptUpdate(ctx, output.data(), &len, publicKey.data(), publicKey.size()) != 1) {
//        handleErrors();
//        EVP_CIPHER_CTX_free(ctx);
//        return {};
//    }
//
//    int final_len = 0;
//    if (EVP_EncryptFinal_ex(ctx, output.data() + len, &final_len) != 1) {
//        handleErrors();
//        EVP_CIPHER_CTX_free(ctx);
//        return {};
//    }
//
//    output.resize(len + final_len);
//    EVP_CIPHER_CTX_free(ctx);
//    return output;
//}
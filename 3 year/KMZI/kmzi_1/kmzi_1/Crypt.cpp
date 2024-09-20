//#include "Crypt.h"
//
//std::string generateNonce(size_t length) {
//    unsigned char buffer[32]; // Достаточно для 256-битного nonce
//    if (RAND_bytes(buffer, length) != 1) {
//        throw std::runtime_error("Ошибка генерации случайного числа");
//    }
//
//    // Преобразуем в строку в шестнадцатичном формате
//    std::ostringstream oss;
//    for (size_t i = 0; i < length; ++i) {
//        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
//    }
//    return oss.str();
//}
//
//CryptUser::CryptUser(Role role) {
//    this->userRole = role;
//    this->nonce = generateNonce(16);
//    publicKey = generateRSAKey(2048);
//}
//
//RSA* CryptUser::generateRSAKey(int bits) {
//    RSA* rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
//    if (!rsa) handleErrors();
//    return rsa;
//}
//
//void CryptUser::handleErrors() {
//    ERR_print_errors_fp(stderr);
//    abort();
//}
//
//std::string CryptUser::encryptKey(RSA* spKey) {
//    std::string encrypted(RSA_size(spKey), '\0');
//    std::string message = "secretmessageB";
//    int result = RSA_public_encrypt(message.size(), (unsigned char*)message.c_str(),
//        (unsigned char*)encrypted.data(), spKey, RSA_PKCS1_OAEP_PADDING);
//    if (result == -1) handleErrors();
//    return encrypted;
//}
//
//std::string CryptUser::decryptKey(RSA* spKey, std::string encryptedR) {
//    std::string decrypted(RSA_size(spKey), '\0');
//    int result = RSA_private_decrypt(encryptedR.size(), (unsigned char*)encryptedR.c_str(),
//        (unsigned char*)decrypted.data(), spKey, RSA_PKCS1_OAEP_PADDING);
//    if (result == -1) handleErrors();
//    decrypted.resize(result); 
//    return decrypted;
//}
//
//void CryptUser::makeSharedKey(std::string data) {
//    if (this->userRole == SENDER) {
//        data = "secretkeyA" + data;
//        unsigned char hash[SHA256_DIGEST_LENGTH];
//        SHA256((unsigned char*)data.c_str(), data.size(), hash);
//        this->sharedKey = std::string((char*)hash, SHA256_DIGEST_LENGTH);
//    }
//    else {
//        unsigned char hash[SHA256_DIGEST_LENGTH];
//        SHA256((unsigned char*)data.c_str(), data.size(), hash);
//        this->sharedKey = std::string((char*)hash, SHA256_DIGEST_LENGTH);
//    }
//}
//
//bool CryptUser::connect(CryptUser sender, CryptUser reciever) {
//    std::string result = reciever.encryptKey(sender.sendKey());
//    std::string res = sender.decryptKey(reciever.sendKey(), result);
//    std::cout << res << "\n";
//}
//
//RSA* CryptUser::sendKey() {
//    return this->publicKey;
//}
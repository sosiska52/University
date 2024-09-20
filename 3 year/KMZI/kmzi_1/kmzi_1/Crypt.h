#pragma once
#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstring>

enum Role {
	RECIEVER,
	SENDER
};

class CryptUser {
public:
	CryptUser(Role);
	bool connect(CryptUser sender, CryptUser reciever);
private:
	//std::string ID;
	RSA* publicKey;
	std::string nonce;
	std::string sharedKey;

	RSA* generateRSAKey(int bits);
	void handleErrors();

	std::string encryptKey(RSA* spKey);
	std::string decryptKey(RSA* spKey, std::string encryptedR);
	void makeSharedKey(std::string);
	std::string sendID();
	RSA* sendKey();
	std::string sendNonce();

	Role userRole;
	/*unsigned char nonceA[16];
	unsigned char password[16];
	void generate_random_password(unsigned char* password, int length);*/
};
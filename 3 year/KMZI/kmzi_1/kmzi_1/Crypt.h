//#pragma once
//#define OPENSSL_USE_APPLINK
//
//#define _CRT_SECURE_NO_WARNINGS
//#include <openssl/applink.c>
//#include <string>
//#include <vector>
//#include <iomanip>
//#include <iostream>
//#include <openssl/rand.h>
//#include <openssl/evp.h>
//#include <openssl/err.h>
//
//class Client {
////for server
//public:
//	//name
//	//public key K'
//	//shared P
//	
//	//2)send encrypted public key -> (name, Ep(K'))
//	//8)send Ek(Ra, Sa)
//	//14)send Ek(Rb)
//
//	const int keySize = 8;
//	std::string name;
//	std::vector<unsigned char> publicKey; // K'
//	std::vector<unsigned char> sharedKey; // P
//
//	Client(std::string name);
//	void syncSharedKey(Client&);
//	std::vector<unsigned char> sendEpK();
//private:
//	//private key
//	//1)symetrical crypt public key with private key(K', P) -> Ep(K')
//	//6)decrypt Ep(Ek'(K)) -> K
//	//7)generate rand message Ra and Sa and encrypt it with K(K) -> Ek(Ra, Sa)
//	//12)decrypt Ek(Ra, Rb, Sb) -> Ra, Rb, Sb
//	//13)if Ra correct then encrypt Rb -> Ek(Rb) 
//
//
//
//
////for client
//public:
//	//name
//	//shared P
//	
//	//5)send Ep(Ek'(K))
//	//11)send Ek(Ra, Rb, Sb)
//private:
//	//3)decrypt encrypted public key(Ep, P) -> K'
//	//4)generate session key(K) and encrypt it twice(P, K') -> Ep(Ek'(K))
//	//9)decrypt Ek(Ra, Sa) -> Ra, Sa
//	//10)generate Rb and Sb encrypt Ra and Rb and Sb -> Ek(Ra, Rb, Sb)
//	//15)decrypt Ek(Rb) -> Rb
//	//16)if Rb correct then your session key = Sa XOR Sb
//};
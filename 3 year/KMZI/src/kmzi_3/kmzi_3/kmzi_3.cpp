#include <iostream>
#include "RipeMD160_Hash.h"
#include "TCP.h"
#include "ShnorDigitalSignature.h"

int main()
{
    //RIPEMD160 ripemd160;
    std::string msg1 = "Hello my name is nikita and this is my secret message";
    //std::string msg1 = "privet";
    //uint8_t digest[20];
    //ripemd160.hash(msg1, msg1.length(), digest);

    //std::cout << "RIPEMD160(\"" << msg1 << "\") = ";
    //for (const auto& byte : digest) {
    //    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    //}
    //std::cout << std::endl;

    //TCPServer serv("127.168.0.1", 666);
    //TCPClient client;

    ShnorDigitalSignature dsa;
    auto signature = dsa.sign(msg1);
    std::cout << "Signature: (e, s) = (" << signature.first << ", " << signature.second << ")\n";

    if (dsa.verify(signature, msg1))
        std::cout << "True";
    else std::cout << "False";
}
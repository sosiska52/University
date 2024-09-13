#include <iostream>
#include <openssl/rand.h>

int main()
{
	unsigned char nonceA[16];
	RAND_bytes(nonceA, sizeof(nonceA));
	for (int i = 0; i < 16; i++) {
		std::cout << int(nonceA[i]) << "\n";
	}
}
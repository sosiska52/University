#include <iostream>
#include "CBCTable.h"

int main()
{
	CBCTable table;
	table.encryptStandard("text.txt");
	table.decryptStandard("encrypted1.txt");
	table.encryptDouble("text.txt");
	table.decryptDouble("encrypted2.txt");
	return 0;
}
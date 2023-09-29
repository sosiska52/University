#include <iostream>
using namespace std;
int main()
{
	int sr=0, sh=0, s1=0, s=0, t=0, p=0, pokazatel=0,jj=0,kk=0;
	int kod[13];
	char simb;
	//ввод кода в массив 
	for (int i = 0; i < 13; i++)
	{
		cin >> simb;
		if (simb >= '0' && simb <= '9')
			kod[i] = simb - '0';
		else kod[i] = -1;
	}
	//перебирает массив и ищет место неправильного эл.
	for (int i = 0; i < 13; i++)
	{
		if (kod[i] == -1)
		{
			pokazatel = 1;
			//подбирает правильный эл.
			for (int j = 0; j < 10; j++)
			{
				kod[i] = j;
				for (int i = 0; i < 13; i++)
				{
					if (i % 2 == 1)
						sr = sr + kod[i];
					else sh = sh + kod[i];
				}
				sh = sh - kod[12];
				s1 = sr * 3;
				s = sh + s1;
				t = s % 10;
				p = 10 - t;
				if (p == kod[12])
				{
					kk = i;
					jj = j;
					break;
				}
				else
					sr = sh = s1 = s = t = p = 0;
			}
		}
	}
	//проверка на легальность кода
	for (int i = 0; i < 13; i++)
	{
		if (i % 2 == 1)
			sr = sr + kod[i];
		else sh = sh + kod[i];
	}
	sh = sh - kod[12];
	s1 = sr * 3;
	s = sh + s1;
	t = s % 10;
	p = 10 - t;
	if (p == kod[12])
	{
		pokazatel = 2;
	}
	//вывод результата
	 if (pokazatel == 2)
		 cout <<"the code accepted without errors";
	 if (pokazatel == 1)
	 {
		 cout << "the code not accepted, error in position: " << kk+1 << endl << "corrected with: " << jj;
	 }
	 if (pokazatel == 0)
		 cout << "the code is illegal";
	return 0;
}
#include <math.h>
#include <conio.h>
#include <random>
#include <iostream>

using namespace std;

//возведение в степень по модулю

unsigned __int64 As(unsigned base, unsigned __int64 exp, unsigned __int64 modulo)
{
	unsigned __int64 res = 1;

	while (exp != 0)
	{
		if ((exp & 1) != 0)
		{
			res = (1ll * res * base) % modulo;
		}

		base = (1ll * base * base) % modulo;
		exp >>= 1;
	}

	return  res;
}


unsigned  __int64  random(unsigned __int64  p)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, p - 1);
	unsigned __int64  rand = dist(gen);
	return rand;

}



void main() {
	unsigned 	 __int64  p;
	cout << "enter p:";
	cin >> p;
	int g = 5;
	unsigned 	 __int64  a = random(p);

	unsigned  __int64  B;

	unsigned  __int64  A = As(g, a, p);
	cout << "A=" << A << endl;
	cout << "a=" << a << endl;
	cout << "g=" << g << endl;

	cout << "enter B:";
	cin >> B;
	unsigned __int64  Secret = As(B, a, p);

	cout << "Secret Key=" << Secret << endl;


	_getch();
}

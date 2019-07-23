#include <iostream>
#include <conio.h>

double func(double x) {
	return ((x - 15)*(x - 15)) + 5;
}


double F(int n)
{
	double sqrt5 = sqrt(5.0), pow2n = pow(2.0, n);
	return (pow(1.0 + sqrt5, n) / pow2n - pow(1.0 - sqrt5, n) / pow2n) / sqrt5;
}


using namespace std;
void main() {
	
{double const k1 = ((3 - sqrt(5)) / 2);
	double const k2 = ((sqrt(5) - 1) / 2);
	double x1, x2, ai, bi, eps = 0.001, func1, f2, b2, a2;
	double n = 0;

	ai = 2;
	bi = 200;
	x1 = ai + k1 * (bi - ai);
	x2 = ai + k2 * (bi - ai);
	/*method of dichotomy*/
	/*{

	func1 = func(x1);
	f2 = func(x2);

	while ((bi - ai) > eps)
	{
		b2 = bi;
		a2 = ai;
		if (func1 > f2)
		{
			ai = x1;
			x1 = x2;
			x2 = ai + k2 * (bi - ai);
			func1 = f2;
			f2 = func(x2);

		}
		else
		{

			bi = x2;
			x2 = x1;
			x1 = ai + k1 * (bi - ai);
			f2 = func1;
			func1 = func(x1);
		}


		cout << ai << "  " << bi << "  " << bi - ai << "  " << (b2 - a2) / (bi - ai) << "  " << x1 << "  " << x2 << "  " << func << "  " << f2 << endl;
	}}*/

	/*method of the Golden section*/
	/*{double b = 1E-6;

	while ((bi - ai) > eps)
	{
		a2 = ai;
		b2 = bi;
		if (func1 > f2)
		{
			ai = x1;


		}
		else {
			bi = x2;
		}
		x1 = (ai + bi - b) / 2;
		x2 = (ai + bi + b) / 2;
		func1 = func(x1);
		f2 = func(x2);
		cout << ai << "  " << bi << "  " << bi - ai << "  " << (b2 - a2) / (bi - ai) << "  " << x1 << "  " << x2 << "  " << func << "  " << f2 << endl;
	}}*/

	 /*fibonacci*/
	
	double len = fabs(ai - bi);
	int iter = 0, vf = 2;
	while (F(n) < (bi - ai) / eps)
	n ++ ;

	 x1 = ai + (F(n - 2) / F(n)) * (bi - ai);
	double f1 = func(x1);
	 x2 = ai + (F(n - 1) / F(n)) * (bi - ai);
    f2 = func(x2);

	for (int k = 0; k < n - 3; k++)
	{
		a2 = ai;
		b2 = bi;
		if (f1 <= f2)
		{
			bi = x2;
			x2 = x1;
			f2 = f1;
			x1 = ai + (F(n - k - 3) / F(n - k - 1)) * (bi - ai);
			f1 = func(x1);
			vf++;
		}
		else
		{
			ai = x1;
			x1 = x2;
			f1 = f2;
			x2 = ai + (F(n - k - 2) / F(n - k - 1)) * (bi - ai);
			f2 = func(x2);
			vf++;
		}
		cout << ai << "  " << bi << "  " << bi - ai << "  " << (b2 - a2) / (bi - ai) << "  " << x1 << "  " << x2 << "  " << func << "  " << f2 << endl;
		len = bi - ai;
		iter++;
	}

	cout << "KOL-VO ITERACIY:" << iter << endl;
	cout << "VICHESLENNO FUNC: " << vf;

	_getch();
}
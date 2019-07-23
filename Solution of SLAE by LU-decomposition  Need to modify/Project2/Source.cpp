#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <locale>
#include <iostream>
using namespace std;
typedef double real;
typedef double scalar;

struct matrix {
	vector< vector<real> >A;
	vector< vector<real> >B;
	int n;
	int m;
	int p;
	int q;
	vector<real>F;
	vector<real>x;
	void read();

	void razl();
	void print();
	void CalcX();
	void CalcY();
	
};

void matrix::read() {
	ifstream  Aa("A.txt");
	ifstream  input("input.txt");
	ifstream  Ff("F.txt");
	input >> n;
	input >> p;
	input >> q;
	m = p + q + 1;
	F.resize(n);
	for (int i = 0; i < n; i++) { Ff >> F[i]; }
	A.resize(n, vector<real>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			Aa >> A[i][j];
		}
	}
}


void matrix::print() {
	ofstream  LU("LU.txt");
	ofstream  x("x.txt");
	for (int i = 0; i < n; i++) {
		x << F[i] << " ";
		for (int j = 0; j < m; j++) {
			LU << A[i][j] << " ";
		}
		LU << endl;
	}
}

void matrix::razl() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scalar s = 0;
			if (j <= p) {
				for (int k = 1; (k + p < m) && (j + k <= p) && (i - k >= 0); k++) {
					s += A[i - k][j + k] * A[i - k][p + k];
				}
				A[i][j] = A[i][j] - s;
			}
			else {
				for (int k = 1; (j + k < m) && (k <= p) && (i - k >= 0); k++) {
					s += A[i - k][k] * A[i - k][j + k];
				}
				A[i][j] = (A[i][j] - s) / A[i][0];
			}
		}
	}
}

void matrix::CalcY()// прямой ход (Ly=F)
{
	for (int i = 0; i < n; i++) {
		scalar s = 0;
		for (int k = 1; k <= p; k++) { if (i - k >= 0) { s += F[i - k] * A[i - k][k]; } }
		F[i] = (F[i] - s) / A[i][0];
	}
	ofstream  y("y.txt");
	for (int i = 0; i < n; i++) {
		y << F[i] << " ";
	}
}

void matrix::CalcX()// обратный ход (Ux=y)
{
	for (int i = n - 1; i >= 0; i--) {
		scalar s = 0;
		for (int k = 1; k <= q; k++) { if ((p + k < m) && (i + k < n)) { s += F[i + k] * A[i][p + k]; } }
		F[i] = (F[i] - s);
	}
}




void main() {

	int flag = 0;
	try
	{
		cout << "1 - LU "<< endl;
		cin >> flag;
		switch (flag)
		{
		case 1:
		{
			matrix M;

			real w = 0;
			ofstream  iks("x.txt");
			iks.precision(15);
			for (int i = 0; i < 20; i++)
			{
				M.read();
				w = pow(10.0, -i);
				M.A[0][0] += w;
				M.F[0] += w;
				M.razl();
				M.CalcY();
				M.CalcX();
				for (int i = 0; i < M.n; i++)
				{
					iks << M.F[i] << endl;
				}
				iks << endl;
			}
			break;
		}

	
		default:
		{
			break;
		}
		}
	}
	catch (int error)
	{
		switch (error)
		{
		case 1:
		{
			cout << "error";
			system("pause");
			break;
		}
		}
	}
}

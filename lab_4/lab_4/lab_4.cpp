#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iomanip>

using namespace std;

const double eps = 0.01;
const int toch = 4;
const int N = 3; // кол-во уравнений
double matrix[N][N + 1];
double otvet[N] = { 0 };
double F[N];
double X[N];
//double Xk[N];
double Xp[N];
double buff[N];
double W1[N][N];
double f[1][1];
int alfa;

void X0();
void VvodUR();
double F1(double, double, double);
double F2(double, double, double);
double F3(double, double, double);
double w11(double);
double w12(double);
double w13(double);
double w21(double);
double w22(double);
double w23(double);
double w31(double);
double w32(double);
double w33(double);
void FW(int);
void PechMat();
void PoiPeres(int);
void ZamObr();
void NoviiX(int);

int main()
{
	setlocale(LC_ALL, "Russian");
	int q;
	cout << "Решение СНУ методом Ньютона" << endl;
	X0();
	VvodUR();
	cout << endl;
	/*cout << "Количество шагов: ";
	cin >> q;
	cout << endl;*/
	//for (int d = 0; d < q; d++)
	int d = -1;
	do {
		for (int j = 0; j < N; j++)
		{
			Xp[j] = X[j];
		}
		d++;
		FW(d);
		PechMat();
		cout << endl;
		ZamObr();
		cout << endl;
		NoviiX(d);
	} while ((abs(abs(Xp[0]) - abs(X[0])) > eps) || d < 1);
	return 0;
}

void X0()
{
	int j;
	for (j = 0; j < N; j++)
		X[j] = 1;
}

void VvodUR()
{
	cout << "f1 = x^2 + y^2 - z^2 - 1 = 0" << endl;
	cout << "f2 = 2x^2 + y^2 - 4z = 0" << endl;
	cout << "f3 = 3x^2 - 4y + z^2 = 0" << endl;
}

double F1(double x, double y, double z)
{
	double f1 = x * x + y * y - z * z - 1;
	return f1;
}
double F2(double x, double y, double z)
{
	double f2 = 2 * x*x + y * y - 4 * z;
	return f2;
}
double F3(double x, double y, double z)
{
	double f3 = 3 * x*x - 4 * y + z * z;
	return f3;
}

double w11(double x)
{
	return (2 * x);
}
double w12(double y)
{
	return (2 * y);
}
double w13(double z)
{
	return (2 * z);
}
double w21(double x)
{
	return (4 * x);
}
double w22(double y)
{
	return (2 * y);
}
double w23(double z)
{
	return (-4);
}
double w31(double x)
{
	return (6 * x);
}
double w32(double y)
{
	return ((-4) * y);
}
double w33(double z)
{
	return (2 * z);
}

void FW(int i)
{
	if (i != 0)
	{
		for (int p = 0; p < N; p++)
		{
			X[p] = Xp[p];
		}
	}
	cout << "Шаг " << i + 1 << " :" << endl;
	F[0] = F1(X[0], X[1], X[2]);
	F[1] = F2(X[0], X[1], X[2]);
	F[2] = F3(X[0], X[1], X[2]);
	cout << "F = (" ;
	for (int l = 0; l < N; l++)
		cout << setprecision(toch) << F[l] << "  ";
	cout << " )" << endl;
	cout << endl;

	W1[0][0] = w11(X[0]);
	W1[0][1] = w12(X[1]);
	W1[0][2] = w13(X[2]);
	W1[1][0] = w21(X[0]);
	W1[1][1] = w22(X[1]);
	W1[1][2] = w23(X[2]);
	W1[2][0] = w31(X[0]);
	W1[2][1] = w32(X[1]);
	W1[2][2] = w33(X[2]);
	cout << "Матрица произведений W :" << endl;
	for (int k = 0; k < N; k++)
	{
		for (int j = 0; j < N; j++)
			cout << setprecision(toch) << W1[k][j] << "\t";
		cout << endl;
	}
	
	for (int s = 0; s < N; s++)
	{
		for (int j = 0; j < N; j++)
			matrix[s][j] = W1[s][j];
		cout << endl;
	}
	for (int r = 0; r < N; r++)
		matrix[r][N] = F[r];
	cout << "СЛАУ WY=F :" << endl;
}

void PechMat()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N + 1; j++)
		{
			cout << setprecision(toch) << fixed << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

void PoiPeres(int i)
{
	for (int j = i; j < N; j++)
	{
		if (matrix[j][i] < 0)
		{
			buff[j] = (-1)*matrix[j][i];
		}
		else {
			buff[j] = matrix[j][i];
		}
	}
	double Maxbuff;
	int t;
	Maxbuff = buff[i];
	for (t = i; t < N; t++)
	{
		if (buff[t] >= Maxbuff)
		{
			Maxbuff = buff[t];
			alfa = t;
		}
	}
	if (alfa != i)
	{
		cout << "Обмен сроки " << i + 1 << " и строки " << alfa + 1 << endl;
		for (int k = i, z = i; k < N + 1, z < N + 1; k++, z++)
		{
			f[i][i] = matrix[i][z];
			matrix[i][z] = matrix[alfa][k];
			matrix[alfa][k] = f[i][i];
		}
		cout << endl;
		PechMat();
	}
}

void ZamObr()
{
	int i, j, k;
	double d;
	cout << "Решение методом Гаусса WY=F:" << endl;
	
	for (i = 0; i < N - 1; i++)
	{
		PoiPeres(i);
		for (j = i + 1; j < N; j++)
		{
			d = (matrix[j][i] / matrix[i][i]);
			cout << "C" << j + 1 << "-(C" << i + 1 << "*" << setprecision(toch) << d << ")" << endl;
			for (k = i; k < N + 1; k++)
				matrix[j][k] -= (matrix[i][k] * d);
		}
		cout << endl;
		PechMat();
	}
	cout << endl;
	cout << endl;
	
	otvet[N - 1] = matrix[N - 1][N] / matrix[N - 1][N - 1];
	for (i = N - 2; i >= 0; i--)
	{
		for (j = 0, d = 0; j < N - i - 1; j++)
			d += (otvet[N - j - 1] * matrix[i][N - j - 1] * (-1));
		otvet[i] = (matrix[i][N] + d) / matrix[i][i];
	}

	
	cout << "---------------------------------------------------------" << endl;
	for (i = 0; i < N; i++)
		cout << "Y" << i + 1 << "=" << setprecision(toch) << otvet[i] << endl;
}

void NoviiX(int i)
{
	cout << "Вектор Х на шаге " << i + 1 << endl;
	for (int j = 0; j < N; j++)
	{
		X[j] = X[j] - otvet[j];
		cout << setprecision(toch) << X[j] << "\t";
	}
	cout << endl;
	cout << "---------------------------------------------------------" << endl; 
	cout << "---------------------------------------------------------" << endl;
}


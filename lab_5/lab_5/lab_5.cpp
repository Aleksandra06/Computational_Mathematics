#include "pch.h"
#include <iostream>
#include <iomanip>

using namespace std;

const int n = 3;
const int toch = 4;
const double h = 0.2;
double P;
double X0 = 1.44;
double X[n + 1];

double f(double);

double l_composition_ch(int);
double l_composition_zn(int);
double lagrang();

double aitken();

double fact(int);
double newton();

int main()
{
	setlocale(LC_ALL, "Russian");
	X[0] = 1;
	for (int i = 1; i <= n; i++) {
		X[i] = X[i - 1] + h;
	}
	int flag;
	cout << "Интерполяция:" << endl;
	cout << "Лагранж/Эйткен/Ньютон (1/2/3) : ";
	cin >> flag;
	switch (flag) {
	case 1:
		cout << "P(" << X0 << ")=" << lagrang() << endl;
		cout << "eps=" << abs(abs(f(X0)) - abs(lagrang()));
		break;
	case 2:
		cout << "eps=" << abs(abs(f(X0)) - abs(aitken()));
		break;
	case 3:
		cout << "eps=" << newton() << endl;
		break;
	}
		system("pause");
	return 0;
}

double f(double a) {
	return 1 / a;
}

double l_composition_ch(int i) {
	double otvet = 1;
	for (int j = 0; j < i; j++) {
		otvet = otvet * (X0 - X[j]);
	}
	for (int j = i + 1; j <= n; j++) {
		otvet = otvet * (X0 - X[j]);
	}
	return otvet;
}

double l_composition_zn(int i) {
	double otvet = 1;
	for (int j = 0; j < i; j++) {
		otvet = otvet * (X[i] - X[j]);
	}
	for (int j = i + 1; j <= n; j++) {
		otvet = otvet * (X[i] - X[j]);
	}
	return otvet;
}

double lagrang() {
	P = 0;
	for (int i = 0; i <= n; i++) {
		P = P + f(X[i])*l_composition_ch(i) / l_composition_zn(i);
	}
	return P;
}

double aitken() {
	double Px[n + 1];
	for (int i = 0; i <= n; i++) {
		Px[i] = f(X[i]);
		cout << "Px" << i << "(" << X0 << ") = " << Px[i] << endl;
	}
	cout << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n - i; j++) {
			Px[j] = (Px[j] * (X0 - X[j + i]) - Px[j + 1] * (X0 - X[j])) / (X[j] - X[j + i]);
			cout << "Px" << j << "(" << X0 << ") = " << Px[j] << endl;
		}
		cout << endl;
	}
	P = Px[0];
	return Px[0];
}

double fact(int a) {
	if (a == 0) return 1;
	else {
		int otvet = 1;
		for (int i = 1; i <= a; i++)
			otvet = otvet * a;
		return otvet;
	}
}

double newton() {
	double dy[n][n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dy[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		dy[i][0] = f(X[i + 1]) - f(X[i]);
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			dy[j][i] = dy[j + 1][i - 1] - dy[j][i - 1];
		}
	}
	for (int i = 0; i <= n; i++)
		cout << "y" << i << "d\t";
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << setprecision(toch) << fixed << f(X[i]) << "\t";
		for (int j = 0; j < n - i; j++) {
			cout << setprecision(toch) << fixed << dy[i][j] << "\t";
		}
		cout << endl;
	}
	///вторая формула
	P = 0;
	double q, tmp;
	q = (X0 - X[n]) / h;
	cout << "q=" << q << endl;
	tmp = q;
	for (int i = 0; i < n; i++) {
		P = P + dy[n - (i + 1)][i] / fact(i + 1) * tmp;
		tmp = tmp * (q + (i - 1));
	}
	P = f(X[n]) + P;
	cout << "P(" << X0 << ")=" << P << endl;
	double eps;
	eps = dy[0][n - 1] / fact(n + 1) * tmp * (q - n);
	return eps;
}
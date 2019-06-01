#include "pch.h"
#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

const double eps = 0.00000001;
const double Y = 1;
const double Yp = 1;
const double H = 0.2;
const double a = 0;
const double b = 1;

double fpp(double, double, double);
double f(double x, double y, double z);
double g(double x, double y, double z);
double RK4(double h, int range, double yy[], double z0);
double RK4DP(double m);
double RK2t(double h, int range, double yy[], double z0);
double RK2tDP();

int main()
{
	setlocale(LC_ALL, "Russian");
	int flag = 10;
	while (flag != 0) {
		system("cls");
		cout << "0)Выход\n1) Рунге-Кутта 2 порядка с усреднением по времени\n2) Рунге - Кутта 4 порядка\n" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Метод: ";
		cin >> flag;
		switch (flag)
		{
		case 1:
			RK2tDP();
			_getch();
			break;
		case 2:
			RK4DP(Yp);
			_getch();
			break;
		default:
			break;
		}
	}
	return 0;
}

const int r = 0;

double fpp(double x, double y, double yp) {
	return (double)(exp(x) + y) / 2;
}

double RK2t(double h, int r, double yy[], double z0) {
	double xc = a, yc = Y, zc = z0, y1c = 1, k1, k2, k4, k3, k11, k22, k44, k33;
	for (int i = 0; i < r; i++) {
		printf("%0.8f\t%0.8f\t%0.8f\t\n", xc, y1c, zc);
		yy[i] = yc + (double)h / 2 * zc;
		zc = zc + (double)h / 2 * fpp(xc + h / 2.0, yc, zc);
		yc = y1c;
		xc += h;
	}
	printf("%0.8f\t%0.8f\t%0.8f\t\n", xc, y1c, zc);
	return y1c;
}

double RK2tDP() {
	int r, R;
	double xn = b, x0 = a, m = Yp;
	double *yy, *YY;
	double H = 0.2, h = H / 2;
	cout << "       X\t\tY\t\tY'" << endl;
	double result;
	do {
		R = (int)((xn - x0) / h);
		r = (int)((xn - x0) / H);
		YY = new double[r];
		cout << "H = " << H << endl;
		RK4(H, r, YY, m);
		yy = new double[R];
		cout << "h = " << h << endl;
		result = RK4(h, R, yy, m);
		cout << endl;
		h *= 0.5;
		H = 2 * h;
	} while (abs(yy[R - 1] - YY[r - 1]) > eps);
	h = 0.1; H = 2 * h;
	return result;
}

double RK4DP(double m) {
	int r, R;
	double xn = b, x0 = a;
	double *yy, *YY; 
	double H = 0.2, h = H / 2;
	cout << "       X\t\tY\t\tY'" << endl;
	double result;
	do {
		R = (int)((xn - x0) / h);
		r = (int)((xn - x0) / H);
		YY = new double[r];
		cout << "H = " << H << endl;
		RK4(H, r, YY, m);
		yy = new double[R];
		cout << "h = " << h << endl;
		result = RK4(h, R, yy, m);
		cout << endl;
		h *= 0.5;
		H = 2 * h;
	} while (abs(yy[R - 1] - YY[r - 1]) > eps);
	h = 0.1; H = 2 * h;
	return result;
}

double f(double x, double y, double z) {
	double result = (exp(x) + y) / 2;
	return result;
}

double g(double x, double y, double z) {
	return (z);
}

double RK4(double h, int r, double yy[], double z0) {
	double xc = a, yc = Y, zc = z0, y1c = 1, k1, k2, k4, k3, k11, k22, k44, k33;
	for (int i = 0; i < r; i++) {
		printf("%0.8f\t%0.8f\t%0.8f\t\n", xc, y1c, zc);
		k1 = h * f(xc, yc, zc);
		k11 = h * g(xc, yc, zc);
		k2 = h * f(xc + h / 2.0, yc + k11 / 2.0, zc + k1 / 2.0);
		k22 = h * g(xc + h / 2.0, yc + k11 / 2.0, zc + k1 / 2.0);
		k3 = h * f(xc + h / 2.0, yc + k22 / 2.0, zc + k2 / 2.0);
		k33 = h * g(xc + h / 2.0, yc + k22 / 2.0, zc + k2 / 2.0);
		k4 = h * f(xc + h, yc + k33, zc + k3);
		k44 = h * g(xc + h, yc + k33, zc + k3);
		zc = zc + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;//y'
		yy[i] = y1c = yc + (k11 + 2.0 * k22 + 2.0 * k33 + k44) / 6.0;//y
		yc = y1c;
		xc += h;
	}
	printf("%0.8f\t%0.8f\t%0.8f\t\n", xc, y1c, zc);
	return y1c;
}
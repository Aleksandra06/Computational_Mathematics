#include "pch.h"
#include <iostream>

using namespace std;

double x0 = 0, xn = 1, yo = 0, z0 = 0.7, yk = 1;
double m1 = z0, m2 = 1.2, m3, H = 0.2, h = H/2;
double *yy, *YY, shot1, shot2, shot, eps = 0.00000001;


double f(double x, double y, double z);
double g(double x, double y, double z);
double RK4(double h, int range, double yy[], double z0);
double RK4DP(double m);
void shooting();

int main() {
	setlocale(LC_ALL, "Russian");
	shooting();
	system("pause");
	return 0;
}

double f(double x, double y, double z) {
	double result = (exp(x) + z);
	return result;
}

double g(double x, double y, double z) {
	return (z);
}

void shooting() {
	shot1 = RK4DP(m1);
	shot2 = RK4DP(m2);
	if (abs(shot1 - yk) < eps) printf("y подсчитан, shot1: %0.8f", shot1);
	else if (abs(shot2 - yk) < eps) printf("y подсчитан, shot2: %0.8f", shot2);
	else {
		m3 = m2 + (((m2 - m1) * (yk - shot2)) / ((shot2 - shot1)));
		shot = RK4DP(m3);
	}
	while (abs(shot - yk) >= eps) {
		m1 = m2;
		m2 = m3;
		shot1 = shot2;
		shot2 = shot;
		m3 = m2 + (((m2 - m1) * (yk - shot2)) / ((shot2 - shot1)));
		z0 = m3;
		shot = RK4DP(m3);
	} 
	printf("y подсчитан, shot: %0.8f, m3 = %0.8f", shot, m3);
}

double RK4DP(double m) {
	int r, R;
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

double RK4(double h, int r, double yy[], double z0) {
	double xc = x0, yc = yo, zc = z0, y1c = 1, k1, k2, k4, k3, k11, k22, k44, k33;
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

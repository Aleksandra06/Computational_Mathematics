#include "pch.h"
#include <iostream>

using namespace std;

const double H = 0.1;
const double eps = 0.0001;
double a = 1;
double b = 2;

double f(double);
double f3(double);
double f5(double);
double trapeze(double, double, double);
double trapeze_toch_ucech(double, double, double);
double trapeze_toch_okr(double, double);
double simpson(double, double, double);
double simpson_toch_ucech(double, double, double);
double simpson_toch_okr(double, double);

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Трапеции: " << endl;
	double t2 = trapeze(a, b, H);
	double t1 = 0;
	double h = H;
	double tmp;
	int i = 2;
	cout << "Шаг 1" << endl;
	cout << "I = " << t2 << endl;
	cout << "h = " << h << endl;
	do {
		tmp = t2;
		t2 = t1;
		t1 = tmp;
		h = h / 2;
		t2 = trapeze(a, b, h);
		cout << "Шаг " << i << endl;
		i++;
		cout << "I = " << t2 << endl;
		cout << "h = " << h << endl;
	} while (abs(t1 - t2) > 3*eps);
	cout << "Eусеч <= " << trapeze_toch_ucech(a, b, h) << endl;
	cout << "Eокр <= " << trapeze_toch_okr(a, b) << endl;

	cout << endl;
	h = H;
	cout << "Симпсона: " << endl;
	i = 2;
	t2 = simpson(a, b, H);
	cout << "Шаг 1" << endl;
	cout << "I = " << t2 << endl;
	cout << "h = " << h << endl;
	do {
		tmp = t2;
		t2 = t1;
		t1 = tmp;
		h = h / 2;
		t2 = simpson(a, b, h);
		cout << "Шаг " << i << endl;
		i++;
		cout << "I = " << t2 << endl;
		cout << "h = " << h << endl;
	} while (abs(t1 - t2) > 3*eps);
	cout << "Eусеч <= " << simpson_toch_ucech(a, b, h) << endl;
	cout << "Eокр <= " << simpson_toch_okr(a, b) << endl;
	return 0;
}

double f(double a) {
	return (double) 1 / a;
}

double f3(double a) {
	return (double)(0 - 6) / pow(a, 4);
}

double f5(double a) {
	return (double)(0 - 120) / pow(a, 6);
}

double trapeze(double a, double b, double h) {
	double otv = 0;
	int ld = (b - a) / h + 1;
	for (int i = 1; i <= ld; i++) {
		otv += f(a + h * (i + 1));
	}
	otv += (f(a) + f(b)) / 2;
	otv = otv * h;
	return otv;
}

double trapeze_toch_ucech(double a, double b, double h) {
	double toch = 0, M;
	M = f(a);
	int ld = (b - a) / h + 1;
	for (int i = 1; i <= ld; i++) {
		if (M < f3(a+h*(i+1))) M = f3(a + h * (i + 1));
	}
	toch = pow(h, 2) / 12 * (b - a)*M;
	return toch;
}

double trapeze_toch_okr(double a, double b) {
	return (double)1 / 2 * (b - a)*(f(a) + f(b));
}

double simpson(double a, double b, double h) {
	double otv = 0;
	double tmp = 0;
	for (double i = a + h; i < b; i += (2 * h)) {
		tmp += f(i);
	}
	otv = f(a) + f(b) + 4 * tmp;
	tmp = 0;
	for (double i = a + (2 * h); i < b; i += (2 * h)) {
		tmp += f(i);
	}
	otv = (otv + (2 * tmp)) * h / 3;
	return otv;
}

double simpson_toch_ucech(double a, double b, double h) {
	double toch = 0, M;
	M = f(a);
	for (double i = a + h; i <= b; i += h) {
		if (M < f5(i)) M = f5(i);
	}
	toch = pow(h, 4) / 180 * (b - a) * M;
	return toch;
}

double simpson_toch_okr(double a, double b) {
	return (double)1 / 2 * (b - a)*(f(a) + f(b));
}
#include "pch.h"
#include <iostream>

using namespace std;

double eps = 0.01;

double fun(double);
double bissection(double, double);
double hord(double, double);
double funp(double);
double newton(double, double);

int main() {
	setlocale(LC_ALL, "Russian");
	//данные
	double a, b;
	cout << "Введите интервал: ";
	cin >> a;
	cin >> b;
	cout << endl;
	/*cout << "eps=";
	cin >> eps;
	cout << endl;*/
	if ((fun(a)*fun(b) >= 0) || (a > b)) {
		cout << "Некорректен интервал";
		exit(1);
	}
	//
	int flag;
	cout << "Биссекций/Хорд/Ньютона (1/2/3): ";
	cin >> flag;
	switch (flag) {
	case 1: //биссекций
		cout << "Ответ: " << bissection(a, b);
		break;
	case 2: //хорд
		cout << "Ответ: " << hord(a, b);
		break;
	case 3: //Ньютона
		cout << "Ответ: " << newton(a, b);
		break;
	}
	system("PAUSE");
	return 0;
}

double fun(double x) {
	return x * x - 2;
}

double bissection(double a, double b) {
	double c;
	int f = 0;
	do {
		f++;
		cout << "Шаг " << f << endl;
		c = (a + b) / 2;
		/*cout << "a=" << a << endl;
		cout << "b=" << b << endl;*/
		cout << "(" << a << "; " << b << ")" << endl;
		cout << "c=" << c << endl;
		cout << "f(a)*f(c) = " << fun(a)*fun(c) << endl;
		cout << "f(c)*f(b) = " << fun(c)*fun(b) << endl << endl;
		if (fun(a)*fun(c) < 0) b = c;
		else
			a = c;
	} while (abs((abs(b) - abs(a)) / 2) > eps);
	return (a + b) / 2;
}

double hord(double a, double b) {
	double x, x_last;
	int f = 1;
	x = a - fun(a)*(b - a) / (fun(b) - fun(a));
	cout << "x(" << f << ")=" << x << endl;
	do {
		f++;
		x_last = x;
		x = x_last - fun(x_last)*(b - x_last) / (fun(b) - fun(x_last));
		cout << "x(" << f << ")=" << x << endl;
		cout << "eps = " << abs(x_last - x) << endl;
	} while (abs(x_last-x) > eps);
	return x;
}

double funp(double x) {
	return 2 * x;
}

double newton(double a, double b) {
	double lastX;
	double x;
	int f = 1;
	x = 2;
	cout << "x(" << f << ")=" << x << endl;
	do {
		f++;
		lastX = x;
		x = lastX - (fun(lastX) / funp(lastX));
		cout << "x(" << f << ")=" << x << endl;
	} while (abs(lastX - x) > eps);
	return x;
}
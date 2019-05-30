#include "pch.h"
#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

const double eps = 0.00001;
const double Y = 1;
const double Yp = 1;
const double H = 0.2;
const double a = 0;
const double b = 1;

double fpp(double, double, double);
void euler();
void RK2t();
void RK2p();
void RK4();
void milna();

int main()
{
	setlocale(LC_ALL, "Russian");
	int flag = 10;
	while (flag != 0) {
		system("cls");
		cout << "0)Выход\n1) Эйлер \n2) Рунге-Кутта 2 порядка с усреднением по времени\n3) Рунге-Кутта 2 порядка с усреднением по произвоной\n4) Рунге - Кутта 4 порядка\n5) Милна" << endl;
		cout << "-------------------------------------------------------" << endl;
		cout << "Метод: ";
		cin >> flag;
		switch (flag)
		{
		/*case 1:
			euler();
			_getch();
			break;*/
		case 2:
			RK2t();
			_getch();
			break;
		case 3:
			RK2p();
			_getch();
			break;
		case 4:
			RK4();
			_getch();
			break;
		/*case 5:
			milna();
			_getch();
			break;*/
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

void euler() {
	double **f, **fl;
	f = new double*[2];
	fl = new double*[2];
	double x = a;
	double y = Y;
	double yp = Yp;
	double h = H;
	bool toch = 1;
	int k = (int)(abs(b - a) / h) + r;
	for (int j = 0; j < 2; j++) {
		f[j] = new double[k];
		fl[j] = new double[k];
	}
	for (int j = 0; j < k; j++) {
		f[0][j] = y + h * yp;
		f[1][j] = yp + h * fpp(x, y, yp);
		y = f[0][j];
		yp = f[1][j];
		x += h;
	}
	int i = 1;
	do {
		cout << endl;
		//cout << "Шаг " << i << endl;
		//cout << "h = " << h << endl;
		printf("%0.8f\t\t%0.8f\t\t%0.8f\n\n", a + h, f[0][k - 1], f[1][k - 1]);
		i++;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			delete[] fl[j];
		}
		for (int j = 0; j < 2; j++) {
			fl[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fl[0][j] = f[0][j];
			fl[1][j] = f[1][j];
		}
		for (int j = 0; j < 2; j++) {
			delete[]f[j];
		}
		h = h / 2;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			f[j] = new double[k];
		}
		x = a;
		y = Y;
		yp = Yp;
		for (int j = 0; j < k; j++) {
			f[0][j] = y + h * yp;
			f[1][j] = yp + h * fpp(x, y, yp);
			y = f[0][j];
			yp = f[1][j];
			//printf("%0.8f\t\t%0.8f\t\t%0.8f\n\n", x, f[0][k - 1], f[1][k - 1]);
			x += h;
		}
		//k = (int)(abs(b - a) / (h * 2)) + r;
		//cout << "Y(h)=(" << fl[0][k - 1] << "," << fl[1][k - 1] << ")" << endl;
		//k = (int)(abs(b - a) / h) + r;
		//cout << "Y(h/2)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;
		k = (int)(abs(b - a) / (h * 2)) + r;
		for (int j = 1; j < k; j++) {
			if (abs(f[0][2 * j] - fl[0][j]) <= 3 * eps) toch = 0;
			else toch = 1;
		}
	} while (abs(f[0][2 * k - 1] - fl[0][k - 1]) > 3 * eps);
}

void RK2t() {
	double **f, **fl, **fz;
	f = new double*[2];
	fl = new double*[2];
	fz = new double*[2];
	double x = a;
	double y = Y;
	double yp = Yp;
	double h = H;
	bool toch = 1;
	int k = (int)(abs(b - a) / h) + r;
	for (int j = 0; j < 2; j++) {
		f[j] = new double[k];
		fl[j] = new double[k];
		fz[j] = new double[k];
	}
	for (int j = 0; j < k; j++) {
		fz[0][j] = y + (double)h / 2 * yp;
		fz[1][j] = yp + (double)h / 2 * fpp(x, y, yp);
		f[0][j] = y + h * fz[1][j];
		f[1][j] = yp + h * fpp(x + (double)h / 2, fz[0][j], fz[1][j]);
		y = f[0][j];
		yp = f[1][j];
		x += h;
	}
	int i = 1;
	do {
		cout << endl;
		//cout << "Шаг " << i << endl;
		//cout << "h = " << h << endl;
		k = (int)(abs(b - a) / h) + r;
		//cout << "Yz(h)=(" << fz[0][k - 1] << "," << fz[1][k - 1] << ")" << endl;
		//cout << "Y(h)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;
		//printf("%0.10f\t\t%0.10f\t\t%0.10f\n\n", a + h, f[0][k - 1], f[1][k - 1]);
		i++;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			delete[] fl[j];
		}
		for (int j = 0; j < 2; j++) {
			fl[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fl[0][j] = f[0][j];
			fl[1][j] = f[1][j];
		}
		for (int j = 0; j < 2; j++) {
			delete[]f[j];
			delete[]fz[j];
		}
		h = h / 2;
		x = a;
		y = Y;
		yp = Yp;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			f[j] = new double[k];
			fz[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fz[0][j] = y + (double)h / 2 * yp;
			fz[1][j] = yp + (double)h / 2 * fpp(x, y, yp);
			f[0][j] = y + h * fz[1][j];
			f[1][j] = yp + h * fpp(x + (double)h / 2, fz[0][j], fz[1][j]);
			y = f[0][j];
			yp = f[1][j];
			/*if (x > 0.99670)
				printf("1\t\t%0.10f\t\t%0.10f\n\n", f[0][j], f[1][j]);
			else*/
				printf("%0.10f\t\t%0.10f\t\t%0.10f\n\n", x, f[0][j], f[1][j]);
			x += h;
		}
		/*cout << "Yz(h/2)=(" << fz[0][k - 1] << "," << fz[1][k - 1] << ")" << endl;
		cout << "Y(h/2)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;*/
		k = (int)(abs(b - a) / (h * 2)) + r;
		for (int j = 1; j < k; j++) {
			if (abs(f[0][2 * j] - fl[0][j]) <= 3 * eps) toch = 0;
			else toch = 1;
		}
	} while (abs(f[0][2 * k - 1] - fl[0][k - 1]) > 3 * eps);
}

void RK2p() {
	double **f, **fl, **fz;
	f = new double*[2];
	fl = new double*[2];
	fz = new double*[2];
	double x = a;
	double y = Y;
	double yp = Yp;
	double h = H;
	bool toch = 1;
	int k = (int)(abs(b - a) / h) + r;
	for (int j = 0; j < 2; j++) {
		f[j] = new double[k];
		fl[j] = new double[k];
		fz[j] = new double[k];
	}
	for (int j = 0; j < k; j++) {
		fz[0][j] = y + (double)h / 2 * yp;
		fz[1][j] = yp + (double)h / 2 * fpp(x, y, yp);
		f[0][j] = y + (double)h / 2 * (yp + fz[1][j]);
		f[1][j] = yp + (double)h/2*(fpp(x, y, yp) + fpp(x + h, fz[0][j], fz[1][j]));
		y = f[0][j];
		yp = f[1][j];
		x += h;
	}
	int i = 1;
	do {
		cout << endl;
		///cout << "Шаг " << i << endl;
		//cout << "h = " << h << endl;
		k = (int)(abs(b - a) / h) + r;
		//cout << "Yz(h)=(" << fz[0][k - 1] << "," << fz[1][k - 1] << ")" << endl;
		//cout << "Y(h)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;
		//printf("%0.10f\t\t%0.10f\t\t%0.10f\n\n", a + h, f[0][k - 1], f[1][k - 1]);
		i++;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			delete[] fl[j];
		}
		for (int j = 0; j < 2; j++) {
			fl[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fl[0][j] = f[0][j];
			fl[1][j] = f[1][j];
		}
		for (int j = 0; j < 2; j++) {
			delete[]f[j];
			delete[]fz[j];
		}
		h = h / 2;
		x = a;
		y = Y;
		yp = Yp;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			f[j] = new double[k];
			fz[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fz[0][j] = y + (double)h / 2 * yp;
			fz[1][j] = yp + (double)h / 2 * fpp(x, y, yp);
			f[0][j] = y + (double)h / 2 * (yp + fz[1][j]);
			f[1][j] = yp + (double)h / 2 * (fpp(x, y, yp) + fpp(x + h, fz[0][j], fz[1][j]));
			y = f[0][j];
			yp = f[1][j];
			//printf("%0.10f\t\t%0.10f\t\t%0.10f\n\n", x, f[0][j], f[1][j]);
			x += h;
		}
		//cout << "Yz(h/2)=(" << fz[0][k - 1] << "," << fz[1][k - 1] << ")" << endl;
		//cout << "Y(h/2)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;
		k = (int)(abs(b - a) / (h * 2)) + r;
		for (int j = 1; j < k; j++) {
			if (abs(f[0][2 * j] - fl[0][j]) <= 3 * eps) toch = 0;
			else toch = 1;
		}
	} while (abs(f[0][2 * k - 1] - fl[0][k - 1]) > 3 * eps);
}

void RK4() {
	double **f, **fl;
	f = new double*[2];
	fl = new double*[2];
	double x = a;
	double y = Y;
	double yp = Yp;
	double h = H;
	double k1[2], k2[2], k3[2], k4[2];
	bool toch = 1;
	int k = (int)(abs(b - a) / h) + r;
	for (int j = 0; j < 2; j++) {
		f[j] = new double[k];
		fl[j] = new double[k];
	}
	for (int j = 0; j < k; j++) {
		k1[0] = yp;
		k1[1] = fpp(x, y, yp);
		k2[0] = yp + (double)h / 2 * k1[1];
		k2[1] = fpp(x + (double)h / 2, y + (double)h / 2 * k1[0], yp + (double)h / 2 * k1[1]);
		k3[0] = yp + (double)h / 2 * k2[1];
		k3[1] = fpp(x + (double)h / 2, y + (double)h / 2 * k2[0], yp + (double)h / 2 * k2[1]);
		k4[0] = yp + h * k3[1];
		k4[1] = fpp(x + h, y + h * k3[0], yp + h * k3[1]);
		f[0][j] = y + (double)h / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);
		f[1][j] = yp + (double)h / 6 * (k1[1] + 2 * k2[1] + 2 * k3[0] + k4[1]);
		y = f[0][j];
		yp = f[1][j];
		x += h;
	}
	int i = 1;
	do {
		cout << endl;
		//cout << "Шаг " << i << endl;
		///cout << "h = " << h << endl;
		k = (int)(abs(b - a) / h) + r;
		/*cout << "k(1)=(" << k1[0] << "," << k1[1] << ")" << endl;
		cout << "k(2)=(" << k2[0] << "," << k2[1] << ")" << endl;
		cout << "k(3)=(" << k3[0] << "," << k3[1] << ")" << endl;
		cout << "k(4)=(" << k4[0] << "," << k4[1] << ")" << endl;
		cout << "Y(h)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;*/
		printf("%0.10f\t\t%0.10f\t\t%0.10f\n\n", a + h, f[0][k - 1], f[1][k - 1]);
		i++;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			delete[] fl[j];
		}
		for (int j = 0; j < 2; j++) {
			fl[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fl[0][j] = f[0][j];
			fl[1][j] = f[1][j];
		}
		for (int j = 0; j < 2; j++) {
			delete[]f[j];
		}
		h = h / 2;
		x = a;
		y = Y;
		yp = Yp;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			f[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			k1[0] = yp;
			k1[1] = fpp(x, y, yp);
			k2[0] = yp + (double)h / 2 * k1[1];
			k2[1] = fpp(x + (double)h / 2, y + (double)h / 2 * k1[0], yp + (double)h / 2 * k1[1]);
			k3[0] = yp + (double)h / 2 * k2[1];
			k3[1] = fpp(x + (double)h / 2, y + (double)h / 2 * k2[0], yp + (double)h / 2 * k2[1]);
			k4[0] = yp + h * k3[1];
			k4[1] = fpp(x + h, y + h * k3[0], yp + h * k3[1]);
			f[0][j] = y + (double)h / 6 * (k1[0] + 2 * k2[0] + 2 * k3[0] + k4[0]);
			f[1][j] = yp + (double)h / 6 * (k1[1] + 2 * k2[1] + 2 * k3[0] + k4[1]);
			y = f[0][j];
			yp = f[1][j];
			printf("%0.10f\t\t%0.10f\t\t%0.10f\n\n", x, f[0][j], f[1][j]);
			x += h;
		}
		k = (int)(abs(b - a) / (h * 2)) + r;
		/*cout << "k(1)=(" << k1[0] << "," << k1[1] << ")" << endl;
		cout << "k(2)=(" << k2[0] << "," << k2[1] << ")" << endl;
		cout << "k(3)=(" << k3[0] << "," << k3[1] << ")" << endl;
		cout << "k(4)=(" << k4[0] << "," << k4[1] << ")" << endl;
		cout << "Y(h/2)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;*/
		/*for (int j = 1; j < k; j++) {
			if (abs(f[0][2 * j] - fl[0][j]) <= 15 * eps) toch = 0;
			else toch = 1;
		}*/
	} while (abs(f[0][2 * k - 1] - fl[0][k-1]) > 15 * eps);
}

void milna() {
	double **f, **fl, *fz;;
	f = new double*[2];
	fl = new double*[2];
	fz = new double[2];
	double x = a;
	double y = Y;
	double yp = Yp;
	double h = H;
	bool toch = 1;
	int k = (int)(abs(b - a) / h) + r;
	for (int j = 0; j < 2; j++) {
		f[j] = new double[k];
		fl[j] = new double[k];
	}
	for (int j = 0; j < 3; j++) {
		f[0][j] = y + h * yp;
		f[1][j] = yp + h * fpp(x, y, yp);
		y = f[0][j];
		yp = f[1][j];
		x  = x+ h;
		//cout << "Yh(" << j + 1 << ")=(" << f[0][j] << "," << f[1][j] << ")" << endl;
	}
	for (int j = 2; j < k - 1; j++) {
		fz[0] = f[0][j - 2] + 4 * (double)h / 3 * (2 * f[1][j - 2] - f[1][j - 1] + 2 * f[1][j]);
		fz[1] = f[1][j - 2] + 4 * (double)h / 3 * (2 * fpp(x - 2 * h, f[0][j - 2], f[1][j - 2]) - fpp(x - 2 * h, f[0][j - 1], f[1][j - 1]) + 2 * fpp(x - h, f[0][j], f[1][j]));
		f[0][j + 1] = f[0][j - 1] + (double)h / 3 * (f[1][j - 1] - 4 * f[1][j] + fz[1]);
		f[1][j + 1] = f[1][j - 1] + (double)h / 3 * (fpp(x - 1 * h, f[0][j - 1], f[1][j - 1]) - 4 * fpp(x - 1 * h, f[0][j], f[1][j]) + fpp(x + h, fz[0], fz[1]));
		y = f[0][j];
		yp = f[1][j];
		//printf("%0.8f       %0.8f       %0.8f\n\n", x, f[0][k - 1], f[1][k - 1]);
		//cout << x << "\t\t" << f[0][k - 1] << "\t\t" << f[1][k - 1] << endl;
		x =x+h;

		//cout << "!!!" << x << endl;/*
		//cout << "Yh(" << j + 2 << ")=(" << f[0][j] << "," << f[1][j] << ")" << endl;*/
	}

	int i = 1;
	do {
		cout << endl;
		//cout << "Шаг " << i << endl;
		//cout << "h = " << h << endl;
		k = (int)(abs(b - a) / h) + r;
		//cout << "Y(h)=(" << f[0][k - 1] << "," << f[1][k - 1] << ")" << endl;
		//cout << x << "\t\t" << f[0][k - 1] << "\t\t" << f[1][k - 1] << endl;
		//printf("%0.8f\t\t%0.8f\t\t%0.8f\n", x, f[0][k - 1], f[1][k - 1]);
		printf("%0.8f\t\t%0.8f\t\t%0.8f\n\n", a + h, f[0][k - 1], f[1][k - 1]);
		i++;
		for (int j = 0; j < 2; j++) {
			delete[] fl[j];
		}
		for (int j = 0; j < 2; j++) {
			fl[j] = new double[k];
		}
		for (int j = 0; j < k; j++) {
			fl[0][j] = f[0][j];
			fl[1][j] = f[1][j];
		}
		for (int j = 0; j < 2; j++) {
			delete[]f[j];
		}
		h = h / 2;
		x = a;
		y = Y;
		yp = Yp;
		k = (int)(abs(b - a) / h) + r;
		for (int j = 0; j < 2; j++) {
			f[j] = new double[k];
		}
		for (int j = 0; j < 3; j++) {
			f[0][j] = y + h * yp;
			f[1][j] = yp + h * fpp(x, y, yp);
			y = f[0][j];
			yp = f[1][j];
			x = x + h;
			//cout << "Yh(" << j + 1 << ")=(" << f[0][j] << "," << f[1][j] << ")" << endl;
		}
		for (int j = 2; j < k - 1; j++) {

			fz[0] = f[0][j - 2] + 4 * (double)h / 3 * (2 * f[1][j - 2] - f[1][j - 1] + 2 * f[1][j]);
			fz[1] = f[1][j - 2] + 4 * (double)h / 3 * (2 * fpp(x - 2 * h, f[0][j - 2], f[1][j - 2]) - fpp(x - 2 * h, f[0][j - 1], f[1][j - 1]) + 2 * fpp(x - h, f[0][j], f[1][j]));
			f[0][j + 1] = f[0][j - 1] + (double)h / 3 * (f[1][j - 1] - 4 * f[1][j] + fz[1]);
			f[1][j + 1] = f[1][j - 1] + (double)h / 3 * (fpp(x - 1 * h, f[0][j - 1], f[1][j - 1]) - 4 * fpp(x - 1 * h, f[0][j], f[1][j]) + fpp(x + h, fz[0], fz[1]));
			y = f[0][j];
			yp = f[1][j];
			//printf("%0.8f\t\t%0.8f\t\t%0.8f\n\n", x, f[0][k - 1], f[1][k - 1]);
			//cout << x << "\t\t" << f[0][k - 1] << "\t\t" << f[1][k - 1] << endl;
			x =x+ h;/*
			cout << "Yh(" << j + 2 << ")=(" << f[0][j] << "," << f[1][j] << ")" << endl;*/

		}
		k = (int)(abs(b - a) / (h * 2)) + r;
		//cout << "Y(h/2)=(" << f[0][k-1] << "," << f[1][k-1] << ")" << endl;
		for (int j = 1; j < k; j++) {
			if (abs(f[0][2 * j] - fl[0][j]) <= 3 * eps) toch = 0;
			else toch = 1;
		}
	} while (abs(f[0][2 * k - 1] - fl[0][k - 1]) > 15 * eps);
}
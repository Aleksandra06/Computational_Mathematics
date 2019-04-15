#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <math.h>

using namespace std;

int M, N;//кол-во строк и столбцов
const double eps = 0.001;
double **matrix;
double **A;
double **C;
double *B;
double *Cx;
double *Cx1;
double *Cx2;
double BeskNormB;
double BeskNormC;

void look(double **, int a, int b);
void build_A();
void build_B();
void build_C();
double calc_BeskNormB();
double calc_BeskNormC();
double Kolchshag();
int iter(double **);
void CX(double *, double **, int);

void Zeidel(double **, int );

int main() {
	setlocale(LC_ALL, "Russian");
	//считывание из файла//
	ifstream file;
	file.open("matrix.txt");
	if (file.eof()) {
		cout << "Ошибка чтения файла";
		return 0;
	}
	file >> M;//число строк
	N = M + 1;//число столбцов
	matrix = new double*[N];
	int tmp;
	for (int i = 0; i < N; i++) {
		matrix[i] = new double[M];
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (file.eof()) {
				cout << "Ошибка чтения файла";
				return 0;
			}
			file >> tmp;
			matrix[j][i] = (int)tmp;
		}
	}
	file.close();
	look(matrix, M, N);
	cout << endl;
	//
	cout << "Матрица А:" << endl;
	A = new double*[N];
	for (int i = 0; i < M; i++) {
		A[i] = new double[M];
	}
	build_A();
	look(A, M, M);
	cout << endl;
	cout << " Матрица В:" << endl;
	B = new double[M];
	build_B();
	cout << endl;
	cout << " Матрица C:" << endl;
	C = new double*[N];
	for (int i = 0; i < M; i++) {
		C[i] = new double[M];
	}
	build_C();
	look(C, M, M);
	cout << endl;
	//
	BeskNormB = calc_BeskNormB();
	BeskNormC = calc_BeskNormC();
	cout << "||B|| = " << BeskNormB << endl;
	cout << "||C|| = " << BeskNormC << endl;
	double n;
	n = Kolchshag();
	cout << "Количество шагов: " << n << endl;
	cout << "Для точности: " << eps << endl;
	//
	int k;
	k = (int)n + 1;
	int fl;
	cout << "МПИ/Зейделя (0/1): ";
	cin >> fl;

	double **X;
	switch (fl) {
	case 0:
		X = new double*[M];
		for (int i = 0; i < M; i++) {
			X[i] = new double[k + 1];
		}
		for (int i = 0; i < M; i++) {
			X[i][0] = 0;
		}
		k = iter(X);

		for (int i = 0; i < k; i++) {
			cout << "X" << i << "= ( ";
			for (int j = 0; j < M; j++) {
				cout << "\t" << X[j][i];
			}
			cout << " )" << endl;
		}
		break;
	case 1:
		X = new double*[M];
		for (int i = 0; i < M; i++) {
			X[i] = new double[k + 1];
		}
		Cx1 = new double[M];
		Cx2 = new double[M];
		Cx = new double[M];
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < k + 1; j++)
				X[i][j] = 0;
		}
		int i = 0;
		do {
			i++;
			Zeidel(X, i);
			cout << "Шаг " << i << " :" << endl;
			for (int t = 0; t < M; t++) {
				cout << "X[" << t + 1 << "]= " << X[t][i] << endl;
			}
		} while (abs(abs(X[0][i]) - abs(X[0][i - 1])) > eps);
		break;
	}
	system("PAUSE");
	return 0;
}


void look(double **mass, int a, int b) {//вывод матрицы на экран
	cout << endl;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++)
			cout << mass[j][i] << "\t ";
		cout << endl;
	}
}

void build_A() {
	double k;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			k = 1 / matrix[i][i];
			A[j][i] = matrix[j][i] * k;
		}
	}
}

void build_B() {
	for (int i = 0; i < M; i++) {
		{
			B[i] = matrix[M][i] / matrix[i][i];
			cout << B[i];
		}
		cout << endl;
	}
}

void build_C() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j)
				C[j][i] = 0;
			else
				C[j][i] = A[j][i];
		}
	}
}

double calc_BeskNormB() {
	double max = abs(B[0]);
	for (int i = 1; i < M; i++) {
		if (max < abs(B[i]))
			max = abs(B[i]);
	}
	return max;
}

double calc_BeskNormC() {
	double max = 0, tmp;
	for (int i = 0; i < M; i++) {
		tmp = 0;
		for (int j = 0; j < M; j++) {
			tmp = tmp + abs(C[j][i]);
		}
		if (max < tmp) max = tmp;
	}
	return max;
}

double Kolchshag() {
	double podlog, otnoshlog, kolsh;
	podlog = (eps*(1 - BeskNormC)) / BeskNormB;
	otnoshlog = log(podlog) / log(BeskNormC);
	kolsh = otnoshlog + 1;
	return kolsh;
}

void CX(double *cx, double **X, int i) {
	for (int m = 0; m < M; m++)
	{
		cx[m] = 0;
		for (int k = 0; k < M; k++) {
			cx[m] = cx[m] + X[k][i] * C[k][m];
		}
	}
}

int iter(double **X) {
	double *cx;
	cx = new double[M];
	int i = 0;
	do {
		i++;
		CX(cx, X, i-1);
		for (int j = 0; j < M; j++) {
			X[j][i] = B[j] - cx[j];
			/*cout << "cx=" << cx[j] << endl;
			cout << X[j][i] << endl;*/
			//cout << X[0][i] - X[0][i - 1] << endl;
		}
		//cout << "X-X " << abs(X[0][i]) - abs(X[0][i - 1]) << endl;
	} while (abs(abs(X[0][i]) - abs(X[0][i - 1])) > eps);
	return i;
}

void Zeidel(double **X, int i) {
	for (int l = 0; l < M; l++) {
		for (int j = 0; j < l; j++) {
			X[l][i] = X[l][i] + C[j][l] * X[j][i];
			//cout << "X1=" << C[j][l] << endl;
		}
		for (int j = l; j < M; j++) {
			X[l][i] = X[l][i] + C[j][l] * X[j][i - 1];
			//cout << "X2=" << C[j][l] << endl;
		}
		X[l][i] = B[l] - X[l][i];
		cout << endl;
	}
}
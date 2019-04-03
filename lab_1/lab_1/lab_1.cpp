#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int M, N;

void look(float **mas, int n, int m);
void obmen(float **mas, int a);

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream file;
	file.open("matrix.txt");///открываем файл
	//считывание из файла//
	file >> N;//число строк
	M = N + 1;//число столбцов
	//cout << M << " " << N << endl;;
	float **matrix = new float*[M];///выделяем память в строке.хз
	for (int i = 0; i < M; i++) {
		matrix[i] = new float[N];///выделяем в каждом элементе строки память, получаем столбцы.хз
	}
	for (int i = 0; i < N; i++) {///читаем матрицу
		for (int j = 0; j < M; j++) {
			if (file.eof()) {///если элементов не хватает, то ошибка
				cout << "Ошибка чтения файла";
				return 0;
			}
			file >> matrix[j][i];///считываем из файла один элемент типа инт (потому что матрица типа инт) в матрицу
		}
	}
	file.close();///закрываем файл
	look(matrix, M, N);///смотрим матрицу
	cout << "Обычный/модернизированный (0/1): " << endl;
	int r;
	cin >> r;
	float k;
	switch (r) {
	case 0://обычный
		for (int j = 0; j < N - 1; j++) {//смотри комментарии ниже. здесь так же, но без обмена
			if (matrix[j][j] == 0) {//вис ис костыль, хотя может так и должно быть. ХЗ. Если эл. = 0, то получается фигня, мы просто не можем в этом столбце другие строки обратить в ноль
				float tmp;
				int a = j;
				while (matrix[j][a] == 0 && a < N) {
					a++;
				}
				for (int i = j; i < M; i++) {///меняем местами строку а и строку мах местами
					tmp = matrix[i][j + 1];
					matrix[i][j + 1] = matrix[i][j];
					matrix[i][j] = tmp;
				}
			}
			for (int i = j + 1; i < N; i++) {
				k = matrix[j][i] / matrix[j][j];
				cout << k << endl;
				for (int e = j; e < M; e++) {
					matrix[e][i] = matrix[e][i] - matrix[e][j] * k;
				}
			}
			look(matrix, M, N);
		}
		break;
	case 1://модернизированный
		for (int j = 0; j < N - 1; j++) {// пробегаем по всем строкам, исключая последнюю
			obmen(matrix, j);//поднимаем наверх строку с макс. эл. в j строке
			//look(matrix, M, N); cout << endl;
			for (int i = j + 1; i < N; i++) {//идем по всем строкам, исключая первую
				k = matrix[j][i] / matrix[j][j];//вычисляем коэффициент
				cout << k << endl;
				if (k == 0) break;
				else {
					for (int e = j; e < M; e++) {//от i строки отнимаем j умноженную на коэф.
						matrix[e][i] = matrix[e][i] - matrix[e][j] * k;
					}
				}
			}
			look(matrix, M, N);//смотрим, что получилось
		}
		break;
	}
	////решение системы уравнений//
	float *x;
	float tmp;
	x = new float[N];
	for (int i = 1; i <= N; i++) {//пробегаем по всем строчкам
		tmp = 0;
		for (int j = 0; j < i - 1; j++) {//ищем сумму известных х умноженных на коэффициент
			tmp = tmp + x[N - (j + 1)] * matrix[N - (j + 1)][N - i];
		}
		x[N - i] = (matrix[M - 1][N - i] - tmp) / matrix[N - i][N - i];//нахождение искомого x: ах+b=c; x=(c-b)/a
	}
	////Ответ//
	cout << "Ответ:" << endl;
	for (int i = 0; i < N; i++) {
		cout << "x" << i << "= " << x[i] << endl;
	}
	system("PAUSE");
	return 0;
}

void look(float **mas, int n, int m) {//вывод матрицы на экран
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << mas[j][i] << "\t ";
		cout << endl;
	}
}

void obmen(float **mas, int a) {//поднятие строки матрицы с максимальным элементом в заданном столбце, наверх.
	float tmp;
	int max;
	max = a;
	for (int j = a + 1; j < N; j++) { ///ищем максимальный элемент в заданном столбце а
		if (abs(mas[a][max]) < abs(mas[a][j]))///костыль, потому что если макс. эл. = 0, то получается фигня, мы просто не можем в этом столбце другие строки обратить в ноль
			max = j;
	}
	for (int i = a; i < M; i++) {///меняем местами строку а и строку мах местами
		tmp = mas[i][max];
		mas[i][max] = mas[i][a];
		mas[i][a] = tmp;
	}
}
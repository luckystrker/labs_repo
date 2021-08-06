#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <iterator>


using namespace std;

typedef vector <string>  matrix;

ifstream fin;
ofstream fout;

// Генерация датасета
void GenerateDataset(const char* filename, int num) {
	fout.open(filename);
	char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < num; i++)
	{
		fout << letters[rand() % 26] << letters[rand() % 26] << letters[rand() % 26] << endl;
	}
	fout.close();
}

matrix ReadArray(const char* filename, int n) { // считывание массива из файла
	fin.open(filename);
	string buff;
	char* b1 = new char[100];
	matrix arr(n);
	for (int i = 0; i < n; i++) {
		fin >> arr[i];
	}
	fin.close();
	return arr;
}


void iswap(string &n1, string &n2)  // вспомогательная функция для сортировки (обмен значениями двух переменных)
{
	string temp = n1;
	n1 = n2;
	n2 = temp;
}

int pyr_sort(matrix &a, int n) {  // пирамидальная сортировка
	int sh = 0, abc = 0; 
	bool b;
	do
	{
		b = false;
		for (int i = 0; i < n; i++)
		{
			if (i * 2 + 2 + sh < n)
			{
				if ((a[i + sh] < a[i * 2 + 1 + sh]) || (a[i + sh] < a[i * 2 + 2 + sh]))
				{
					if (a[i * 2 + 1 + sh] > a[i * 2 + 2 + sh])
					{
						iswap(a[i + sh], a[i * 2 + 1 + sh]);
						b = true;
						abc++;
					}
					else if (a[i * 2 + 2 + sh] > a[i * 2 + 1 + sh])
					{
						iswap(a[i + sh], a[i * 2 + 2 + sh]);
						b = true;
						abc++;
					}
				}
				if (a[i * 2 + 2 + sh] > a[i * 2 + 1 + sh])
				{
					iswap(a[i * 2 + 1 + sh], a[i * 2 + 2 + sh]);
					b = true;
					abc++;
				}
			}
			else if (i * 2 + 1 + sh < n)
			{
				if (a[i + sh] < a[i * 2 + 1 + sh])
				{
					iswap(a[i + sh], a[i * 2 + 1 + sh]);
					b = true;
					abc++;
				}
			}
		}
		if (!b)
			++sh; 
	} while (sh + 2 < n);
	return abc;
}


int SortDataset(const char* filename, int n) {  // функция, считывающая массив, сортирующая его и выдающая число сравнений

	matrix arr = ReadArray(filename, n);

	int compares = pyr_sort(arr, n);


	fout.open("filename.sort.txt");

	for (int i = n-1; i > 0; i--) {
		fout << arr[i] << endl;
	}

	fout.close();

	return compares;
}

void output(const char* filename) { // функция вывода экспериментальных и теоретических значений
	int num = 1;
	ofstream abc;
	abc.open("out.txt");
	int T;
	double T1, T2, tt2, tt1;
	abc << "num\t\tT\t\tT1\t\tT2\t\tT/T1\t\tT/T2\t\t" << endl;
	cout << "num\t\tT\t\tT1\t\tT2\t\tT/T1\t\tT/T2\t\t" << endl;
	for (int i = 2; i < 14; i++) {
		num = pow(2, i);
		GenerateDataset(filename, num);
		T = SortDataset(filename, num);
		T1 = pow(num, 2);
		T2 = num * (log10(num) / log10(2));
		tt2 = T / T2;
		tt1 = T / T1;
		abc << num << "\t\t" << T << "\t\t" << T1 << "\t\t" << T2 << "\t\t" << tt1 << "\t\t" << tt2 << "\t\t" << endl;
		cout << num << "\t\t" << T << "\t\t" << T1 << "\t\t" << T2 << "\t\t" << tt1 << "\t\t" << tt2 << "\t\t" << endl;
	}
	abc.close();
}


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	const char* filename = "filename.txt";
	output(filename);
	return 0;
}


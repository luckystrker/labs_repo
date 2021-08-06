// задание - найти, у какого узла в ориентированном графе меньше всего "друзей"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

typedef vector<vector<int> > matrix; //чтобы не писать долгую конструкцию, заменим ее на matrix

ifstream fin;

matrix getGraph(const char* filename) { // функция для ввода графа
	fin.open(filename);
	int n, temp; //размерность матрицы и переменная-буфер

	fin >> n;
	matrix abc(n);
	for (int i = 0; i < n; i++) {
		abc[i].resize(n); // задаем размер вложенным векторам
		for (int j = 0; j < n; j++) {
			fin >> temp; // используем буферную переменную для ввода значений в вектор
			abc[i][j] = temp;
		}
	}
	fin.close();
	return abc;
}

void outGraph(matrix array) { // функция для вывода графа

	for (size_t i = 0; i < array.size(); i++) {
		for (vector<int>::iterator it = array[i].begin(); it < array[i].end(); ++it) { // используем итераторы для того, чтобы пройтись по вложенному вектору
			cout << *it << " ";
		}
		cout << endl;
	}

}

int findMin(matrix array) { // ищем, у кого меньше всего друзей
	int min = array.size() + 3, m, j = 0; // несколько вспомогательных переменных - min для поиска минимального количества друзей, m для сохранения номера узла с наим. кол-вом друзей, j - переменная для счета количества итераций вложенного цикла
	vector<int> subArr(array.size()); // вспомогательный вектор, хранящий количество друзей каждого узла
	for (int i = 0; i < array.size(); i++) {
		for (vector<int>::iterator it = array[i].begin(); it < array[i].end(); ++it) { // используем итераторы для того, чтобы пройтись по вложенному вектору
			j++;
			if (*it != 0 && i != j) subArr[i]++; // добавляем друга, кроме тех случаев, когда узел имеет петлю
		}
	}
	for (int i = 0; i < array.size(); i++) {
		if (subArr[i] < min) {
			min = subArr[i];
			m = i;
		}
	}
	return m+1;
}

int main() {
	const char* a= "1.txt";
	matrix arr = getGraph(a);
	cout << "Graph: " << endl;
	outGraph(arr);
	cout << findMin(arr) << " element has the lowest number of friends";
	return 0;
}

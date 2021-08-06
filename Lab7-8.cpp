// ������� - �����, � ������ ���� � ��������������� ����� ������ ����� "������"

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

typedef vector<vector<int> > matrix; //����� �� ������ ������ �����������, ������� �� �� matrix

ifstream fin;

matrix getGraph(const char* filename) { // ������� ��� ����� �����
	fin.open(filename);
	int n, temp; //����������� ������� � ����������-�����

	fin >> n;
	matrix abc(n);
	for (int i = 0; i < n; i++) {
		abc[i].resize(n); // ������ ������ ��������� ��������
		for (int j = 0; j < n; j++) {
			fin >> temp; // ���������� �������� ���������� ��� ����� �������� � ������
			abc[i][j] = temp;
		}
	}
	fin.close();
	return abc;
}

void outGraph(matrix array) { // ������� ��� ������ �����

	for (size_t i = 0; i < array.size(); i++) {
		for (vector<int>::iterator it = array[i].begin(); it < array[i].end(); ++it) { // ���������� ��������� ��� ����, ����� �������� �� ���������� �������
			cout << *it << " ";
		}
		cout << endl;
	}

}

int findMin(matrix array) { // ����, � ���� ������ ����� ������
	int min = array.size() + 3, m, j = 0; // ��������� ��������������� ���������� - min ��� ������ ������������ ���������� ������, m ��� ���������� ������ ���� � ����. ���-��� ������, j - ���������� ��� ����� ���������� �������� ���������� �����
	vector<int> subArr(array.size()); // ��������������� ������, �������� ���������� ������ ������� ����
	for (int i = 0; i < array.size(); i++) {
		for (vector<int>::iterator it = array[i].begin(); it < array[i].end(); ++it) { // ���������� ��������� ��� ����, ����� �������� �� ���������� �������
			j++;
			if (*it != 0 && i != j) subArr[i]++; // ��������� �����, ����� ��� �������, ����� ���� ����� �����
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

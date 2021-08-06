#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

using namespace std;

typedef vector<vector<int> > matrix; //����� �� ������ ������ �����������, ������� �� �� matrix

struct node {
	vector<int> rebra;
	string name;
};

struct graph {
	vector<node> nodes;
};

ifstream fin;

matrix getGraph(const char* filename) { // ������� ��� ����� ������� ���������
	fin.open(filename);
	int n, temp; //����������� ������� � ����������-�����

	fin >> n; // ������ ���������� ����� n � ���������� ����� m
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

graph fillGraph(matrix array, string* names) { // �������, ������� ��������� ����
	graph gr1;
	gr1.nodes.resize(array.size()); // ������ ����� ������
	for(size_t i = 0; i < array.size(); i++) {
		gr1.nodes[i].rebra.resize(array.size()); // ������ ������ �����
		for(size_t j = 0; j < array.size(); j++) {
			gr1.nodes[i].rebra[j] = array[i][j]; // ������������ � ���� �����
			gr1.nodes[i].name = names[i]; // ������ ���� ���
		}
	}
	return gr1;
}
 
void addNode(graph &gr) {  // ���������� ������ ���� � ����
	gr.nodes.resize(gr.nodes.size() + 1);
	int n;
	string im;
	for(size_t i = 0; i < gr.nodes.size(); i++) {
		gr.nodes[i].rebra.resize(gr.nodes.size());
	}
	cout << "Enter rebra of this node: ";
	for(size_t i = 0; i < gr.nodes.size(); i++) {
		cin >> n;
		gr.nodes[gr.nodes.size()-1].rebra[i] = n;
	}
	cout << "Now enter rebra of other nodes with this element: ";
	for(size_t k = 0; k < gr.nodes.size() - 1; k++) {
		cin >> n;
		gr.nodes[k].rebra[gr.nodes.size()-1] = n;
	}
	cout << "Enter the name of city: ";
	cin >> im;
	gr.nodes[gr.nodes.size() - 1].name = im;
}

graph deleteNode(graph gr) {   // �������� ���� � �����
	cout << "Enter the num of node: ";
	int n;
	cin >> n;
	graph gr1;
	gr1.nodes.resize(gr.nodes.size()-1);
	for(size_t i = 0; i < gr1.nodes.size(); i++) {
		if(i == n) continue;
		else if(i > n) {	
			gr1.nodes[i-1].rebra.resize(gr1.nodes.size());
			for(size_t j = 0; j < gr1.nodes.size(); j++) {
				gr1.nodes[i-1].rebra[j] = gr.nodes[i].rebra[j];
				gr1.nodes[i-1].name = gr.nodes[i].name;
			}	
		}
		else if (i < n){
			gr1.nodes[i].rebra.resize(gr1.nodes.size());
			for(size_t j = 0; j < gr1.nodes.size(); j++) {
				gr1.nodes[i].rebra[j] = gr.nodes[i].rebra[j];
			}
		}
	}
	return gr1;
}

void outGraph(graph gr) { // ������� ��� ������ �����

	for(size_t i = 0; i < gr.nodes.size(); i++) {
		cout << gr.nodes[i].name << ": ";
		for(vector<int>::iterator it = gr.nodes[i].rebra.begin(); it < gr.nodes[i].rebra.end(); ++it) {
			cout << *it << " ";
		}
		cout << endl;
	}
}


int main() {
	const char* a= "1.txt";
	int n;
	matrix arr = getGraph(a);
	string cities [7]= {"Novosibirsk", "Omsk", "Barnaul", "Tomsk", "Moskva", "Kaliningrad", "Yakutsk"};
	graph grM = fillGraph(arr, cities);
	cout << "1-add new elem; 2-delete elem; 3-output graph, 22-exit";
	while(n != 22) {
		cin >> n;
		switch(n) {
			case 1:
				addNode(grM);
				break;
			case 2:
				grM = deleteNode(grM);
				break;
			case 3:
				outGraph(grM);
				break;
			case 22:
				cout << "Bye!";
				break;
			default:
				cout << "Wrong input!" << endl;
				break;
		}
	}
	return 0;
}

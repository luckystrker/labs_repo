#include <iostream>
#include <vector>
#include <cmath>

#define EPS 1E-10 // определяем эпсилон
using namespace std;

bool is_equal(double x, double y) { // функция для сравнения чисел с плавающей точкой
	return fabs(x - y) < EPS;
}

class Vector3D { // класс для точки в трехмерном пространстве
public:
	double X;
	double Y;
	double Z;
	Vector3D(double a, double b, double c) : X(a), Y(b), Z(c) // инициализация обьекта класса 
	{
	}
	Vector3D() { // пустой конструктор

	}
	Vector3D coord(Vector3D a, Vector3D b) {  // координата отрезка в пространстве
		Vector3D cord(b.X - a.X, b.Y - a.Y, b.Z - a.Z);
		return cord;
	}
};

class Segment3D { // класс для отрезка в трехмерном пространстве
public:
	Vector3D start;
	Vector3D end;
	Segment3D(Vector3D abc, Vector3D def) : start(abc), end(def) // инициализация обьекта класса 
	{
	}

	double dot(Segment3D a, Segment3D b) {  // скалярное произведение векторов
		return (a.start.X * b.start.X + a.start.Y * b.start.Y + a.start.Z * b.start.Z);
	}

	double length(Segment3D a) { // длина отрезка
		return sqrt(pow(a.start.X - a.end.X, 2) + pow(a.start.Y - a.end.Y, 2) + pow(a.start.Z - a.end.Z, 2));
	}
	bool is_on_segment(Segment3D AB, Vector3D C) { // проверка, лежит ли точка на отрезке
		Segment3D AC(AB.start, C), BC(C, AB.end);
		bool a;
		if (fabs(length(AC) + length(BC) - length(AB)) * fabs(length(AC) + length(AB) - length(BC)) * fabs(length(AB) + length(BC) - length(AC) < EPS)) a = true;
		else a = false;
		return a;
	}
	Vector3D find_point(Segment3D first, Segment3D second, Vector3D v1, Vector3D v2) { // функция для поиска точки пересечения 
		double x, y, z;
		if (is_equal(first.start.X, first.end.X) * is_equal(second.start.X, second.end.X) * is_equal(v1.X, v2.X) * is_equal(first.start.X, second.end.X) * is_equal(first.start.X, v1.X) * is_equal(second.start.X, v1.X) == 0)
			x = (first.start.X * v1.Y * v2.X - second.start.X * v1.X * v2.Y - first.start.Y * v1.X * v2.X + second.start.Y * v1.X * v2.X) / (v1.Y * v2.X - v1.X * v2.Y); // проверка на то, что все точки находятся в одной из плоскостей Х, Y или Z
		else x = v1.X;																																				 // из канонического уравнения прямой ( (x-x0)/p = (y-y0)/q = (z-z0)/r ) получаем три уравнения для
		if (is_equal(first.start.Y, first.end.Y) * is_equal(second.start.Y, second.end.Y) * is_equal(v1.Y, v2.Y) * is_equal(first.start.Y, second.end.Y) * is_equal(first.start.Y, v1.Y) * is_equal(second.start.Y, v1.Y) == 0) // x, y и z, точки пересечения двух прямых
			y = (first.start.Y * v1.X * v2.Y - second.start.Y * v1.Y * v2.X - first.start.X * v1.Y * v2.Y + second.start.X * v1.Y * v2.Y) / (v1.X * v2.Y - v1.Y * v2.X);
		else y = v1.Y;
		if (is_equal(first.start.Z, first.end.Z) * is_equal(second.start.Z, second.end.Z) * is_equal(v1.Z, v2.Z) * is_equal(first.start.Z, second.end.Z) * is_equal(first.start.Z, v1.Z) * is_equal(second.start.Z, v1.Z) == 0)
			z = (first.start.Z * v1.Y * v2.Z - second.start.Z * v1.Z * v2.Y - first.start.Y * v1.Z * v2.Z + second.start.Y * v1.Z * v2.Z) / (v1.Y * v2.Z - v1.Z * v2.Y);
		else z = v1.Z;
		Vector3D found(x, y, z);
		cout << "Coordinates of intercection are: X(" << x << "), Y(" << y << "), Z(" << z << ")" << endl;
		return found;
	}
};


bool Intersect(Segment3D a, Segment3D b) { // проверка, пересекаются ли прямые в пространстве
	bool abc; // переменная, показывающая, пересекаются прямые, заданные отрезками, или нет
	vector<vector<double> > m(3);
	for (int i = 0; i < 3; i++) m[i].resize(3);
	m = { {a.start.X - a.end.X, a.start.Y - a.end.Y, a.start.Z - a.end.Z},{b.start.X - b.end.X, b.start.Y - b.end.Y, b.start.Z - b.end.Z},{a.start.X - b.start.X, a.start.Y - b.start.Y, a.start.Z - b.start.Z} };  // матрица
	double determ = (m[0][0] * m[1][1] * m[2][2]) + (m[0][1] * m[1][2] * m[2][0]) + (m[0][2] * m[1][0] * m[2][1]) - (m[0][2] * m[1][1] * m[2][0]) - (m[0][0] * m[1][2] * m[2][1]) - (m[0][1] * m[1][0] * m[2][2]); // определитель матрицы
	cout << "Determinant of thix matrix is " << determ << endl;
	if (fabs(determ) <= EPS) { // если определитель равен нулю (то есть прямые лежат в одной плоскости)
		if (fabs(m[0][0] / m[1][0] - m[0][1] / m[1][1]) < EPS && fabs(m[0][1] / m[1][1] - m[0][2] / m[1][2]) < EPS) {
			abc = false; // делаем проверку по каноническому уравнению, если равенство верно - прямые параллельны
			cout << "Segments are parallel" << endl;
		}
		else abc = true; // иначе прямые пересекаются
	}
	else {
		abc = false; // в любых других случаях прямые скрещиваются
		cout << "Segments are crossing" << endl;
	}
	return abc;
}




int main() {
	vector<vector<int> > pt(4); // двухмерный массив размера 4х3, где будут храниться данные 
	for (int k = 0; k < 4; k++) {
		cout << "Enter the X, Y and Z of " << k+1 << " point: ";
		for (int i = 0; i < 3; i++) {
			pt[k].resize(3);
			cin >> pt[k][i];
		}
	}

	Vector3D P1(pt[0][0], pt[0][1], pt[0][2]);
	Vector3D P2(pt[1][0], pt[1][1], pt[1][2]);
	Vector3D P3(pt[2][0], pt[2][1], pt[2][2]);
	Vector3D P4(pt[3][0], pt[3][1], pt[3][2]);
	Segment3D S1(P1, P2);
	Segment3D S2(P3, P4);
	Vector3D vct1, vct2, pnt; // направляющие вектора отрезков и искомая точка
	vct1 = vct1.coord(P1, P2);
	vct2 = vct2.coord(P3, P4);

	if (S1.length(S1) < EPS || S1.length(S2) < EPS) {
		cout << "Some of the segments has zero length";
		return 0;
	}

	bool a = Intersect(S1, S2);
	if (a) {
		cout << "Pramiye are intersecting" << endl;
		pnt = S1.find_point(S1, S2, vct1, vct2);
		if (S1.is_on_segment(S1, pnt) || S1.is_on_segment(S2, pnt)) {
			cout << "Searched point is on the one of segments";
		}
	}
	else return 0;



	return 0;
}

#include "ATD.h" 
#include <iostream>
using namespace std;

double matrix::EPS = 0.0001;

int main() {
	try {
		double stroka[4] = {3,5,6,7};
		double stolbec[3] = {1.5,2.3,3.0};
		//bool b;
	
		matrix A(3, 2);                               // конструктор матрицы размера mxn со значениями 0.0
		matrix B(5) ;                                 // матрица 1x1 с этим элементом
		matrix C(stroka, 4) ;                         // матрица-строка из массива длины n0
		matrix D(3, stolbec) ;                        // матрица-столбец из массива длины m0
		matrix E("{ {1, 2, 3}, {3, 4}, {0}, {0} }");  // из строкового представления
		matrix F(A);                                  // конструктор копирования
		matrix G("{ {9, 8}, {5, 4, 3} }");
		
		//cout << "++++\n" << E(5);
		
		cout << "A=\n" << A;
		cout << "B=\n" << B;
		cout << "C=\n" << C;
		cout << "D=\n" << D;
		cout << "E=\n" << E;
		cout << "F=\n" << F;
		cout << "G=\n" << G;
	
		A = matrix::identity(5);
		F = matrix::diagonal(stroka, 4);
		B = E*4;
	}
	catch (const char* er){
		cout << er << '\n';
		return 1;
	}
	
	return 0;
}

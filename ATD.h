#ifndef hlist
#define hlist

#include <iostream>
using namespace std;

class matrix {
	double ** M;        // указатель на матрицу
	int n, m;           // n - число столбцов, m - число строк
	static double EPS;
public:
	matrix(int m0, int n0) ;  // конструктор матрицы размера mxn со значениями 0.0
	
	matrix(double a) ;  // матрица 1x1 с этим элементом
	
	matrix(double* p, int n0) ;  // матрица-строка из массива длины n0
	
	matrix(int m0, double* p) ;  // матрица-столбец из массива длины m0
	
	matrix(const char* str) ;  // из строкового представления
	
	matrix(const matrix & B) ;  // конструктор копирования
	
	static matrix identity(int n0) ;  // возвращает единичную матрицу размера n;
	
	static matrix diagonal(double* vals, int n) ;  // возвращает диагональную матрицу размера n с заданными
							 // элементами по главной диагонали;
	int rows() ;  // число строк;
	
	int columns() ;  // число столбцов;
	
	double & operator () (int m0, int n0) ;  // присвоить значение элементу [i][j];
	
	matrix operator () (int k) ;  // вернуть строку матрицы;
		
	matrix operator * (double a) ;  // умножение матрицы на скаляр
	
	matrix & operator *= (double a) ;  // умножение матриц на скаляр
	
	matrix operator + (const matrix & B) ;  // сложение матриц
	
	matrix & operator += (const matrix & B) ;  // сложение матриц
	
	matrix operator - (const matrix & B) ;  // вычитание матриц
	
	matrix & operator -= (const matrix & B) ;  // вычитание матриц
	
	matrix operator * (const matrix & B) ;  // умножение матриц
	
	matrix & operator *= (const matrix & B) ;  // умножение матриц
	
	matrix operator - () ;  // умножение элементов матрицы на -1
	
	bool operator == (const matrix & B) ;  // сравнение матриц на равенсто
	
	bool operator != (const matrix & B) ;  // сравнение матриц
	
	matrix operator | (const matrix & B) ;  // конкатенировать матрицы горизонтально
	
	matrix operator / (const matrix & B) ;  // конкатенировать матрицы вертикально
	
	matrix & operator = (const matrix & B) ;  // присваивание матриц
	
	friend ostream & operator << (ostream & output, const matrix & A) ;  // перегрузка операции << – вывод матрицы, в привычном двумерном виде
	
	~matrix() ;  // деструктор
};

#endif

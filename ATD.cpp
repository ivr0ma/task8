#include "ATD.h" 
#include <iostream>
#include <stdio.h>
using namespace std;

matrix::matrix(int m0, int n0) {
	int i, j;
	
	n = n0;
	m = m0;
	
	M = new double* [m];
	
	for (i=0; i<m; i++) {
		M[i] = new double [n];
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			M[i][j] = 0.0;
		}
	}
};

matrix::matrix(double a) {
	n = 1;
	m = 1;
	
	M = new double* [1];
	M[0] = new double [1];
	
	M[0][0] = a;
};

matrix::matrix(double* p, int n0) {
	int i, j;
	
	n = n0;
	m = 1;
	
	M = new double* [m];
	
	for (i=0; i<m; i++) {
		M[i] = new double [n];
	}
	
	for (j=0; j<n; j++) {
		M[0][j] = p[j];
	}
}

matrix::matrix(int m0, double* p) {
	int i;
	
	n = 1;
	m = m0;
	
	M = new double* [m];
	
	for (i=0; i<m; i++) {
		M[i] = new double [n];
	}
	
	for (i=0; i<m; i++) {
		M[i][0] = p[i];
	}
}

matrix::matrix(const char* str) {
	int i = 0; // кол-во "{"
	int j = 0; // кол-во "}"
	int k = 0; // длина строки
	int t = 0; // кол-во "," в столбце
	int r = 0; // максимально кол-во "," в столбце
	
	// подсчет параметров
	while (str[k] != '\0') {
		if (str[k] == '{') {
			i++;
			t = 0;
		}
		if (str[k] == ',') {
			t++;
		}
		if (str[k] == '}') {
			j++;
			if (t>r) {
				r = t;
			}
		}
		k++;
	};
	
	if (k <= 2 || i != j || i <= 1 || str[0] != '{' || str[k-1] != '}') {
		// cout << "error\n";
		throw "error: incorrect string format";
	}
	else {
		m = i-1;
		n = r+1;
		
		// создаем матрицу размерами m*n
		M = new double* [m];
	
		for (i=0; i<m; i++) {
			M[i] = new double [n];
		}
		
		// идем по строкам
		t = 1;
		for (i=0; i<m; i++) {
			j = 0;
			
			// доходим до скобки
			while (str[t++] != '{') { };
			
			// обрабатываем столбец
			r = t;
			while (str[t] != '}') {
				if (str[t] == ',') {
					sscanf(str+r, "%lf", &M[i][j]);
					r = t+1;
					j++;
				}
				t++;
			}
			
			// записываем число перед скобкой
			sscanf(str+r, "%lf", &M[i][j]);
			j++;
			
			// добиваем оставшиеся позиции в столбце
			for ( ; j<n; j++) {
				M[i][j] = 0.0;
			}
		}
	}
}

matrix::matrix(const matrix & B) {
    int i, j;
    
    n = B.n;
    m = B.m;

    M = new double* [m];

    for (i=0; i<m; i++) {
        M[i] = new double [n];
    }

    for (i=0; i<m; i++) {
        for (j=0; j<n; j++) {
            M[i][j] = B.M[i][j];
        }
    }
}

matrix matrix::identity(int n0) {
	matrix T(n0, n0);
	for (int i=0; i<n0; i++) {
		T.M[i][i] = 1;
	}
	return T;
}

matrix matrix::diagonal(double* vals, int n0) {
	matrix T(n0, n0);
	for (int i=0; i<n0; i++) {
		T.M[i][i] = vals[i];
	}
	return T;
}

int matrix::rows() {
	return m;
}

int matrix::columns() {
	return n;
}

double & matrix::operator () (int m0, int n0) {
	return M[m0][n0];
}

matrix matrix::operator () (int k) {
	int i;
	
	matrix T(1, n);
	
	if (k >= m) {
		throw "index out of range";
	}
	
	for (i=0; i<n; i++) {
		T.M[0][i] = M[k][i];
	}
	return T;
}

matrix & matrix::operator = (const matrix & B) {
	int i, j;
	
	if (this == & B)
		return * this;
	
	if (M != 0) {
		for (i = 0; i < m; i++) {
			delete [] M[i];
		}
        	
      		delete [] M;
	}
	
	n = B.n;
	m = B.m;
	
	M = new double* [m];
	
	for (i=0; i<m; i++) {
		M[i] = new double [n];
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			M[i][j] = B.M[i][j];
		}
	}
	
	return * this;
}

matrix matrix::operator * (double a) {
	int i, j;
	
	matrix T1(m, n);
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			T1.M[i][j] = M[i][j] * a;
		}
	}
	
	return T1;
}

matrix & matrix::operator *= (double a) {
	int i, j;
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			M[i][j] *= a;
		}
	}
	return * this;
}

matrix matrix::operator + (const matrix & B) {
	int i, j;
	
	matrix T(m, n);
	
	if (n != B.n || m != B.m) {
		throw "+: size mismatch";
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			T.M[i][j] = M[i][j] + B.M[i][j];
		}
	}
	
	return T;
}

matrix & matrix::operator += (const matrix & B) {
	int i, j;
	
	if (n != B.n || m != B.m) {
		throw "+=: size mismatch";
	}

	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			M[i][j] += B.M[i][j];
		}
	}
	return * this;
}

matrix matrix::operator - (const matrix & B) {
	int i, j;
	
	matrix T(m, n);
	
	if (n != B.n || m != B.m) {
		throw "-: size mismatch";
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			T.M[i][j] = M[i][j] - B.M[i][j];
		}
	}
	
	return T;
}

matrix & matrix::operator -= (const matrix & B) {
	int i, j;
	
	if (n != B.n || m != B.m) {
		throw "-=: size mismatch";
	}

	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			M[i][j] -= B.M[i][j];
		}
	}
	return * this;
}

matrix matrix::operator * (const matrix & B) {
	int i, j, k;
	
	matrix T(m, B.n);
	
	if (n != B.m) {
		throw "*: size mismatch";
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<B.n; j++) {
			for (k=0; k<n; k++) {
				T.M[i][j] += M[i][k] * B.M[k][j];
			}
		}
	}
	
	return T;
}

matrix & matrix::operator *= (const matrix & B) {
	double ** T;
	int i, j, k;
	
	if (n != B.m) {
		throw "*=: size mismatch";
	}
	
	T = M;
	
	M = new double* [m];
	
	for (i=0; i<m; i++) {
		M[i] = new double [B.n];
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<B.n; j++) {
			M[i][j] = 0.0;
		}
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<B.n; j++) {
			for (k=0; k<n; k++) {
				M[i][j] += T[i][k] * B.M[k][j];
			}
		}
	}
	
	n = B.n;
	
	for (i = 0; i < m; i++) {
		delete [] T[i];
	}
        	
      	delete [] T;
      	
	return * this;
}

matrix matrix::operator - () {
	int i, j;
	
	matrix T(m, n);
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			T.M[i][j] = M[i][j]*(-1);
		}
	}
	
	return T;
}

bool matrix::operator == (const matrix & B) {
	if (n != B.n || m != B.m) {
		return false;
	}
	
	bool compare = true;
	
	for (int i=0; i<m; i++) {
		for (int j=0; j<n; j++) {
			if ( abs(M[i][j] - B.M[i][j]) > EPS ) {
				compare = false;
				break;
			}
		}
		if (!compare) {
			break;
		}
	}
	
	return compare;
}

bool matrix::operator != (const matrix & B) {
	if (n != B.n || m != B.m) {
		return true;
	}
	
	bool compare = false;
	
	for (int i=0; i<m; i++) {
		for (int j=0; j<n; j++) {
			if ( abs(M[i][j] - B.M[i][j]) > EPS ) {
				compare = true;
				break;
			}
		}
		if (compare) {
			break;
		}
	}
	
	return compare;
}

matrix matrix::operator | (const matrix & B) {
	int i, j;
	
	matrix T(m, B.n+n);
	
	if (m != B.m) {
		throw "|: size mismatch";
	}
	
	for (i=0; i<m; i++) {
		for (j=0; j<n; j++) {
			T.M[i][j] = M[i][j];
		}
		for (j=0; j<B.n; j++) {
			T.M[i][j+n] = B.M[i][j];
		}
	}
	
	return T;
}

matrix matrix::operator / (const matrix & B) {
	int i, j;
	
	matrix T(B.m+m, n);
	
	if (n != B.n) {
		throw "/: size mismatch";
	}
	
	for (i=0; i<m+B.m; i++) {
		for (j=0; j<n; j++) {
			if (i<m) {
				T.M[i][j] = M[i][j];
			} 
			else {
				T.M[i][j] = B.M[i-m][j];
			}
		}
	}
	
	return T;
}

ostream & operator << (ostream & output, const matrix & A) {
	for (int i=0; i<A.m ; i++) {
		for (int j=0; j<A.n; j++) {
			output << A.M[i][j] << ' ';
		}
		output << endl;
	}
	return output;
}

matrix::~matrix() {
	int i;
	
	if (M != 0) {
		for (i = 0; i < m; i++) {
			delete [] M[i];
		}
        	
      		delete [] M;
	}
};

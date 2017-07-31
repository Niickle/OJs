#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Matrix {
public:
	Matrix( const unsigned int d );
	~Matrix();
	
	void swapRow( const unsigned int x, const unsigned int y );	//swap( mat[x], mat[y] )
	void multiRow( const unsigned int ri, const double m );	//mat[ri] *= m
	void minusRow( const unsigned int ri, const unsigned int rj, const double m );	//mat[ri] -= mat[rj] * m
	
	unsigned int dim;
	double** mat;	
};

Matrix::Matrix( const unsigned int d ) : dim(d) {
	mat = new double*[d];
	for( unsigned int i = 0; i < d; i ++ ) {
		mat[i] = new double[d];
		memset( mat[i], 0, sizeof(double) * d );
		mat[i][i] = 1;
	}
}
Matrix::~Matrix() {
	for( unsigned int i = 0; i < dim; i ++ )
		delete mat[i];
	delete mat;
}

void Matrix::swapRow( const unsigned int x, const unsigned int y ) {
	if( x >= dim || y >= dim )
		return;
	
	if( x != y ) {	
		double* tmp( mat[x] );
		mat[x] = mat[y];
		mat[y] = tmp;
	}
	
	return;
}

void Matrix::multiRow( const unsigned int ri, const double m ) {
	if( ri >= dim )
		return;
	
	for( unsigned int i = 0; i < dim; i ++ )
		mat[ri][i] *= m;
	return;
}

void Matrix::minusRow( const unsigned int ri, const unsigned int rj, const double m ) {
	if( ri >= dim || rj >= dim )
		return;
	
	for( unsigned int i = 0; i < dim; i ++ )
		mat[ri][i] -= mat[rj][i] * m;
	return;	
}

int main() {
	
	//input
	unsigned int dim;
	cin>>dim;
	Matrix m1(dim), m2(dim);
	for( unsigned int i = 0; i < dim; i ++ )
		for( unsigned int j = 0; j < dim; j ++ )
			cin>>m1.mat[i][j];
	
	//solve
	unsigned int ti;
	for( unsigned int i = 0; i < dim; i ++ ) {
		for( ti = i; ti < dim; ti ++ )
			if( m1.mat[ti][i] )
				break;
		m2.swapRow( i, ti );
		m1.swapRow( i, ti );
		m2.multiRow( i, 1.0 / m1.mat[i][i] );
		m1.multiRow( i, 1.0 / m1.mat[i][i] );
		for( ti = i+1; ti < dim; ti ++ ) {
			m2.minusRow( ti, i, m1.mat[ti][i] );
			m1.minusRow( ti, i, m1.mat[ti][i] );
		}
	}
	for( unsigned int i = dim-1; i > 0; i --  ) {
		for( ti = 0; ti < i; ti ++ ) {
			m2.minusRow( ti, i, m1.mat[ti][i] );
			m1.minusRow( ti, i, m1.mat[ti][i] );			
		}
	}
	
	//output
	cout.precision(3);
	cout<<fixed;
	for( unsigned int i = 0; i < dim; i ++ ) {
		for( unsigned int j = 0; j < dim-1; j ++ )
			cout<<m2.mat[i][j]<<' ';
		cout<<m2.mat[i][dim-1]<<endl;
	}
	
	return 0;
}

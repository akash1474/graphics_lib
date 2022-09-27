#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <string.h>
#include <vector>
#include "functional"
#include "exception"


/* 
 * @params (int row, int cols, std::vector<std::vector<double>>)
 * @params (int row, int cols, double initialValue)
*/
class Matrix{
public:
	int rows;
	int cols;
	std::vector<std::vector<double>> data;

	class matrix_error:public std::exception{
		private:		
			const char* m_Msg;
		public:
			matrix_error(const char* err):m_Msg(err){}
			virtual const char* what()const noexcept override{
				std::cout << "MATRIX_ERROR: ";
				return this->m_Msg;
			}
	};


	Matrix(int,int,double d=1.0);
	Matrix(int,int,std::vector<std::vector<double>>);
	Matrix(std::vector<std::vector<double>>);
	~Matrix(){}

	void print();
	void shape();
	void map(double(*fn)(double));
	void randomize(float x=0,float y=1);
	void transpose();
	void normalize();
	double rowSum(int r=0);
	double colSum(int c=0);

	std::vector<double> row(int r=0);
	std::vector<double> col(int c=0);
	std::vector<double> diagonal();


	void operator= (const Matrix&);
	bool operator== (const Matrix&);
	void operator+ (const double);
	void operator- (const double);
	void operator* (const double);
	void operator/ (const double);
	void operator^ (const int&);
	Matrix operator+ (const Matrix&);
	Matrix operator- (const Matrix&);
	Matrix operator* (const Matrix&);
	Matrix operator/ (const Matrix&);
	friend std::ostream& operator<< (std::ostream& os,const Matrix& m);

	static double sum(const Matrix&);
	static double vecSum(const std::vector<double>&);
	static float random(float, float);
	/*
		@brief Creates a Matrix of (1xn), where n=vec.size()
	*/
	static Matrix convertFromArray(std::vector<double>);
	static Matrix convertFromArray(std::vector<std::pair<double,double>>);
	static Matrix dot(const Matrix&,const Matrix&);
	static Matrix transpose(const Matrix&);
	static std::pair<double,double> min_max(const Matrix&);
	static Matrix normalize(const Matrix& m);
	static Matrix pow(Matrix m,int pow);
	static Matrix map(const Matrix&,double(*fn)(double));
	static Matrix mapx(const Matrix&,std::function<double(double)>);
	static Matrix map(const Matrix&,std::vector<double>(*fn)(std::vector<double>));
	static Matrix map(Matrix&,Matrix&,double(*fn)(double,double));
	static Matrix mapx(Matrix,Matrix,std::function<double(double,double)>);
	static Matrix rowSum(Matrix,std::vector<double>(*fn)(std::vector<double>));
};




#endif

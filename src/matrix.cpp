#include "matrix.h"
#include "iostream"
#include "vector"
#include "random"
#include "stdio.h"
#include "time.h"

Matrix::Matrix(int r,int c,double v):rows{r},cols{c}{
	this->data=std::vector<std::vector<double>>(rows,std::vector<double>(cols));
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			if(i==j) this->data[i][j]=v;
			else this->data[i][j]=0.0;
		}
		this->data[i].shrink_to_fit();
	}
	this->data[0].shrink_to_fit();
}

Matrix::Matrix(std::vector<std::vector<double>> vec){
	this->rows=vec.size();
	this->cols=vec[0].size();
	this->data=vec;
}

Matrix::Matrix(int r,int c,std::vector<std::vector<double>> d={}):rows{r},cols{c},data{d}{
	if(data.size()==0){
		this->data={};
		for(int i=0;i<this->rows;i++){
			this->data[i]={};
			for(int j=0;j<this->cols;j++){
				this->data[i][j]=0.0;
			}
		}
	}else{
		if((int)this->data.size() !=this->rows || (int)this->data[0].size() !=this->cols){
			throw Matrix::matrix_error("Incorrect Dimensions");
		}
	}
}

///////////////////////////////////////     MEMBER FUNCTIONS      //////////////////////////////////////////

void Matrix::shape(){
	printf("shape=(%d,%d)",this->rows,this->cols);
}

void Matrix::map(double(*fn)(double)){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]=fn(this->data[i][j]);
		}
	}
}


void Matrix::print(){
	std::cout  << " [\n";
		for(int i=0;i<this->rows;i++){
			std::cout  << "\t[ ";
			for(int j=0;j<this->cols;j++){
				std::cout  << this->data[i][j] << " ";	
			}
			std::cout  << "]\n";
		}
	std::cout  << " ] -> ";
	printf("(%d,%d)\n",this->rows,this->cols);
}

void Matrix::randomize(float min,float mx){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]=Matrix::random(min,mx);
		}
	}
}


void Matrix::transpose(){
	Matrix mat(this->cols,this->rows,0.0);
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			mat.data[j][i]=this->data[i][j];
		}
	}
	this->rows=mat.rows;
	this->cols=mat.cols;
	this->data=mat.data;
}

std::vector<double> Matrix::diagonal(){
	if(this->rows==this->cols){
		throw Matrix::matrix_error("Matrix is not a square matrix (nxn)");
	}
	std::vector<double> vec;
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			if(i==j){
				vec.push_back(this->data[i][j]);
			}
		}
	}
	return vec;
}

std::vector<double> Matrix::row(int r){
	std::vector<double> vec;
	for(int i=0;i<this->rows;i++){
		if(r==i){
			for(int j=0;j<this->cols;j++){
				vec.push_back(this->data[j][i]);
			}
		}
	}
	return vec;
}

std::vector<double> Matrix::col(int c){
	std::vector<double> vec;
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			if(c==j){
				vec.push_back(this->data[j][i]);
			}
		}
	}
	return vec;
}

double Matrix::rowSum(int r){
	return Matrix::vecSum(this->row(r));
}

double Matrix::colSum(int c){
	return Matrix::vecSum(this->col(c));
}

void Matrix::normalize(){
	std::pair<double,double> mm=Matrix::min_max((*this));
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]=(this->data[i][j]-mm.first)/(mm.second-mm.first);
		}
	}
}

///////////////////////////////////////     STATIC      //////////////////////////////////////////
double Matrix::sum(const Matrix& m){
	double sum=0.0;
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			sum+=m.data[i][j];
		}
	}
	return sum;
}

float Matrix::random(float LO=0, float HI=1){
   static bool first = true;
   if (first) 
   {  
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }   
   return LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
}

Matrix Matrix::dot(const Matrix& m1,const Matrix& m2){
	if(m1.cols!=m2.rows){
		printf("\nERROR_DOT:  m1(%dx%d) != m2(%dx%d)\n",m1.rows,m1.cols,m2.rows,m2.cols);
		throw Matrix::matrix_error("Matrix not compatible for dot product");
	}
	Matrix m(m1.rows,m2.cols,0.0);
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			double sum=0.0;
			for(int k=0;k<m1.cols;k++){
				sum+=m1.data[i][k]*m2.data[k][j];
			}
			m.data[i][j]=sum;
		}
	}
	return m;
}


Matrix Matrix::transpose(const Matrix& m){
	Matrix mat(m.cols,m.rows,0.0);
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			mat.data[j][i]=m.data[i][j];
		}
	}
	return mat;
}

double Matrix::vecSum(const std::vector<double>& vec){
	double sum=0.0;
	for(const double& el:vec){
		sum+=el;
	}
	return sum;
}

Matrix Matrix::map(const Matrix& m,double(*fn)(double)){
	Matrix mat=m;
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			mat.data[i][j]=fn(m.data[i][j]);
		}
	}
	return mat;
}


Matrix Matrix::mapx(const Matrix& m,std::function<double(double)>fn){
	Matrix mat=m;
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			mat.data[i][j]=fn(m.data[i][j]);
		}
	}
	return mat;
}


Matrix Matrix::convertFromArray(std::vector<double>vec){
	return Matrix(1,vec.size(),{vec});
}

Matrix Matrix::convertFromArray(std::vector<std::pair<double,double>> vec){
	Matrix m=Matrix(vec.size(),2,0.0);
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			if(j%2==0) m.data[i][j]=vec[i].first;
			if(j%2!=0) m.data[i][j]=vec[i].second;
		}
	}
	return m;
}

std::pair<double,double> Matrix::min_max(const Matrix& m){
	std::pair<double,double> mm;
	double min=0.0;
	double max=0.0;
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			if(min > m.data[i][j]) min=m.data[i][j];
			if(max < m.data[i][j]) max=m.data[i][j];
		}
	}
	mm.first=min;
	mm.second=max;
	return mm;
}

Matrix Matrix::normalize(const Matrix& m){
	Matrix mat=m;
	std::pair<double,double> mm=Matrix::min_max(m);
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			mat.data[i][j]=(m.data[i][j]-mm.first)/(mm.second-mm.first);
		}
	}
	return mat;
}


Matrix Matrix::pow(Matrix m,int p){
	for(int i=0;i<m.rows;i++){
		for(int j=0;j<m.cols;j++){
			m.data[i][j]=std::pow(m.data[i][j],p);
		}
	}
	return m;
}

Matrix Matrix::map(const Matrix& m,std::vector<double>(*fn)(std::vector<double>)){
	Matrix mat(m.rows,m.cols,0.0);
	for(int i=0;i<m.rows;i++){
		mat.data[i]=fn(m.data[i]);
	}
	return mat;
}

Matrix Matrix::map(Matrix& m1,Matrix& m2,double(*fn)(double,double)){
	if(m1.rows!=m2.rows || m1.cols!=m2.cols){
		printf("\n ERROR_MAP: Invalid dimesions of (%dx%d)!=(%d,%d)",m1.rows,m1.cols,m2.rows,m2.cols);
		throw Matrix::matrix_error("Invalid Dimesions for performing maping...");
	}
	Matrix m(m1.rows,m1.cols,0.0);
	for(int i=0;i<m1.rows;i++){
		for(int j=0;j<m1.cols;j++){
			m.data[i][j]=fn(m1.data[i][j],m2.data[i][j]);
		}
	}
	return m;
}


Matrix Matrix::mapx(Matrix m1,Matrix m2,std::function<double(double,double)>fn){
	if(m1.rows!=m2.rows || m1.cols!=m2.cols){
		printf("\n ERROR_MAP: Invalid dimesions of (%dx%d)!=(%d,%d)",m1.rows,m1.cols,m2.rows,m2.cols);
		throw Matrix::matrix_error("Invalid Dimesions for performing maping...");
	}
	Matrix m(m1.rows,m1.cols,0.0);
	for(int i=0;i<m1.rows;i++){
		for(int j=0;j<m1.cols;j++){
			m.data[i][j]=fn(m1.data[i][j],m2.data[i][j]);
		}
	}
	return m;
}


Matrix Matrix::rowSum(Matrix m,std::vector<double>(*fn)(std::vector<double>)){
	Matrix mat(m.rows,1,0.0);
	for(int i=0;i<m.rows;i++){
		mat.data[i]=fn(m.data[i]);
	}
	return mat;
}

///////////////////////////////////////     OPERATOR OVERLOAD      //////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const Matrix& mat){
	os  << " [\n";
		for(int i=0;i<mat.rows;i++){
			os  << "\t[ ";
			for(int j=0;j<mat.cols;j++){
				os  << mat.data[i][j] << " ";	
			}
			os  << "]\n";
		}
	os  << " ]\n";
	return os;
}

void Matrix::operator= (const Matrix& m){
	this->rows=m.rows;
	this->cols=m.cols;
	this->data=m.data;
}

bool Matrix::operator== (const Matrix& m){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			if(this->data[i][j]!=m.data[i][j]) return false;
		}
	}
	return true;
}

void Matrix::operator^ (const int& d){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]=std::pow(this->data[i][j],d);
		}
	}
}

void Matrix::operator+ (const double d){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]+=d;
		}
	}
}

void Matrix::operator- (const double d){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]-=d;
		}
	}
}

void Matrix::operator* (const double d){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]*=d;
		}
	}
}

void Matrix::operator/ (const double d){
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			this->data[i][j]/=d;
		}
	}
}
Matrix Matrix::operator+ (const Matrix& m){
	Matrix mat(this->rows,this->cols,0);

	//adding m to each row
	if(m.cols==this->cols && m.rows==1){
		for(int i=0;i<this->rows;i++){
			for(int j=0;j<this->cols;j++){
				mat.data[i][j]=this->data[i][j]+m.data[0][j];
			}
		}
		return mat;
	}

	//adding m to each column
	if(m.rows==this->rows && m.cols==1){
		for(int i=0;i<this->rows;i++){
			for(int j=0;j<this->cols;j++){
				mat.data[i][j]=this->data[i][j]+m.data[i][0];
			}
		}
		return mat;
	}

	if(m.rows!=this->rows || m.cols!=this->cols){
		printf("Dimensions Mismatch (+)\n");
		throw Matrix::matrix_error("Invalid Dimesions for performing operator+ ");
	}

	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			mat.data[i][j]=this->data[i][j]+m.data[i][j];
		}
	}
	return mat;
}


Matrix Matrix::operator- (const Matrix& m){
	if(m.rows!=this->rows || m.cols!=this->cols){
		throw Matrix::matrix_error("Dimensions Mismatch! for operator-");
	}
	Matrix mat(this->rows,this->cols,0);
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			mat.data[i][j]=this->data[i][j]-m.data[i][j];
		}
	}

	return mat;
}

Matrix Matrix::operator* (const Matrix& m){
	if(m.rows!=this->rows || m.cols!=this->cols){
		throw Matrix::matrix_error("Dimensions Mismatch! for operator*");
	}
	Matrix mat(this->rows,this->cols,0);
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			mat.data[i][j]=this->data[i][j]*m.data[i][j];
		}
	}

	return mat;
}

Matrix Matrix::operator/ (const Matrix& m){
	if(m.rows!=this->rows || m.cols!=this->cols){
		throw Matrix::matrix_error("Dimensions Mismatch! for operator/");
	}
	Matrix mat(this->rows,this->cols,0);
	for(int i=0;i<this->rows;i++){
		for(int j=0;j<this->cols;j++){
			mat.data[i][j]=this->data[i][j]/m.data[i][j];
		}
	}

	return mat;
}


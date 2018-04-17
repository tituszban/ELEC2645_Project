#include "Matrix.h"
#include "mbed.h"
#include <string>
// #include <iostream>



void MatrixDimentionMissmatchError(Shape s1, Shape s2, string context)
{
  printf("Matrix Dimension Mismatch Exception! Operation on matrices of shape: %d:%d and %d:%d in context: %s\n", s1.width, s1.height, s2.width, s2.height, context.c_str());
  while(1){

  }
}

Matrix::Matrix(){
  matrix_type m(0, vector<double>(0));
  this->Setup(m);
}
Matrix::Matrix(Shape shape){
  matrix_type m(shape.width, vector<double>(shape.height));
  this->Setup(m);
}
Matrix::Matrix(int width, int height){
  matrix_type m(width, vector<double>(height));
  this->Setup(m);
}
Matrix::Matrix(matrix_type m){
  this->Setup(m);
}
Matrix::Matrix(int width, int height, double* m){
  matrix_type tempM(width, vector<double>(height));
  for(int i = 0; i < width; i++){
    for (int j = 0; j < height; j++) {
      tempM[i][j] = m[i + width * j];
    }
  }
  this->Setup(tempM);
}

void Matrix::Setup(matrix_type m){
  int width = m.size();
  int height = width == 0 ? 0 : m[0].size();
  Shape temp_shape = {width, height};
  this->shape = temp_shape;
  this->_matrix = m;
}

void Matrix::print_matrix(){
  string buffer = "[\n";
  for(int j = 0; j < this->shape.height; j++){
    for(int i = 0; i < this->shape.width; i++){
      char b[1024];
      sprintf(b, "%s\t%f%s", buffer.c_str(), this->get(i, j), (i + 1 < this->shape.width ? "" : "\n"));
      string str(b);
      buffer = str;
    }
  }
  printf("%s\n]\n", buffer.c_str());
}

void Matrix::set(int w, int h, double v){
  this->_matrix[w][h] = v;
}

double Matrix::get(int w, int h){
  return this->_matrix[w][h];
}

Matrix Matrix::transpose(){
  Matrix m(this->shape.height, this->shape.width);
  for(int i = 0; i < m.shape.width; i++){
    for(int j = 0; j < m.shape.height; j++){
      m.set(i, j, this->get(j, i));
    }
  }
  return m;
}

double Matrix::dot(Matrix other){
  if(this->shape.width != other.shape.width || this->shape.height != other.shape.height ||
  (this->shape.width != 1 && this->shape.height != 1)){
    MatrixDimentionMissmatchError(this->shape, other.shape, "Dot product");
    return -1;
  }
  double sum = 0;
  if(this->shape.width == 1){
    for(int i = 0; i < this->shape.height; i++){
      sum += this->get(0, i) * other.get(0, i);
    }
  }
  else{
    for(int i = 0; i < this->shape.width; i++){
      sum += this->get(i, 0) * other.get(i, 0);
    }
  }
  return sum;
}

Matrix Matrix::cross(Matrix other){
  if(this->shape.width != 1 || this->shape.height != 3 || other.shape.width != 1 || other.shape.height != 3){
    MatrixDimentionMissmatchError(this->shape, other.shape, "Cross product");
    return Matrix();
  }
  Matrix m = Matrix(1, 3);
  m.set(0, 0, this->get(0, 1) * other.get(0, 2) - this->get(0, 2) * other.get(0, 1));
  m.set(0, 1, this->get(0, 2) * other.get(0, 0) - this->get(0, 0) * other.get(0, 2));
  m.set(0, 2, this->get(0, 0) * other.get(0, 1) - this->get(0, 1) * other.get(0, 0));
  return m;
}

double Matrix::distance(Matrix other){
  if(this->shape.width != other.shape.width || this->shape.height != other.shape.height ||
  (this->shape.width != 1 && this->shape.height != 1)){
    MatrixDimentionMissmatchError(this->shape, other.shape, "distance");
    return -1;
  }
  double sum = 0;
  if(this->shape.width == 1){
    for(int i = 0; i < this->shape.height; i++){
      sum += pow(this->get(0, i) - other.get(0, i), 2);
    }
  }
  else{
    for(int i = 0; i < this->shape.width; i++){
      sum += pow(this->get(i, 0) - other.get(i, 0), 2);
    }
  }
  return sqrt(sum);
}

double Matrix::homogDistance(Matrix other){
  if(this->shape.width != other.shape.width || this->shape.height != other.shape.height ||
  (this->shape.width != 1 && this->shape.height != 1)){
    MatrixDimentionMissmatchError(this->shape, other.shape, "homogenious distance");
    return -1;
  }
  double sum = 0;
  if(this->shape.width == 1){
    for(int i = 0; i < this->shape.height - 1; i++){
      sum += pow(this->get(0, i) - other.get(0, i), 2);
    }
  }
  else{
    for(int i = 0; i < this->shape.width - 1; i++){
      sum += pow(this->get(i, 0) - other.get(i, 0), 2);
    }
  }
  return sqrt(sum);
}

Matrix Matrix::operator+(Matrix p){
  if(this->shape.width != p.shape.width || this->shape.height != p.shape.height){
    MatrixDimentionMissmatchError(this->shape, p.shape, "Addition");
    return Matrix();
  }
  matrix_type m(p.shape.width, vector<double>(p.shape.height));
  for(int i = 0; i < p.shape.width; i++){
    for(int j = 0; j < p.shape.height; j++){
      m[i][j] = this->get(i, j) + p.get(i, j);
    }
  }
  return m;
}

Matrix Matrix::operator-(){
  Matrix m(this->shape);
  for(int i = 0; i < m.shape.width; i++){
    for(int j = 0; j < m.shape.height; j++){
      m.set(i, j, -this->get(i, j));
    }
  }
  return m;
}

Matrix Matrix::operator-(Matrix p){
  if(this->shape.width != p.shape.width || this->shape.height != p.shape.height){
    MatrixDimentionMissmatchError(this->shape, p.shape, "Subtraction");
    return Matrix();
  }
  matrix_type m(p.shape.width, vector<double>(p.shape.height));
  for(int i = 0; i < p.shape.width; i++){
    for(int j = 0; j < p.shape.height; j++){
      m[i][j] = this->get(i, j) - p.get(i, j);
    }
  }
  return Matrix(m);
}
Matrix Matrix::operator*(Matrix p){
  if(this->shape.width != p.shape.height){
    MatrixDimentionMissmatchError(this->shape, p.shape, "Multiplication");
    return Matrix();
  }
  int n_width = p.shape.width;
  int n_height = this->shape.height;
  int n = p.shape.height;
  matrix_type m(n_width, vector<double>(n_height));
  for(int i = 0; i < n_width; i++){
    for(int j = 0; j < n_height; j++){
      double sum = 0;
      for(int k = 0; k < n; k++){
        sum += this->get(k, j) * p.get(i, k);
      }
      m[i][j] = sum;
    }
  }
  return Matrix(m);
}

Matrix Matrix::operator*(double x){
  Matrix m(this->shape);
  for(int i = 0; i < m.shape.width; i++){
    for(int j = 0; j < m.shape.height; j++){
      m.set(i, j, this->_matrix[i][j] * x);
    }
  }
  return m;
}

Matrix Matrix::operator/(double x){
  Matrix m(this->shape);
  for(int i = 0; i < m.shape.width; i++){
    for(int j = 0; j < m.shape.height; j++){
      m.set(i, j, this->_matrix[i][j] / x);
    }
  }
  return m;
}
Matrix Matrix::copy(){
  Matrix m = Matrix(this->_matrix);
  return m;
}

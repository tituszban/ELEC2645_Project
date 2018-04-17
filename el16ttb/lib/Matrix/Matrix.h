#ifndef MATRIX
#define MATRIX

using namespace std;
#include <vector>
#include <math.h>

typedef std::vector<std::vector<double> > matrix_type;

struct Shape{
  int width;
  int height;
};


class Matrix{

public:
  Matrix();
  Matrix(matrix_type m);
  Matrix(Shape shape);
  Matrix(int width, int height);
  Matrix(int width, int height, double* m);
  //~Matrix();

  Shape shape;

  void print_matrix();

  void set(int w, int h, double v);
  double get(int w, int h);

  Matrix transpose();
  double dot(Matrix other);
  Matrix cross(Matrix other);
  double distance(Matrix other);
  double homogDistance(Matrix other);
  Matrix copy();

  //std::vector<double> operator[](int index); // getter only, not setter
  Matrix operator+(Matrix p);
  Matrix operator-();
  Matrix operator-(Matrix p);
  Matrix operator*(Matrix p);
  Matrix operator*(double x);
  Matrix operator/(double x);
private:
  void Setup(matrix_type m);
  matrix_type _matrix;
};

#endif

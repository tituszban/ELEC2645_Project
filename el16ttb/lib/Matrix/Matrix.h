#ifndef MATRIX
#define MATRIX

using namespace std;
#include <vector>
#include <math.h>

typedef std::vector<std::vector<float> > matrix_type;

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
  Matrix(int width, int height, float* m);
  //~Matrix();

  Shape shape;

  void print_matrix();

  void set(int w, int h, float v);
  float get(int w, int h);

  Matrix transpose();
  float dot(Matrix other);
  Matrix cross(Matrix other);
  float distance(Matrix other);
  float homogDistance(Matrix other);
  Matrix copy();

  //std::vector<float> operator[](int index); // getter only, not setter
  Matrix operator+(Matrix p);
  Matrix operator-();
  Matrix operator-(Matrix p);
  Matrix operator*(Matrix p);
  Matrix operator*(float x);
  Matrix operator/(float x);
private:
  void Setup(matrix_type m);
  matrix_type _matrix;
};

#endif

#ifndef UTIL
#define UTIL

using namespace std;

#include "Matrix.h"
#include <vector>
#include <utility>
#include <string>
#include "mbed.h"
// #include <Face.h>

struct Texture{
  int width;
  int height;
  vector<vector<int> > texture;
};

#define PI  3.14159265358979323846

Matrix pos2homogPos(Matrix pos);
vector<double> lerp(double a, double b, int length);
pair<Matrix, Matrix> getPerpVectors(Matrix fwd);
Texture arrayToTexture(int width, int height, const int* array);

#endif

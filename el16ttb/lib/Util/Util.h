#ifndef UTIL
#define UITL

using namespace std;

#include <Matrix.h>
#include <vector>
#include <utility>

#define PI  3.14159265358979323846

Matrix pos2homogPos(Matrix pos);
vector<double> lerp(double a, double b, int length);
pair<Matrix, Matrix> getPerpVectors(Matrix fwd);

#endif

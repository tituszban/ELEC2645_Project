#ifndef UTIL
#define UTIL

using namespace std;

#include "Matrix.h"
#include <vector>
#include <utility>
#include <algorithm>
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
vector<float> lerp(float a, float b, int length);
pair<Matrix, Matrix> getPerpVectors(Matrix fwd);
void memoryBenchmark(string id);
Texture arrayToTexture(int width, int height, const int* array);
Texture flipTexture(Texture tx, int d);
int sgn(int val);
int mod(int val, int m);

#endif

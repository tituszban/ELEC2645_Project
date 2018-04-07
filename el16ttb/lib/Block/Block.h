#ifndef BLOCK
#define BLOCK

#include <Matrix.h>
#include "mbed.h"

using namespace std;
#include <vector>

#define CORNER_N 8
#define EDGE_N 12


class Block{
public:
  Block(Matrix pos);
  Matrix position;
  vector< vector<Matrix> > getEdges();

private:
  Matrix _corners[CORNER_N];
};

#endif

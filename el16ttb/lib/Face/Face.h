#ifndef FACE
#define FACE

using namespace std;

#include <Matrix.h>
#include "mbed.h"
#include <Camera.h>
#include <Renderer.h>
#include <vector>
#include <utility>
#include <Util.h>
#include <math.h>

struct Texture{
  int width;
  int height;
  vector<vector<int> > texture;
};

class Face{

public:
  Face();
  Face(Matrix position, Matrix facing);
  void setTexture(Texture texture);
  void render(Camera &cam, Renderer &renderer);

private:
  Matrix position;
  Matrix facing;
  Texture texture;
  pair<pair<Matrix, Matrix>, pair<Matrix, Matrix> > corners;

  Texture getEmptyTexture();
};

#endif

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
  void setTexture(Texture texture);
  void setDirection(Matrix normal, Matrix up);
  void setPosition(Matrix position);
  void render(Camera &cam, Renderer &renderer);

private:
  Matrix position;
  Matrix normal;
  Matrix up;
  Texture texture;
  pair<pair<Matrix, Matrix>, pair<Matrix, Matrix> > corners;
  bool faceChanged;

  void updateCorners();

  Texture getEmptyTexture();
};

#endif

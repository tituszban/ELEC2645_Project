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

class Face{

public:
  Face();
  void setTexture(Texture texture);
  void setDirection(Matrix normal, Matrix up);
  void setPosition(Matrix position);
  void render(Camera &cam, Renderer &renderer);
  void setSize(float width, float height);

private:
  Matrix position;
  Matrix normal;
  Matrix up;
  Matrix left;
  Texture texture;
  float halfWidth;
  float halfHeight;
  pair<pair<Matrix, Matrix>, pair<Matrix, Matrix> > corners;
  bool faceChanged;

  void updateCorners();

  Texture getEmptyTexture();
};

#endif

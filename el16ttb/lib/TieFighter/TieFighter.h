#ifndef LIB_TIEFIGHTER_H_
#define LIB_TIEFIGHTER_H_

using namespace std;
#include <Face.h>
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <math.h>
#include <Util.h>


class TieFighter{
public:
  TieFighter();
  void setPosition(Matrix position);
  void setRotation(double rotation);
  void render(Camera &cam, Renderer &renderer);

private:
  Matrix position;
  double rotation;
  Matrix forward;
  Matrix left;
  Face wingL;
  Face wingLInside;
  Face wingR;
  Face wingRInside;
  Face cockpitFront;
  Face cockpitBack;
  Face cockpitTop;
  Face cockpitBottom;
  double wingSpan;
  double cockpitThickness;
  bool changed;
  double wingWidth;
  double wingHeight;


  void update();
};

const int wingSprite [] = {
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 1, 0, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
  1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
  1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1
};

const int wingInsideSprite [] = {
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 1, 0, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
   1, 1, 1, 1, 0, 0, 1, 1, 1,  1,
   1, 1, 1, 1, 1, 1, 1, 1, 1,  1,
   1, 1, 1, 1, 1, 1, 1, 1, 1,  1,
   1, 1, 1, 1, 1, 1, 1, 1, 1,  1,
   1, 1, 1, 1, 0, 0, 1, 1, 1,  1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1
};

const int cockpitFrontSprite [] = {
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1
};
const int cockpitBackSprite [] = {
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1
};
const int cockpitTopSprite [] = {
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1
};


#endif

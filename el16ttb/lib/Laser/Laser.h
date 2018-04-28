#ifndef LIB_LASER_H_
#define LIB_LASER_H_

using namespace std;
#include <Face.h>
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <math.h>
#include <Util.h>

#define MAX_LASER_DISTANCE 15

class Laser{
public:
  Laser();
  void setPosition(Matrix position);
  void setVelocity(Matrix velocity, Matrix up);
  void update(double dt);
  void render(Camera &cam, Renderer &renderer);
  bool toBeRemoved;
private:
  double width;
  double length;
  double speed;
  Matrix position;
  Matrix origin;
  Matrix velocity;
  Matrix forward;
  Matrix up;
  Face laserUp;
  Face laserDown;
};

const int laserSprite[] =	{
	1
};

#endif

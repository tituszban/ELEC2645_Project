#ifndef LIB_TIEFIGHTER_H_
#define LIB_TIEFIGHTER_H_

using namespace std;
#include <Face.h>
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <Util.h>
#include <math.h>
#include <vector>
#include <Laser.h>
#include <Explosion.h>


class TieFighter{
public:
  TieFighter();
  TieFighter(Matrix position, float rotation);
  void reset();
  void setPosition(Matrix position);
  void setRotation(float rotation);
  bool detectCollision(Matrix projectile);
  void render(Camera &cam, Renderer &renderer);
  void update(float dt, float steering, float elevation, bool fire);
  Matrix getPosition();
  float getRotation();
  Matrix getFacing();
  bool toBeRemoved;
  bool destroyed;

  vector<Laser> lasers;

private:
  void init();
  Matrix position;
  float rotation;
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
  float wingSpan;
  float cockpitThickness;
  bool changed;
  float wingWidth;
  float wingHeight;

  float steeringAngle;
  float elevationSpeed;
  float speed;
  float fireCooldown;
  float fireTimer;

  float outerHitboxRadius;
  float innerHitboxRadius;

  Explosion explosion;

  void update();

  vector<Laser> removedLasers;
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

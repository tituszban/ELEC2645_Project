#ifndef LIB_XWING_H_
#define LIB_XWING_H_

using namespace std;
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <Controller.h>
#include <Util.h>
#include <math.h>
#include <vector>
#include <Laser.h>
#include <UI.h>
#include <Lives.h>

#define MIN_SPEED 2.5
#define MAX_SPEED 5.0
#define SPEED_INCREMENT 2.0

#define MAX_DAMAGE 10
#define MIN_DAMAGE 5

class XWing{
public:
  XWing(Matrix position, Controller &cont);
  bool detectCollision(Matrix projectile);
  void update(float dt, Controller &cont, Camera &cam);
  void render(Camera &cam, Renderer &renderer);
  Matrix getPosition();

  vector<Laser> lasers;

private:
  UI ui;

  Matrix position;
  float yaw;
  float speed;

  float yawSpeed;
  float pitchAngle;

  int UIIndex;
  int UIcounter;

  float laserYOffset;
  float laserXOffset;


  float fireTimer;
  float fireCooldown;
  float fireDelay;
  int fireSequence;

  float outerHitboxRadius;
  float innerHitboxRadius;

  Lives lives;
};

#endif

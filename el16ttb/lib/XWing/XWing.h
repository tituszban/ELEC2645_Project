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
#include <SoundManager.h>

#define MIN_SPEED 1.5
#define MAX_SPEED 5.0
#define SPEED_INCREMENT 2.0

#define MAX_DAMAGE 15
#define MIN_DAMAGE 8

#define MISSION_DISTACNE 6.0
#define MISSION_SPEED 0.1

class XWing{
public:
  XWing(Matrix position, Controller &cont);
  bool detectCollision(Matrix projectile);
  void damage(float dam);
  void update(float dt, Controller &cont, Camera &cam, SoundManager &sm, int empireAction);
  void updateTargets(vector<int> targets, vector<Matrix> targetPositions);
  void render(Camera &cam, Renderer &renderer);
  Matrix getPosition();
  Matrix getFlatFacing();
  int isGameOver();

  vector<Laser> lasers;

private:
  UI ui;

  vector<Laser> removedLasers;

  Matrix position;
  Matrix facing;
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

  int target;
  int targetPre;
  bool canChangeTarget;
  vector<int> targets;
  vector<Matrix> targetPositions;

  bool missionActive;

  float progress;
  int progressIndicator;

  bool damaged;

  Lives lives;

  int smID1;
  int smID2;
};

#endif

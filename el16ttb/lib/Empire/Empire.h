#ifndef LIB_EMPIRE_H_
#define LIB_EMPIRE_H_

using namespace std;
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <Util.h>
#include <math.h>
#include <vector>
#include <TieFighter.h>
#include <ImperialShuttle.h>
#include <XWing.h>

class Empire{
public:
  Empire();

  bool isGameOver();
  int update(float dt, Matrix xwingPos, Matrix xwingFacing);
  void checkCollisions(XWing &xwing);
  vector<int> getTargets();
  vector<Matrix> getTargetPositions();
  Matrix getShuttlePosition();
  void render(Camera &cam, Renderer &renderer);

private:
  vector<TieFighter> tfs;
  vector<TieFighter> destroyedTFs;
  ImperialShuttle sh;

  void updateShuttle(float dt, Matrix xwingPos, Matrix xwingFacing);
  void updateTieFighter(float dt, Matrix xwingPos, Matrix xwingFacing, int tfi);
  void tfRoleManager();

  Matrix shHeading;
  float shSpeed;
  float shTimer;

  vector<int> tfRoles;
  vector<int> tfEvadeTarget;
  vector<char> tfMem;
  vector<float> tfCooldown;
  Matrix guardPattern;
  Matrix orbitPattern;
  float attackCooldown;
  float respawnTimer;
  int respawnCounter;
};

#endif

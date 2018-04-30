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
  void update(float dt, Matrix xwingPos);
  void checkCollisions(XWing &xwing);
  vector<int> getTargets();
  vector<Matrix> getTargetPositions();
  Matrix getShuttlePosition();
  void render(Camera &cam, Renderer &renderer);

private:
  vector<TieFighter> tfs;
  ImperialShuttle sh;
};

#endif

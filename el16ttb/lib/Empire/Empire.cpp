#include <Empire.h>

Empire::Empire(){
  float initialAngle = -PI * 0.3;
  float shInitialPos[] = {-1, 0.5, 12};
  float tfInitialPos[][3] = {
    {1, -1, 10},
    {3, 1, 14},
    {5, 0, 11},
    {4.5, 1, 6},
    {-4.5, 1, 6}
  };
  sh.setPosition(Matrix(1, 3, shInitialPos));
  sh.setRotation(initialAngle);
  for(int i = 0; i < 3; i++){
    TieFighter tf = TieFighter(Matrix(1, 3, tfInitialPos[i]), initialAngle);
    tfs.push_back(tf);
    tfRoles.push_back(-1);
    tfEvadeTarget.push_back(sh.getPosition());
    tfMem.push_back(0);
  }
  shTimer = 0;
  shHeading = Matrix(1, 3);
  // tfs[1].detectCollision(tfs[1].getPosition());
}

bool Empire::isGameOver(){
  return sh.toBeRemoved;
}

Matrix Empire::getShuttlePosition(){
  return sh.getPosition();
}

void Empire::checkCollisions(XWing &xwing)
{
  for(unsigned int i = 0; i < xwing.lasers.size(); i++){
    Matrix pos = xwing.lasers[i].getPosition();
    bool collided = sh.detectCollision(pos);
    for(unsigned int j = 0; j < tfs.size(); j++){
      if(!collided)
        collided = tfs[j].detectCollision(pos);
    }
    xwing.lasers[i].toBeRemoved = collided;
  }
  for(unsigned int i = 0; i < tfs.size(); i++){
    for(unsigned int j = 0; j < tfs[i].lasers.size(); j++){
      tfs[i].lasers[j].toBeRemoved = xwing.detectCollision(tfs[i].lasers[j].getPosition());
    }
  }
}

vector<int> Empire::getTargets(){
  vector<int> targets;
  targets.push_back(1);
  for(unsigned int i = 0; i < tfs.size(); i++)
  {
    targets.push_back(tfs[i].toBeRemoved ? -1 : (tfs[i].destroyed ? 2 : 0));
  }
  return targets;
}
vector<Matrix> Empire::getTargetPositions(){
  vector<Matrix> targetPositions;
  targetPositions.push_back(sh.getPosition());
  for(unsigned int i = 0; i < tfs.size(); i++)
  {
    targetPositions.push_back(tfs[i].getPosition());
  }
  return targetPositions;
}

void Empire::updateShuttle(float dt, Matrix xwingPos, Matrix xwingFacing){
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  float shSteer = 0;
  float shDist = sh.getPosition().distance(xwingPos);
  shTimer += dt;
  if(shDist < 4){
    shSteer = -xwingFacing.dot(sh.getFacing().cross(up)) * 1.4;
    shSpeed = 1.4f;
  }
  else if(shDist < 8){
    if(shTimer > 0.75){
      float rd = randf();
      shHeading = (xwingFacing * (randf() * 0.8f - 0.2f) + sh.getFacing().cross(up) * ((rd > 0.5) - (rd < 0.5) * (randf() * 2.0f + 1.0f)));
      shHeading = shHeading / shHeading.distance(Matrix(1, 3));
      shSpeed = randf();
      shTimer = 0;
    }
    shSteer = -shHeading.dot(sh.getFacing().cross(up));
  }
  else if(shDist > 30){
    Matrix rel = xwingPos - sh.getPosition();
    rel.set(0, 1, 0);
    rel = rel / rel.distance(Matrix(1, 3));
    shHeading = (rel + xwingFacing) * 0.5;
    shSteer = -shHeading.dot(sh.getFacing().cross(up));
  }
  else{
    shSpeed = 0;
  }
  sh.update(dt, shSteer, shSpeed);
}

void Empire::updateTieFighter(float dt, Matrix xwingPos, Matrix xwingFacing, int tfi){
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);

  if(xwingPos.distance(tfs[tfi].getPosition()) < 4){
    tfRoles[tfi] = 0;
    tfEvadeTarget[tfi] = xwingPos.getPosition();
  }
  else if(sh.distance(tfs[tfi].getPosition()) < 4)
  {
    tfRoles[tfi] = 0;
    tfEvadeTarget[tfi] = sh.getPosition();
  }
  float steer = 0;
  float elev = 0;

  if(tfRoles[tfi] == 0){
    Matrix rel = tfEvadeTarget[tfi] - tfs[tfi].getPosition();
    rel = rel / rel.distance(Matrix(1, 3));
    steer = -rel.dot(tfs[tfi].getFacing().cross(up));
  }

  tfs[tfi].update(dt, steer, elev, false);
}

/*
Roles:
-1 looking for role
0 evade
1 left guard
2 right guard
3 wide orbit
4 attack

*/

void Empire::tfRoleManager(){
  int roleCount[] = {0, 0, 0, 0, 0};
  bool hasToUpdate = false;
  for(unsigned int i = 0; i < tfs.size(); i++){
    if(tfRoles[i] == -1){ hasToUpdate = true; }
    else{ roleCount[tfRoles[i]]++; }
  }
  if(!hasToUpdate)
    return;
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  Matrix selector = Matrix(2, tfs.size());
  for(unsigned int i = 0; i < tfs.size(); i++){
    if(tfRoles[i] == -1){
      float shDist = sh.getPosition().distance(tfs[i].getPosition());
      Matrix shRel = tfs[i].getPosition() - sh.getPosition();
      float shSide = up.cross(sh.getFacing()).dot(shRel);
      selector.set(0, i, shDist + shSide);
      selector.set(1, i, shDist - shSide);
      printf("selector: i: %d shDist: %f\t, shSide: %f, 0: %f, 1: %f\n", i, shDist, shSide, shDist + shSide, shDist - shSide);
    }
  }
  if(roleCount[1] == 0 && roleCount[2] == 0){
    int minSide = 0;
    int mintf = 0;
    for(unsigned int i = 0; i < tfs.size(); i++){
      if(selector.get(0, i) < selector.get(minSide, mintf)){
        mintf = i;
        minSide = 0;
      }
      if(selector.get(1, i) < selector.get(minSide, mintf)){
        mintf = i;
        minSide = 1;
      }
    }
    if(selector.get(minSide, mintf) > 0){
      tfRoles[mintf] = minSide + 1;
      int minRowtf = 0;
      for(unsigned int i = 0; i < tfs.size(); i++){
        if(selector.get(1 - minSide, i) < selector.get(1 - minSide, minRowtf))
          minRowtf = i;
      }
      if(selector.get(1 - minSide, minRowtf) > 0)
        tfRoles[minRowtf] = 2 - minSide;
    }
  }
  else if(roleCount[1] == 0){
    int minRowtf = 0;
    for(unsigned int i = 0; i < tfs.size(); i++){
      if(selector.get(0, i) < selector.get(0, minRowtf))
        minRowtf = i;
    }
    if(selector.get(0, minRowtf) > 0)
      tfRoles[minRowtf] = 1;
  }
  else if(roleCount[2] == 0){
    int minRowtf = 0;
    for(unsigned int i = 0; i < tfs.size(); i++){
      if(selector.get(1, i) < selector.get(1, minRowtf))
        minRowtf = i;
    }
    if(selector.get(1, minRowtf) > 0)
      tfRoles[minRowtf] = 2;
  }
  for(unsigned int i = 0; i < tfs.size(); i++){
    if(tfRoles[i] == -1)
      tfRoles[i] = 3;
    printf("Role: i: %d, r: %d\n", i, tfRoles[i]);
  }
}

void Empire::update(float dt, Matrix xwingPos, Matrix xwingFacing)
{
  tfRoleManager();
  updateShuttle(dt, xwingPos, xwingFacing);
  unsigned int tf = 0;
  while(tf < tfs.size()){
    if(tfs[tf].toBeRemoved){
      tfs.erase(tfs.begin() + tf);
      tfRoles.erase(tfRoles.begin() + tf);
      tfEvadeTarget.erase(tfEvadeTarget.begin() + tf);
    }
    else{
      updateTieFighter(dt, xwingPos, xwingFacing, tf);
      unsigned int i = 0;
      while(i < tfs[tf].lasers.size()){
        if(tfs[tf].lasers[i].toBeRemoved){
          tfs[tf].lasers.erase(tfs[tf].lasers.begin() + i);
        }
        else{
          tfs[tf].lasers[i].update(dt);
          i++;
        }
      }
      tf++;
    }
  }
}

void Empire::render(Camera &cam, Renderer &renderer)
{
  sh.render(cam, renderer);
  for(unsigned int i = 0; i < tfs.size(); i++)
  {
    tfs[i].render(cam, renderer);
  }
}

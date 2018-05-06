#include <Empire.h>

Empire::Empire(){
  float initialAngle = -PI * 0.3;
  float shInitialPos[] = {-1, 0, 12};
  float tfInitialPos[][3] = {
    {1, 0.2, 10},
    {0, -1, 14},
    {5, 0, 11},
    {4.5, 1, 6},
    {-4.5, 1, 6}
  };
  float guardPoses[] = {
    3, -3,
    3, 3,
    6, 0
  };
  guardPattern = Matrix(2, 3, guardPoses);
  float orbitPoses[] = {
    10, 0,
    0, 10,
    -10, 0,
    0, -10
  };
  orbitPattern = Matrix(2, 4, orbitPoses);
  attackCooldown = 0;
  respawnTimer = 0;
  respawnCounter = 0;
  sh.setPosition(Matrix(1, 3, shInitialPos));
  sh.setRotation(initialAngle);
  for(int i = 0; i < 2; i++){
    TieFighter tf = TieFighter(Matrix(1, 3, tfInitialPos[i]), initialAngle);
    tfs.push_back(tf);
    tfRoles.push_back(-1);
    tfEvadeTarget.push_back(0);
    tfMem.push_back(0);
    tfCooldown.push_back(0);
    tfXDist.push_back(0);
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
    if(tfs[i].getPosition().distance(xwing.getPosition()) < 1.2 && !tfs[i].destroyed){
      tfs[i].detectCollision(tfs[i].getPosition());
      xwing.damage(50.0f);
    }
  }
  if(sh.getPosition().distance(xwing.getPosition()) < 1.2){
    xwing.damage(100.0f);
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

void Empire::updateShuttle(float dt, Matrix xwingPos, Matrix xwingFacing, SoundManager &sm){
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  float shSteer = 0;
  float shDist = sh.getPosition().distance(xwingPos);
  shTimer += dt;
  if(shDist < 4){
    shSteer = -xwingFacing.dot(sh.getFacing().cross(up)) * 1.4;
    shSpeed = 1.4f;
  }
  else if(shDist < 6){
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
    shSteer = -rel.dot(sh.getFacing().cross(up));
  }
  else{
    shSpeed = 0;
  }
  sh.update(dt, shSteer, shSpeed, sm);
}

void Empire::updateTieFighter(float dt, Matrix xwingPos, Matrix xwingFacing, int tfi, SoundManager &sm){
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  float xwingDist = xwingPos.distance(tfs[tfi].getPosition());
  float relSpeed = (xwingDist - tfXDist[tfi]) / dt;
  tfXDist[tfi] = xwingDist;
  Matrix xRel = xwingPos - tfs[tfi].getPosition();
  float xRelY = xRel.get(0, 1);
  xRel.set(0, 1, 0);
  xRel = xRel / xRel.distance(Matrix(1, 3));
  if(tfCooldown[tfi] > 0)
    tfCooldown[tfi] -= dt;

  if(xwingDist < 7){
    tfRoles[tfi] = 0;
    tfEvadeTarget[tfi] = 0;
  }
  else if(sh.getPosition().distance(tfs[tfi].getPosition()) < 2)
  {
    tfRoles[tfi] = 0;
    tfEvadeTarget[tfi] = 1;
  }
  else if(xwingDist < 15){
    int roleCount[] = {0, 0, 0, 0, 0};
    for(unsigned int i = 0; i < tfs.size(); i++){
      if(tfRoles[i] != -1){ roleCount[tfRoles[i]]++;}
    }
    if(roleCount[4] == 0 && (roleCount[1] + roleCount[2] > 1
      || (tfRoles[tfi] != 1 && tfRoles[tfi] != 2)
      || tfs.size() == 1) && tfCooldown[tfi] <= 0 && attackCooldown <= 0){
      tfRoles[tfi] = 4;
    }
  }

  float steer = 0;
  float elev = 0;

  if(tfRoles[tfi] == 0){
    Matrix evade = tfEvadeTarget[tfi] == 0 ? xwingPos : sh.getPosition();
    Matrix rel = tfs[tfi].getPosition() - evade;
    rel = rel / rel.distance(Matrix(1, 3));
    steer = -rel.dot(tfs[tfi].getFacing().cross(up));
    if(evade.distance(tfs[tfi].getPosition()) > 8){
      tfRoles[tfi] = -1;
      tfCooldown[tfi] = 1;
    }
  }
  if(tfRoles[tfi] == 1 || tfRoles[tfi] == 2){
    Matrix target = sh.getPosition()
      + sh.getFacing() * guardPattern.get(1, tfMem[tfi])
      + up.cross(sh.getFacing()) * guardPattern.get(0, tfMem[tfi]) * (tfRoles[tfi] == 1 ? 1 : -1);
    if(target.distance(tfs[tfi].getPosition()) < 0.3f){tfMem[tfi] = (tfMem[tfi] + 1) % 3; }
    // printf("Left guard: i: %d, dist %f, t: %d\n", tfi, target.distance(tfs[tfi].getPosition()), tfMem[tfi]);
    Matrix rel = target - tfs[tfi].getPosition();
    float relY = rel.get(0, 1);
    rel.set(0, 1, 0);
    rel = rel / rel.distance(Matrix(1, 3));
    steer = -rel.dot(tfs[tfi].getFacing().cross(up));
    elev = relY;
  }
  if(tfRoles[tfi] == 3){
    Matrix target = sh.getPosition()
      + sh.getFacing() * orbitPattern.get(1, tfMem[tfi])
      + up.cross(sh.getFacing()) * orbitPattern.get(0, tfMem[tfi]);
    if(target.distance(tfs[tfi].getPosition()) < 0.3f){tfMem[tfi] = (tfMem[tfi] + 1) % 4; }
    Matrix rel = target - tfs[tfi].getPosition();
    // float relY = rel.get(0, 1);
    rel.set(0, 1, 0);
    rel = rel / rel.distance(Matrix(1, 3));
    steer = -rel.dot(tfs[tfi].getFacing().cross(up));
  }
  if(tfRoles[tfi] == 4){
    Matrix target = xRel + xwingFacing * 0.2;
    target = target / target.distance(Matrix(1, 3));
    steer = -xRel.dot(tfs[tfi].getFacing().cross(up));
    elev = xRelY;
    attackCooldown = 2;
  }


  bool fire = xRel.dot(tfs[tfi].getFacing()) > 0.8f && xwingDist < 20;

  tfs[tfi].update(dt, steer, elev, fire, sm);
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
      // printf("selector: i: %d shDist: %f\t, shSide: %f, 0: %f, 1: %f\n", i, shDist, shSide, shDist + shSide, shDist - shSide);
    }
    else{
      selector.set(0, i, 9999999);
      selector.set(1, i, 9999999);
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
    if(selector.get(minSide, mintf) < 9999999){
      tfRoles[mintf] = minSide + 1;
      int minRowtf = 0;
      for(unsigned int i = 0; i < tfs.size(); i++){
        if(selector.get(1 - minSide, i) < selector.get(1 - minSide, minRowtf))
          minRowtf = i;
      }
      if(selector.get(1 - minSide, minRowtf) < 9999999)
        tfRoles[minRowtf] = 2 - minSide;
    }
  }
  else if(roleCount[1] == 0){
    int minRowtf = 0;
    for(unsigned int i = 0; i < tfs.size(); i++){
      if(selector.get(0, i) < selector.get(0, minRowtf))
        minRowtf = i;
    }
    if(selector.get(0, minRowtf) < 9999999)
      tfRoles[minRowtf] = 1;
  }
  else if(roleCount[2] == 0){
    int minRowtf = 0;
    for(unsigned int i = 0; i < tfs.size(); i++){
      if(selector.get(1, i) < selector.get(1, minRowtf))
        minRowtf = i;
    }
    if(selector.get(1, minRowtf) < 9999999)
      tfRoles[minRowtf] = 2;
  }
  for(unsigned int i = 0; i < tfs.size(); i++){
    if(tfRoles[i] == -1)
      tfRoles[i] = 3;
    // printf("Role: i: %d, r: %d\n", i, tfRoles[i]);
  }
}

int Empire::update(float dt, Matrix xwingPos, Matrix xwingFacing, SoundManager &sm)
{
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  tfRoleManager();
  updateShuttle(dt, xwingPos, xwingFacing, sm);
  int action = 0;
  if(attackCooldown > 0)
    attackCooldown -= dt;
  unsigned int tf = 0;
  while(tf < tfs.size()){
    if(tfs[tf].toBeRemoved){
      destroyedTFs.push_back(tfs[tf]);
      tfs.erase(tfs.begin() + tf);
      tfRoles.erase(tfRoles.begin() + tf);
      tfEvadeTarget.erase(tfEvadeTarget.begin() + tf);
      tfMem.erase(tfMem.begin() + tf);
      tfCooldown.erase(tfCooldown.begin() + tf);
      tfXDist.erase(tfXDist.begin() + tf);
    }
    else{
      updateTieFighter(dt, xwingPos, xwingFacing, tf, sm);
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
  // printf("Most of it is still working\n");
  if(tfs.size() == 0){
    respawnTimer += dt;
  }
  if(respawnTimer > 4 + respawnCounter + randf()){
    respawnTimer = 0;
    Matrix spawnPoint = sh.getPosition() - xwingPos;
    spawnPoint = spawnPoint / spawnPoint.distance(Matrix(1, 3));
    Matrix spawnOffset = up.cross(spawnPoint);
    float offset[] = {25, -25};
    // memoryBenchmark("ressurect tie fighters");
    for(int i = 0; i < 2; i++){
      destroyedTFs[0].reset();
      destroyedTFs[0].setPosition(spawnPoint * (randf() * 0.5f + 0.5f) * 25 + sh.getPosition() + spawnOffset * offset[i]);
      // memoryBenchmark("about to read tf");
      tfs.push_back(destroyedTFs[0]);
      // memoryBenchmark("tf readded");
      tfRoles.push_back(-1);
      tfEvadeTarget.push_back(0);
      tfMem.push_back(0);
      tfCooldown.push_back(0);
      tfXDist.push_back(0);
      // printf("Everything repopulated\n");
      destroyedTFs.erase(destroyedTFs.begin());
      // printf("Zombie removed\n");
    }
    respawnCounter++;
    action = 1;
  }
  return action;
}

void Empire::render(Camera &cam, Renderer &renderer)
{
  sh.render(cam, renderer);
  for(unsigned int i = 0; i < tfs.size(); i++)
  {
    tfs[i].render(cam, renderer);
  }
}

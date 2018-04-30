#include <Empire.h>

Empire::Empire(){
  float shInitialPos[] = {0, 0.5, 10};
  float tfInitialPos[][3] = {
    {3, 0, 5},
    {-3, 0, 5},
    {0, -2, 5},
    {4.5, 1, 6},
    {-4.5, 1, 6}
  };
  sh.setPosition(Matrix(1, 3, shInitialPos));
  sh.setRotation(0);
  for(int i = 0; i < 3; i++){
    TieFighter tf = TieFighter(Matrix(1, 3, tfInitialPos[i]), 0);
    tfs.push_back(tf);
  }
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

void Empire::update(float dt, Matrix xwingPos)
{
  sh.update(dt, 0);
  unsigned int tf = 0;
  while(tf < tfs.size()){
    if(tfs[tf].toBeRemoved){
      tfs.erase(tfs.begin() + tf);
    }
    else{
      tfs[tf].update(dt, 0, 0, false);
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

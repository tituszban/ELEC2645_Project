#include "XWing.h"

XWing::XWing(Matrix position, Controller &cont){
  this->position = position;
  yawSpeed = PI;
  pitchAngle = PI * 0.16667;
  yaw = 0;
  speed = 0.5;
  UIIndex = 0;
  UIcounter = 0;
  laserYOffset = -0.1;
  laserXOffset = 0.5;
  fireCooldown = 0.6;
  fireTimer = fireCooldown;
  fireDelay = 0.1;
  fireSequence = 5;
  lives = Lives(cont);
  lives.reset();
  target = 0;
  targetPre = 0;
  canChangeTarget = false;
  progress = 0;
  progressIndicator = 0;
  innerHitboxRadius = 0.6;
  outerHitboxRadius = 1.2;
  smID1 = -1;
  smID2 = -1;
  damaged = false;
}

bool XWing::detectCollision(Matrix projectile){
  float dist = position.distance(projectile);
  float rn = (float)rand() / RAND_MAX;
  if(dist < innerHitboxRadius || (dist - innerHitboxRadius) / (outerHitboxRadius - innerHitboxRadius) < rn){
    lives.damage((float)rand() / RAND_MAX * (MAX_DAMAGE - MIN_DAMAGE) + MIN_DAMAGE);
    printf("OUCH!\n");
    damaged = true;
    return true;
  }
  return false;
}

void XWing::damage(float dam){
  lives.damage(dam);
}

void XWing::update(float dt, Controller &cont, Camera &cam, SoundManager &sm, int empireAction){
  if(empireAction == 1)
    ui.setAlert(1);

  speed = min(max(
    speed + ((cont.buttonDown(Y) ? SPEED_INCREMENT : 0.0) + (cont.buttonDown(A) ? -SPEED_INCREMENT : 0.0)) * dt,
    0.0), 1.0);
  yaw += pow(cont.joystickCoord().x, 5) * -yawSpeed * dt;
  float pitch = -cont.joystickCoord().y * pitchAngle;
  cam.setRotation(pitch, yaw);
  cam.setPosition(position.get(0, 0), position.get(0, 1), position.get(0, 2));
  position = position + cam.getFacing() * dt * ((MAX_SPEED - MIN_SPEED) * speed + MIN_SPEED);
  facing = cam.getFacing();
  fireTimer += dt;

  if(smID1 == -1){smID1 = sm.getID();}
  if(smID2 == -1){smID2 = sm.getID();}
  // printf("id1: %d, id2: %d\n", smID1, smID2);

  if(fireTimer >= fireCooldown && cont.buttonDown(R)){
    fireTimer = 0;
    fireSequence = 0;

    if(removedLasers.size() > 0){
      removedLasers[0].reset();
      removedLasers[0].setPosition(position + cam.getUp() * laserYOffset + cam.getFacing().cross(cam.getUp()) * laserXOffset);
      removedLasers[0].setVelocity(cam.getFacing(), cam.getUp());
      lasers.push_back(removedLasers[0]);
      removedLasers.erase(removedLasers.begin());
    }
    else{
      Laser laser = Laser();
      laser.setPosition(position + cam.getUp() * laserYOffset + cam.getFacing().cross(cam.getUp()) * laserXOffset);
      laser.setVelocity(cam.getFacing(), cam.getUp());
      lasers.push_back(laser);
    }
    cont.lcdSetBrightness(1);
    sm.setEffect(smID1, 10, 0.4, 800, 600);
  }
  else if(fireTimer > 0.05 && fireSequence == 0){
    fireSequence++;
    cont.lcdSetBrightness(cont.brightness);
  }
  else if(fireTimer > fireDelay && fireSequence == 1){
    fireSequence++;
    if(removedLasers.size() > 0){
      removedLasers[0].reset();
      removedLasers[0].setPosition(position + cam.getUp() * laserYOffset - cam.getFacing().cross(cam.getUp()) * laserXOffset);
      removedLasers[0].setVelocity(cam.getFacing(), cam.getUp());
      lasers.push_back(removedLasers[0]);
      removedLasers.erase(removedLasers.begin());
    }
    else{
      Laser laser = Laser();
      laser.setPosition(position + cam.getUp() * laserYOffset - cam.getFacing().cross(cam.getUp()) * laserXOffset);
      laser.setVelocity(cam.getFacing(), cam.getUp());
      lasers.push_back(laser);
    }
    cont.lcdSetBrightness(1);
    sm.setEffect(smID1, 10, 0.4, 800, 600);
  }
  else if(fireTimer > fireDelay + 0.05 && fireSequence == 2){
    fireSequence++;
    cont.lcdSetBrightness(cont.brightness);
  }
  else if(fireTimer > fireCooldown - fireDelay && fireSequence == 3){
    fireSequence++;
  }
  else if(fireTimer >= fireCooldown){
    fireSequence = 5;
  }

  unsigned int i = 0;
  while(i < lasers.size()){
    if(lasers[i].toBeRemoved){
      removedLasers.push_back(lasers[i]);
      lasers.erase(lasers.begin() + i);
    }
    else{
      lasers[i].update(dt);
      i++;
    }
  }
  if(canChangeTarget)
    target += cont.buttonPressed(X) - cont.buttonPressed(B);

  ui.setMissionActive(missionActive);
  if(missionActive){
    if(cont.buttonDown(L)){
      progress += MISSION_SPEED * dt;
      float pex = pow(progress, 1.5);
      if(floor(pex * 300.0f) != progressIndicator){
        progressIndicator = floor(pex * 300.0f);
        if(mod(progressIndicator, 8) == 0){
          sm.setEffect(smID1, 10, 0.2, 500, 500);
        }
      }
    }
  }
  if(damaged){
    damaged = false;
    sm.setEffect(smID2, 10, 0.5, 100, 300);
  }
  lives.update();
}

void XWing::updateTargets(vector<int> targets, vector<Matrix> targetPositions){
  bool targetExploded = false;
  bool proximityAlert = false;
  unsigned int i = 0;
  int a = 0;
  while(i < targets.size()){
    if(targets[i] == -1){
      targets.erase(targets.begin() + i);
      targetPositions.erase(targetPositions.begin() + i);
      if(a == target){
        targetExploded = true;
      }
      if(a < target){
        target--;
      }
    }
    else{
      if(targetPositions[i].distance(position) < 1.7 && targets[i] != 2)
        proximityAlert = true;
      i++;
    }
    a++;
  }
  if(targetExploded){
    target = 0;
    targetPre = 0;
    ui.setTarget(0);
  }
  canChangeTarget = targets.size() > 1;

  this->targets = targets;
  this->targetPositions = targetPositions;

  missionActive = position.distance(targetPositions[0]) < MISSION_DISTACNE && !canChangeTarget;
  if(proximityAlert)
    ui.setAlert(0);
}

int XWing::isGameOver(){
  return lives.isGameOver() ? -1 : (progress >= 1 ? 1 : 0);
}

void XWing::render(Camera &cam, Renderer &renderer){
  int bar = int(5.0 * speed);
  ui.setBars(bar, bar);

  if(target != targetPre){
    if(ui.setNextTarget(targets[mod(target, targets.size())], target - targetPre)){
      targetPre += sgn(target - targetPre);
      target = mod(target, targets.size());
      targetPre = mod(targetPre, targets.size());
    }
  }
  else if(ui.targetProgress == 0){
    ui.setTarget(targets[mod(target, targets.size())]);
  }

  int leftIndicator[] = {0, 0, 0, 0, 1, 1};
  int rightIndicator[] = {1, 1, 0, 0, 0, 1};
  ui.setFire(leftIndicator[fireSequence], rightIndicator[fireSequence]);
  ui.missionProgress(floor(10.0f * progress));
  ui.setDir(progressIndicator);

  Matrix targetPos = targetPositions[mod(target, targets.size())];
  Matrix screenPoint = cam.getScreenPosition(pos2homogPos(targetPos));
  float d = screenPoint.get(0, 2);
  int x = round(screenPoint.get(0, 0));
  int y = round(screenPoint.get(0, 1));
  if(!(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT || d < 0)){
    if(d > RENDER_DISTANCE * 0.7f){
      ui.setTargetVisibility(1);
      ui.setFarTargetPos(x, y);
    }
    else{
      ui.setTargetVisibility(0);
    }
  }
  else{
    ui.setTargetVisibility(2);
    Matrix rel = (targetPos - position);
    rel = rel / rel.distance(Matrix(1, 3));
    Matrix proj = rel - cam.getFacing() * rel.dot(cam.getFacing());
    float y = proj.dot(cam.getUp());
    float x = proj.dot(cam.getUp().cross(cam.getFacing()));
    if(abs(x) > abs(y)){
      ui.setOffscreenTarget(x > 0 ? 0 : 2, y);
    }
    else{
      ui.setOffscreenTarget(y > 0 ? 1 : 3, x);
    }
  }

  ui.render(UIIndex, renderer);
  if(UIcounter++ % 10 == 0)
    UIIndex++;
  for(unsigned int i = 0; i < lasers.size(); i++){
    lasers[i].render(cam, renderer);
  }
}
Matrix XWing::getPosition(){
  return position;
}

Matrix XWing::getFlatFacing(){
  Matrix fFacing = facing.copy();
  fFacing.set(0, 1, 0);
  fFacing = fFacing / fFacing.distance(Matrix(1, 3));
  return fFacing;
}

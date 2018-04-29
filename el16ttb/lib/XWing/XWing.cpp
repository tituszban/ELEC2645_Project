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
}

bool XWing::detectCollision(Matrix projectile){
  double dist = position.distance(projectile);
  double rn = (double)rand() / RAND_MAX;
  if(dist < innerHitboxRadius || (dist - innerHitboxRadius) / (outerHitboxRadius - innerHitboxRadius) < rn){
    lives.damage((double)rand() / RAND_MAX * (MAX_DAMAGE - MIN_DAMAGE) + MIN_DAMAGE);
    return true;
  }
  return false;
}

void XWing::update(double dt, Controller &cont, Camera &cam){
  speed = min(max(
    speed + ((cont.buttonDown(Y) ? SPEED_INCREMENT : 0.0) + (cont.buttonDown(A) ? -SPEED_INCREMENT : 0.0)) * dt,
    0.0), 1.0);
  // printf("Speed: %f\n", speed);
  yaw += pow(cont.joystickCoord().x, 3) * -yawSpeed * dt;
  double pitch = -cont.joystickCoord().y * pitchAngle;
  cam.setRotation(pitch, yaw);
  cam.setPosition(position.get(0, 0), position.get(0, 1), position.get(0, 2));
  position = position + cam.getFacing() * dt * ((MAX_SPEED - MIN_SPEED) * speed + MIN_SPEED);
  fireTimer += dt;
  if(fireTimer >= fireCooldown && cont.buttonDown(R)){
    fireTimer = 0;
    fireSequence = 0;
    Laser laser = Laser();

    laser.setPosition(position + cam.getUp() * laserYOffset + cam.getFacing().cross(cam.getUp()) * laserXOffset);
    laser.setVelocity(cam.getFacing(), cam.getUp());
    lasers.push_back(laser);
    cont.lcdSetBrightness(1);
  }
  else if(fireTimer > 0.05 && fireSequence == 0){
    fireSequence++;
    cont.lcdSetBrightness(0.5);
  }
  else if(fireTimer > fireDelay && fireSequence == 1){
    fireSequence++;
    Laser laser = Laser();
    laser.setPosition(position + cam.getUp() * laserYOffset - cam.getFacing().cross(cam.getUp()) * laserXOffset);
    laser.setVelocity(cam.getFacing(), cam.getUp());
    lasers.push_back(laser);
    cont.lcdSetBrightness(1);
  }
  else if(fireTimer > fireDelay + 0.05 && fireSequence == 2){
    fireSequence++;
    cont.lcdSetBrightness(0.5);
  }
  else if(fireTimer > fireCooldown - fireDelay && fireSequence == 3){
    fireSequence++;
  }
  else if(fireTimer >= fireCooldown){
    fireSequence = 5;
  }

  unsigned int i = 0;
  while(i < lasers.size()){
    // printf("remove?: %d\n", lasers[i].toBeRemoved);
    if(lasers[i].toBeRemoved){
      lasers.erase(lasers.begin() + i);
    }
    else{
      lasers[i].update(dt);
      i++;
    }
  }
}

void XWing::render(Camera &cam, Renderer &renderer){
  int bar = int(5.0 * speed);
  ui.setBars(bar, bar);

  int leftIndicator[] = {0, 0, 0, 0, 1, 1};
  int rightIndicator[] = {1, 1, 0, 0, 0, 1};
  ui.setFire(leftIndicator[fireSequence], rightIndicator[fireSequence]);

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

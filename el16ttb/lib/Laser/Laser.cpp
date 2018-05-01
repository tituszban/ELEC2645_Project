#include "Laser.h"

Laser::Laser(){
  reset();

  Texture laserTexture = arrayToTexture(1, 1, laserSprite);
  laserUp.setTexture(laserTexture);
  laserUp.setSize(width, length);
  laserDown.setTexture(laserTexture);
  laserDown.setSize(width, length);
}

void Laser::reset(){
  width = 0.1;
  length = 0.5;
  speed = 20;
  toBeRemoved = false;
}

void Laser::setPosition(Matrix position){
  this->position = position;
  this->origin = position;
}

void Laser::setVelocity(Matrix velocity, Matrix up){
  this->velocity = velocity * speed;
  this->up = up;
  forward = velocity / velocity.distance(Matrix(1, 3));
}

void Laser::update(float dt){
  position = position + velocity * dt;
  if(origin.distance(position) > MAX_LASER_DISTANCE){
    toBeRemoved = true;
  }
  laserUp.setPosition(position);
  laserUp.setDirection(up, forward);
  laserDown.setPosition(position);
  laserDown.setDirection(-up, forward);
}

void Laser::render(Camera &cam, Renderer &renderer){
  if(toBeRemoved)
    return;
  laserUp.render(cam, renderer);
  laserDown.render(cam, renderer);
}

Matrix Laser::getPosition(){
  return position;
}

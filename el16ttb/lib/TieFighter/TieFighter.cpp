#include <TieFighter.h>

TieFighter::TieFighter(){
  wingSpan = 0.425;
  cockpitThickness = 0.2;
  wingWidth = 1;
  wingHeight = 1.5;

  steeringAngle = PI * 2;
  speed = 4;
  elevationSpeed = 1;
  fireCooldown = 1;

  destroyed = false;
  innerHitboxRadius = 0.425;
  outerHitboxRadius = 1;

  toBeRemoved = false;

  setPosition(Matrix(1, 3));
  setRotation(0);

  wingL.setTexture(arrayToTexture(10, 15, wingSprite));
  wingL.setSize(wingWidth, wingHeight);
  wingR.setTexture(arrayToTexture(10, 15, wingSprite));
  wingR.setSize(wingWidth, wingHeight);
  wingLInside.setTexture(arrayToTexture(10, 15, wingInsideSprite));
  wingLInside.setSize(wingWidth, wingHeight);
  wingRInside.setTexture(arrayToTexture(10, 15, wingInsideSprite));
  wingRInside.setSize(wingWidth, wingHeight);
  cockpitFront.setTexture(arrayToTexture(15, 5, cockpitFrontSprite));
  cockpitFront.setSize(wingSpan * 2, cockpitThickness * 2);
  cockpitBack.setTexture(arrayToTexture(15, 5, cockpitBackSprite));
  cockpitBack.setSize(wingSpan * 2, cockpitThickness * 2);
  cockpitTop.setTexture(arrayToTexture(15, 5, cockpitTopSprite));
  cockpitTop.setSize(wingSpan * 2, cockpitThickness * 2);
  cockpitBottom.setTexture(arrayToTexture(15, 5, cockpitTopSprite));
  cockpitBottom.setSize(wingSpan * 2, cockpitThickness * 2);
}

void TieFighter::setPosition(Matrix position){
  this->position = position;
  changed = true;
}

void TieFighter::setRotation(double rotation){
  this->rotation = rotation;
  double si = sin(rotation);
  double co = cos(rotation);
  double fwd[] = {si, 0, co};
  double lft[] = {-co, 0, si};
  forward = Matrix(1, 3, fwd);
  left = Matrix(1, 3, lft);
  changed = true;
}

bool TieFighter::detectCollision(Matrix projectile){
  double dist = position.distance(projectile);
  double rn = (double)rand() / RAND_MAX;
  if((dist < innerHitboxRadius || (dist - innerHitboxRadius) / (outerHitboxRadius - innerHitboxRadius) < rn) && !destroyed){
    destroyed = true;
    explosion.setPosition(position);
    explosion.setSize(2.5);
    return true;
  }
  return false;
}

void TieFighter::update(double dt, double steering, double elevation, bool fire){
  if(!destroyed){
    double u[] = {0, 1, 0};
    Matrix up = Matrix(1, 3, u);
    steering = min(max(steering, -1.0), 1.0);
    elevation = min(max(elevation, -1.0), 1.0);
    setRotation(rotation + steering * steeringAngle * dt);
    setPosition(position + (forward * speed + up * elevation * elevationSpeed) * dt);
    fireTimer += dt;
    if(fireTimer >= fireCooldown && fire){
      fireTimer = 0;
      Laser laser = Laser();
      laser.setPosition(position + forward * 0.2);
      laser.setVelocity(forward, up);
      lasers.push_back(laser);
    }
  }
  else{
    explosion.update(dt);
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
  if(explosion.toBeRemoved && lasers.size() <= 0){
    toBeRemoved = true;
  }
}

Matrix TieFighter::getPosition(){
  return position;
}
double TieFighter::getRotation(){
  return rotation;
}

void TieFighter::update(){
  double u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  wingL.setPosition(position + left * wingSpan);
  wingL.setDirection(left, up);
  wingLInside.setPosition(position + left * wingSpan);
  wingLInside.setDirection(-left, up);
  wingR.setPosition(position - left * wingSpan);
  wingR.setDirection(-left, up);
  wingRInside.setPosition(position - left * wingSpan);
  wingRInside.setDirection(left, up);

  cockpitFront.setPosition(position + forward * cockpitThickness);
  cockpitFront.setDirection(forward, up);
  cockpitBack.setPosition(position - forward * cockpitThickness);
  cockpitBack.setDirection(-forward, up);
  cockpitTop.setPosition(position + up * cockpitThickness * 0.6);
  cockpitTop.setDirection(up, forward);
  cockpitBottom.setPosition(position - up * cockpitThickness * 0.6);
  cockpitBottom.setDirection(-up, forward);
}

void TieFighter::render(Camera &cam, Renderer &renderer){
  if(toBeRemoved)
    return;
  if(!destroyed){
    if(changed)
      update();
    wingL.render(cam, renderer);
    wingLInside.render(cam, renderer);
    wingR.render(cam, renderer);
    wingRInside.render(cam, renderer);
    cockpitFront.render(cam, renderer);
    cockpitBack.render(cam, renderer);
    cockpitTop.render(cam, renderer);
    cockpitBottom.render(cam, renderer);
  }
  else{
    explosion.render(cam, renderer);
  }

  for(unsigned int i = 0; i < lasers.size(); i++){
    lasers[i].render(cam, renderer);
  }
}

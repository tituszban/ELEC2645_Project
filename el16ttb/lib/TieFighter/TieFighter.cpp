#include <TieFighter.h>

TieFighter::TieFighter(){
  this->wingSpan = 0.425;
  this->cockpitThickness = 0.2;
  this->wingWidth = 1;
  this->wingHeight = 1.5;
  this->setPosition(Matrix(1, 3));
  this->setRotation(0);

  wingL.setTexture(arrayToTexture(10, 15, wingSprite));
  wingL.setSize(this->wingWidth, this->wingHeight);
  wingR.setTexture(arrayToTexture(10, 15, wingSprite));
  wingR.setSize(this->wingWidth, this->wingHeight);
  wingLInside.setTexture(arrayToTexture(10, 15, wingInsideSprite));
  wingLInside.setSize(this->wingWidth, this->wingHeight);
  wingRInside.setTexture(arrayToTexture(10, 15, wingInsideSprite));
  wingRInside.setSize(this->wingWidth, this->wingHeight);
  cockpitFront.setTexture(arrayToTexture(15, 5, cockpitFrontSprite));
  cockpitFront.setSize(this->wingSpan * 2, this->cockpitThickness * 2);
  cockpitBack.setTexture(arrayToTexture(15, 5, cockpitBackSprite));
  cockpitBack.setSize(this->wingSpan * 2, this->cockpitThickness * 2);
  cockpitTop.setTexture(arrayToTexture(15, 5, cockpitTopSprite));
  cockpitTop.setSize(this->wingSpan * 2, this->cockpitThickness * 2);
  cockpitBottom.setTexture(arrayToTexture(15, 5, cockpitTopSprite));
  cockpitBottom.setSize(this->wingSpan * 2, this->cockpitThickness * 2);
}

void TieFighter::setPosition(Matrix position){
  this->position = position;
  this->changed = true;
}

void TieFighter::setRotation(double rotation){
  this->rotation = rotation;
  double si = sin(rotation);
  double co = cos(rotation);
  double fwd[] = {si, 0, co};
  double lft[] = {-co, 0, si};
  this->forward = Matrix(1, 3, fwd);
  this->left = Matrix(1, 3, lft);
  this->changed = true;
}

void TieFighter::update(){
  double u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  this->wingL.setPosition(this->position + this->left * this->wingSpan);
  this->wingL.setDirection(this->left, up);
  this->wingLInside.setPosition(this->position + this->left * this->wingSpan);
  this->wingLInside.setDirection(-this->left, up);
  this->wingR.setPosition(this->position - this->left * this->wingSpan);
  this->wingR.setDirection(-this->left, up);
  this->wingRInside.setPosition(this->position - this->left * this->wingSpan);
  this->wingRInside.setDirection(this->left, up);

  this->cockpitFront.setPosition(this->position + this->forward * this->cockpitThickness);
  this->cockpitFront.setDirection(this->forward, up);
  this->cockpitBack.setPosition(this->position - this->forward * this->cockpitThickness);
  this->cockpitBack.setDirection(-this->forward, up);
  this->cockpitTop.setPosition(this->position + up * this->cockpitThickness);
  this->cockpitTop.setDirection(up, this->forward);
  this->cockpitBottom.setPosition(this->position - up * this->cockpitThickness);
  this->cockpitBottom.setDirection(-up, this->forward);
}

void TieFighter::render(Camera &cam, Renderer &renderer){
  if(this->changed)
    this->update();
  this->wingL.render(cam, renderer);
  this->wingLInside.render(cam, renderer);
  this->wingR.render(cam, renderer);
  this->wingRInside.render(cam, renderer);
  this->cockpitFront.render(cam, renderer);
  this->cockpitBack.render(cam, renderer);
  this->cockpitTop.render(cam, renderer);
  this->cockpitBottom.render(cam, renderer);
}

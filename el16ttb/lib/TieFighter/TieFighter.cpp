#include <TieFighter.h>

const int wingSprite [] = {
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 1, 0, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
  1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
  1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1
};

const int wingInsideSprite [] = {
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 1, 0, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
   1, 1, 1, 1, 0, 0, 1, 1, 1,  1,
   1, 1, 1, 1, 1, 1, 1, 1, 1,  1,
   1, 1, 1, 1, 1, 1, 1, 1, 1,  1,
   1, 1, 1, 1, 1, 1, 1, 1, 1,  1,
   1, 1, 1, 1, 0, 0, 1, 1, 1,  1,
  -1, 1, 1, 0, 0, 0, 0, 1, 1, -1,
  -1, 1, 0, 0, 1, 1, 0, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 0, 1, 1, 1, 1, 0, 1, -1,
  -1, 1, 1, 1, 1, 1, 1, 1, 1, -1
};

const int cockpitFrontSprite [] = {
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1
};
const int cockpitBackSprite [] = {
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1
};
const int cockpitTopSprite [] = {
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1
};

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
  double lft[] = {co, 0, si};
  this->forward = Matrix(1, 3, fwd);
  this->left = Matrix(1, 3, lft);
  this->changed = true;
}

void TieFighter::update(){
  double u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  wingL.setPosition(this->position + this->left * this->wingSpan);
  wingL.setDirection(this->left, up);
  wingLInside.setPosition(this->position + this->left * this->wingSpan);
  wingLInside.setDirection(-this->left, up);
  wingR.setPosition(this->position - this->left * this->wingSpan);
  wingR.setDirection(-this->left, up);
  wingRInside.setPosition(this->position - this->left * this->wingSpan);
  wingRInside.setDirection(this->left, up);

  cockpitFront.setPosition(this->position + this->forward * this->cockpitThickness);
  cockpitFront.setDirection(this->forward, up);
  cockpitBack.setPosition(this->position - this->forward * this->cockpitThickness);
  cockpitBack.setDirection(-this->forward, up);
  cockpitTop.setPosition(this->position + up * this->cockpitThickness);
  cockpitTop.setDirection(up, this->forward);
  cockpitBottom.setPosition(this->position - up * this->cockpitThickness);
  cockpitBottom.setDirection(-up, this->forward);
}

void TieFighter::render(Camera &cam, Renderer &renderer){
  if(this->changed)
    this->update();
  wingL.render(cam, renderer);
  wingLInside.render(cam, renderer);
  wingR.render(cam, renderer);
  wingRInside.render(cam, renderer);
  cockpitFront.render(cam, renderer);
  cockpitBack.render(cam, renderer);
  cockpitTop.render(cam, renderer);
  cockpitBottom.render(cam, renderer);
}

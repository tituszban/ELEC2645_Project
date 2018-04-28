#include <TieFighter.h>

TieFighter::TieFighter(){
  wingSpan = 0.425;
  cockpitThickness = 0.2;
  wingWidth = 1;
  wingHeight = 1.5;
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
  cockpitTop.setPosition(position + up * cockpitThickness);
  cockpitTop.setDirection(up, forward);
  cockpitBottom.setPosition(position - up * cockpitThickness);
  cockpitBottom.setDirection(-up, forward);
}

void TieFighter::render(Camera &cam, Renderer &renderer){
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

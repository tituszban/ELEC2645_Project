#include <UI.h>



void UI::setDir(int dir){
  this->dir = dir % 8;
}

void UI::setBars(int left, int right){
  this->leftBar = left % 6;
  this->rightBar = right % 6;
}

void UI::setFire(int left, int right){
  this->leftFire = 1 - left % 2;
  this->rightFire = 1 - right % 2;
}

void UI::render(int index, Renderer &renderer){
  memoryBenchmark("before UI");
  Texture cockpit = arrayToTexture(84, 48, cockpitSprite);
  renderer.addUISprite(0, 0, cockpit);
  Texture topBar = arrayToTexture(16, 1, topBarSprites[index % 19]);
  renderer.addUISprite(34, 30, topBar);
  Texture leftBottom = arrayToTexture(6, 3, leftBottomSprites[index % 3]);
  renderer.addUISprite(9, 44, leftBottom);
  Texture rightBottom = arrayToTexture(6, 3, rightBottomSprites[index % 4]);
  renderer.addUISprite(69, 44, rightBottom);
  Texture ticker = arrayToTexture(7, 2, tickerSprites[index % 6]);
  renderer.addUISprite(23, 45, ticker);
  Texture rightIndicator = arrayToTexture(6, 1, rightIndicatorSprites[index % 21]);
  renderer.addUISprite(59, 38, rightIndicator);
  Texture rightBlinker = arrayToTexture(2, 5, rightBlinkerSprites[index % 5]);
  renderer.addUISprite(53, 36, rightBlinker);
  Texture leftBlinker = arrayToTexture(2, 5, leftBlinkerSprites[index % 7]);
  renderer.addUISprite(29, 36, leftBlinker);
  Texture leftBar = arrayToTexture(1, 5, barSprites[this->leftBar]);
  renderer.addUISprite(55, 43, leftBar);
  Texture rightBar = arrayToTexture(1, 5, barSprites[this->rightBar]);
  renderer.addUISprite(59, 43, rightBar);
  Texture leftFire = arrayToTexture(4, 3, leftBigIndicatorSprite[this->leftFire]);
  renderer.addUISprite(8, 40, leftFire);
  Texture rightFire = arrayToTexture(4, 3, rightBigIndicatorSprite[this->rightFire]);
  renderer.addUISprite(72, 40, rightFire);
  Texture dir = arrayToTexture(3, 3, dirSprites[this->dir]);
  renderer.addUISprite(23, 38, dir);
  memoryBenchmark("After UI");
}

UI::UI(){
  this->setDir(0);
  this->setBars(0, 0);
  this->setFire(0, 0);
}

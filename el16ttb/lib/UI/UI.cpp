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
  // memoryBenchmark("before UI");
  // Texture cockpit = arrayToTexture(84, 48, cockpitSprite);
  renderer.addUISprite(0, 0, 84, 48, cockpitSprite);
  renderer.addUISprite(34, 30, 16, 1, topBarSprites[index % 19]);
  renderer.addUISprite(9, 44, 6, 3, leftBottomSprites[index % 3]);
  renderer.addUISprite(69, 44, 6, 3, rightBottomSprites[index % 4]);
  renderer.addUISprite(23, 45, 7, 2, tickerSprites[index % 6]);
  renderer.addUISprite(59, 38, 6, 1, rightIndicatorSprites[index % 21]);
  renderer.addUISprite(53, 36, 2, 5, rightBlinkerSprites[index % 5]);
  renderer.addUISprite(29, 36, 2, 5, leftBlinkerSprites[index % 7]);
  renderer.addUISprite(55, 43, 1, 5, barSprites[leftBar]);
  renderer.addUISprite(59, 43, 1, 5, barSprites[rightBar]);
  renderer.addUISprite(8, 40, 4, 3, leftBigIndicatorSprite[leftFire]);
  renderer.addUISprite(72, 40, 4, 3, rightBigIndicatorSprite[rightFire]);
  renderer.addUISprite(23, 38, 3, 3, dirSprites[dir]);
  // memoryBenchmark("After UI");
}

UI::UI(){
  this->setDir(0);
  this->setBars(0, 0);
  this->setFire(0, 0);
}

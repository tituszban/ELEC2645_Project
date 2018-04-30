#include <UI.h>

UI::UI(){
  setDir(0);
  setBars(0, 0);
  setFire(0, 0);
  missionProgress(0);
  setTarget(1);
}

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

void UI::missionProgress(int progress){
  this->progress = progress % 11;
}

bool UI::setNextTarget(int type, int dir){
  if(targetProgress == 0){
    nextTarget = type;
    targetProgress = sgn(dir) * 15;
    return true;
  }
  return false;
}

void UI::setTarget(int type){
  target = type;
  targetProgress = 0;
  nextTarget = type;
}

void UI::setTargetVisibility(int visibility){
  targetVisibility = visibility;
}
void UI::setFarTargetPos(int x, int y){
  farTargetX = x;
  farTargetY = y;
}

void UI::setOffscreenTarget(int side, float p){
  arrowSide = side;
  switch(side){
    case 0: arrowX = WIDTH - 7; arrowY = (int)(HEIGHT / 2 - p * (float)HEIGHT); break;
    case 1: arrowX = (int)(WIDTH / 2 + min(max(p, -0.5f), 0.5f) * (float)HEIGHT / 2); arrowY = 0; break;
    case 2: arrowX = 0; arrowY = (int)(HEIGHT / 2 - p * (float)HEIGHT); break;
    case 3: arrowX = (int)(WIDTH / 2 + min(max(p, -0.5f), 0.5f) * (float)HEIGHT / 2); arrowY = HEIGHT - 7; break;
  }
  if(side == 0){

  }
  else if(side == 1){

  }
}

void UI::setMissionActive(bool missionActive){
  this->missionActive = missionActive;
}

void UI::render(int index, Renderer &renderer){
  if(targetVisibility == 1){
    renderer.addUISprite(farTargetX - 2, farTargetY - 2, 5, 5, distantobjectSprite);
  }
  else if(targetVisibility == 2){
    renderer.addUISprite(arrowX, arrowY, 7, 7, arrowSide == 0 ? arrowrightSprite :
      (arrowSide == 1 ? arrowupSprite :
        (arrowSide == 2 ? arrowleftSprite : arrowdownSprite)
      )
    );
  }

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
  if(missionActive){
    renderer.addUISprite(32, 35, 3, 12, missionindicatorSprite);
    for(int i = 0; i < progress; i++){
      renderer.addUISprite(32, 45 - i, 2, 1, missionIndicatorBarSprite);
    }
  }

  if(targetProgress != 0){
    renderer.addUISpriteToSubArea(36, 34, 1 + targetProgress, 1, 15, 14, 12, 11, nextTarget == 0 ? uitietargetSprite : (nextTarget == 1 ? uishuttletargetSprite : uiexplodedtargetSprite));
    renderer.addUISpriteToSubArea(36, 34, 1 - sgn(targetProgress) * 15 + targetProgress, 1, 15, 14, 12, 11, target == 0 ? uitietargetSprite : (target == 1 ? uishuttletargetSprite : uiexplodedtargetSprite));
    targetProgress -= sgn(targetProgress) * 3;
  }
  else{
    target = nextTarget;
    renderer.addUISprite(37, 35, 12, 11, target == 0 ? uitietargetSprite : (target == 1 ? uishuttletargetSprite : uiexplodedtargetSprite));
    // renderer.addUISpriteToSubArea(36, 34, 2, 1, 15, 14, 12, 11, );
  }

}

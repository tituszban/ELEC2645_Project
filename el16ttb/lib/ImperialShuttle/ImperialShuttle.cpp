#include <ImperialShuttle.h>

ImperialShuttle::ImperialShuttle(){
  bodyLength = 1.5;
  bodyWidth = 1;
  cockpitLength = 0.4;
  engineWidth = 0.3;
  engineHeight = 0.2;
  bodyHeight = 0.4;
  cockpitHypot = sqrt(bodyHeight * bodyHeight + cockpitLength * cockpitLength);
  cockpitSin = bodyHeight / cockpitHypot;
  cockpitCos = cockpitLength / cockpitHypot;
  wingAngle = PI / 4;
  wingSin = sin(wingAngle);
  wingCos = cos(wingAngle);
  wingLength = 1.5;
  topWingHeight = 1.5;
  topWingLength = 1.2;
  topWingOffset = 0.1;

  setPosition(Matrix(1, 3));
  setRotation(0);

  Texture sideTexture = arrayToTexture(38, 8, shuttlesideSprite);
  Texture engineTexture = arrayToTexture(27, 7, shuttlesidepanelSprite);
  Texture wingTexture = arrayToTexture(27, 40, shuttlesidewingSprite);
  sideL.setTexture(flipTexture(sideTexture, 0));
  sideL.setSize(bodyLength, bodyHeight);
  sideR.setTexture(sideTexture);
  sideR.setSize(bodyLength, bodyHeight);
  back.setTexture(arrayToTexture(21, 8, shuttlebackSprite));
  back.setSize(bodyWidth, bodyHeight);
  top.setTexture(arrayToTexture(9, 27, shuttletopSprite));
  top.setSize(bodyWidth - engineWidth * 2, bodyLength - cockpitLength);
  bottom.setTexture(arrayToTexture(21, 38, shuttlebottomSprite));
  bottom.setSize(bodyWidth, bodyLength);
  cockpit.setTexture(arrayToTexture(7, 13, shuttlecockpitSprite));
  cockpit.setSize(bodyWidth - engineWidth * 2, cockpitHypot);
  front.setTexture(arrayToTexture(21, 8, shuttlefrontSprite));
  front.setSize(bodyWidth, bodyHeight);
  engineLSide.setTexture(engineTexture);
  engineLSide.setSize(bodyLength - cockpitLength, engineHeight);
  engineRSide.setTexture(engineTexture);
  engineRSide.setSize(bodyLength - cockpitLength, engineHeight);
  engineLTop.setTexture(engineTexture);
  engineLTop.setSize(bodyLength - cockpitLength, engineWidth);
  engineRTop.setTexture(engineTexture);
  engineRTop.setSize(bodyLength - cockpitLength, engineWidth);
  topWingL.setTexture(flipTexture(arrayToTexture(35, 30, shuttletopwingSprite), 0));
  topWingL.setSize(topWingLength, topWingHeight);
  topWingR.setTexture(arrayToTexture(35, 30, shuttletopwingSprite));
  topWingR.setSize(topWingLength, topWingHeight);
  wingLTop.setTexture(flipTexture(wingTexture, 0));
  wingLTop.setSize(bodyLength - cockpitLength, wingLength);
  wingLBottom.setTexture(flipTexture(wingTexture, 0));
  wingLBottom.setSize(bodyLength - cockpitLength, wingLength);
  wingRTop.setTexture(flipTexture(wingTexture, 2));
  wingRTop.setSize(bodyLength - cockpitLength, wingLength);
  wingRBottom.setTexture(flipTexture(wingTexture, 2));
  wingRBottom.setSize(bodyLength - cockpitLength, wingLength);
}

void ImperialShuttle::setPosition(Matrix position){
  this->position = position;
  changed = true;
}

void ImperialShuttle::setRotation(double rotation){
  this->rotation = rotation;
  double si = sin(rotation);
  double co = cos(rotation);

  double fwd[] = {si, 0, co};
  double lft[] = {-co, 0, si};
  double lw[] = {-co * wingCos, wingSin, si*wingSin};
  double rw[] = {co * wingCos, wingSin, -si*wingCos};
  double fc[] = {si * cockpitCos, cockpitSin, co*cockpitCos};
  forward = Matrix(1, 3, fwd);
  left = Matrix(1, 3, lft);
  leftWing = Matrix(1, 3, lw);
  rightWing = Matrix(1, 3, rw);
  cockpitFacing = Matrix(1, 3, fc);
  changed = true;
}

void ImperialShuttle::update(){
  double u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  sideL.setPosition(position + left * (bodyWidth * 0.5 - engineWidth) +forward * cockpitLength * 0.5);
  sideL.setDirection(left, up);
  sideR.setPosition(position - left * (bodyWidth * 0.5 - engineWidth) + forward * cockpitLength * 0.5);
  sideR.setDirection(-left, up);
  back.setPosition(position - forward * (bodyLength - cockpitLength) * 0.5);
  back.setDirection(-forward, up);
  top.setPosition(position + up * bodyHeight * 0.5);
  top.setDirection(up, forward);
  bottom.setPosition(position - up * bodyHeight * 0.5 + forward * cockpitLength * 0.5);
  bottom.setDirection(-up, forward);
  cockpit.setPosition(position + forward * bodyLength * 0.5);
  cockpit.setDirection(cockpitFacing, cockpitFacing.cross(left));
  front.setPosition(position + forward * (bodyLength - cockpitLength) * 0.5);
  front.setDirection(forward, up);
  engineLSide.setPosition(position + up * (engineHeight - bodyHeight) * 0.5 + left * bodyWidth * 0.5);
  engineLSide.setDirection(left, up);
  engineRSide.setPosition(position + up * (engineHeight - bodyHeight) * 0.5 - left * bodyWidth * 0.5);
  engineRSide.setDirection(-left, up);
  engineLTop.setPosition(position + up * (engineHeight - bodyHeight * 0.5) + left * (bodyWidth - engineWidth) * 0.5);
  engineLTop.setDirection(up, left);
  engineRTop.setPosition(position + up * (engineHeight - bodyHeight * 0.5) - left * (bodyWidth - engineWidth) * 0.5);
  engineRTop.setDirection(up, left);
  topWingL.setPosition(position + up * (bodyHeight + topWingHeight) * 0.5 - forward * topWingOffset);
  topWingL.setDirection(left, up);
  topWingR.setPosition(position + up * (bodyHeight + topWingHeight) * 0.5 - forward * topWingOffset);
  topWingR.setDirection(-left, up);
  wingLTop.setPosition(position - up * (wingSin * wingLength + bodyHeight) * 0.5 + left * (bodyWidth + wingCos * wingLength) * 0.5);
  wingLTop.setDirection(leftWing, leftWing.cross(forward));
  wingLBottom.setPosition(position - up * (wingSin * wingLength + bodyHeight) * 0.5 + left * (bodyWidth + wingCos * wingLength) * 0.5);
  wingLBottom.setDirection(-leftWing, leftWing.cross(forward));
  wingRTop.setPosition(position - up * (wingSin * wingLength + bodyHeight) * 0.5 - left * (bodyWidth + wingCos * wingLength) * 0.5);
  wingRTop.setDirection(rightWing, rightWing.cross(forward));
  wingRBottom.setPosition(position - up * (wingSin * wingLength + bodyHeight) * 0.5 - left * (bodyWidth + wingCos * wingLength) * 0.5);
  wingRBottom.setDirection(-rightWing, rightWing.cross(forward));
}

void ImperialShuttle::render(Camera &cam, Renderer &renderer){
  if(changed)
    update();
  sideL.render(cam, renderer);
  sideR.render(cam, renderer);
  back.render(cam, renderer);
  top.render(cam, renderer);
  bottom.render(cam, renderer);
  cockpit.render(cam, renderer);
  front.render(cam, renderer);
  engineLSide.render(cam, renderer);
  engineRSide.render(cam, renderer);
  engineLTop.render(cam, renderer);
  engineRTop.render(cam, renderer);
  topWingL.render(cam, renderer);
  topWingR.render(cam, renderer);
  wingLTop.render(cam, renderer);
  wingLBottom.render(cam, renderer);
  wingRTop.render(cam, renderer);
  wingRBottom.render(cam, renderer);
}

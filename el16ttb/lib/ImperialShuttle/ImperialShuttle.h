#ifndef LIB_IMPERIALSHUTTLE_H_
#define LIB_IMPERIALSHUTTLE_H_

using namespace std;
#include <Face.h>
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <math.h>
#include <Util.h>
#include <Explosion.h>
#include <SoundManager.h>

class ImperialShuttle{
public:
  ImperialShuttle();
  ImperialShuttle(Matrix position, float rotation);
  void setPosition(Matrix position);
  void setRotation(float rotation);
  void render(Camera &cam, Renderer &renderer);
  bool detectCollision(Matrix projectile);
  void update(float dt, float steering, float speedMult, SoundManager &sm);
  Matrix getPosition();
  float getRotation();
  Matrix getFacing();
  bool toBeRemoved;


private:
  void init();
  Matrix position;
  float rotation;
  Matrix forward;
  Matrix left;
  Matrix leftWing;
  Matrix rightWing;
  Matrix cockpitFacing;
  bool changed;

  float bodyLength;
  float bodyWidth;
  float cockpitLength;
  float cockpitSin;
  float cockpitCos;
  float cockpitHypot;
  float engineWidth;
  float engineHeight;
  float bodyHeight;
  float wingAngle;
  float wingSin;
  float wingCos;
  float wingLength;
  float topWingHeight;
  float topWingLength;
  float topWingOffset;

  Face sideL;
  Face sideR;
  Face back;
  Face top;
  Face bottom;
  Face cockpit;
  Face front;
  Face engineLSide;
  Face engineRSide;
  Face engineLTop;
  Face engineRTop;
  Face topWingL;
  Face topWingR;
  Face wingLTop;
  Face wingLBottom;
  Face wingRTop;
  Face wingRBottom;

  float steeringAngle;
  float speed;
  float minSpeed;

  float life;
  float outerHitboxRadius;
  float innerHitboxRadius;

  Explosion explosion;
  int smID;

  void update();
};

const int shuttlesideSprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	1,
	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	1,
	-1,	-1,	-1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	1,	1,
	-1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttlebackSprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttlebottomSprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	1,	1,	1,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	1,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttlecockpitSprite[] =	{
	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,
	1,	0,	1,	1,	1,	0,	1,
	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,
	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1
};
const int shuttlefrontSprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttlesidepanelSprite[] =	{
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttlesidewingSprite[] =	{
	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	1,	0,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,
	-1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	1,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	1,	0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	1,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	1,	1,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttletopSprite[] =	{
	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	0,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	1,	1,	1,	0,	0,	1,
	1,	0,	0,	0,	1,	0,	0,	0,	1,
	1,	1,	1,	1,	1,	1,	1,	1,	1
};
const int shuttletopwingSprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	1,	0,	0,	1,	0,	0,	1,	1,	1,	1,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	1,	1,	1,	0,	1,	0,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	0,	0,	1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	0,	1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	0,	1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	-1,
	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	1,	-1,
	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	-1,
	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	-1,
	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	1,	-1,
	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	-1,
	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	1,
	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1
};

#endif

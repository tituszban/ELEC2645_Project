#ifndef LIB_EXPLOSION_H_
#define LIB_EXPLOSION_H_

using namespace std;
#include <vector>
#include <Face.h>
#include <Matrix.h>
#include "mbed.h"
#include <Renderer.h>
#include <math.h>
#include <Util.h>

class Explosion{
public:
  Explosion();
  Explosion(Matrix position, float size);
  void setPosition(Matrix position);
  void setSize(float size);
  void update(float dt);
  void render(Camera &cam, Renderer &renderer);
  void reset();
  bool toBeRemoved;
private:
  Matrix position;
  float explosionTime;
  float timer;
  int explosionIndexPre;
  Face explosion;
};

const int explosion0Sprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	0,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1
};
const int explosion1Sprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	0,	0,	1,	1,	0,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	0,	1,	0,	0,	0,	1,	0,	0,	0,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	0,	0,	1,	1,	1,	1,	0,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	1,	0,	0,	1,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	1,	0,	0,	0,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	1,	1,	0,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1
};
const int explosion2Sprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	1,	0,	1,	1,	1,	0,	1,	0,	0,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1,	-1,	-1,	-1,
	-1,	1,	0,	1,	1,	0,	1,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	1,	1,	0,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	1,	1,	1,	0,	0,	1,	1,	1,	0,	1,	1,	0,	1,	0,	1,	-1,	-1,	-1,
	-1,	-1,	1,	1,	0,	0,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	0,	1,	0,	0,	1,	0,	0,	1,	1,	1,	0,	0,	0,	1,	1,	-1,	-1,	-1,
	-1,	-1,	1,	1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	1,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	1,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1
};
const int explosion3Sprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	1,	-1,	1,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,
	-1,	-1,	-1,	1,	1,	0,	1,	1,	1,	1,	0,	1,	1,	1,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	0,	0,	1,	1,	0,	0,	0,	1,	1,	1,	1,	0,	0,	1,	-1,	-1,	-1,
	-1,	1,	-1,	1,	1,	0,	1,	0,	0,	0,	1,	0,	1,	1,	1,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	0,	1,	1,	1,	0,	0,	0,	1,	0,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	0,	0,	0,	1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	1,	-1,	-1,	-1,
	-1,	1,	-1,	1,	1,	1,	0,	0,	1,	1,	0,	0,	0,	1,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	1,	1,	0,	0,	0,	0,	1,	1,	0,	0,	1,	1,	0,	1,	1,	-1,	-1,	1,
	1,	-1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	1,	-1,	-1,	-1,	-1,
	-1,	1,	-1,	0,	0,	1,	0,	0,	1,	0,	0,	0,	1,	1,	0,	1,	1,	-1,	1,	-1,
	-1,	-1,	-1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	1,	0,	0,	0,	1,	0,	0,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,
	-1,	-1,	1,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	1,	0,	1,	1,	0,	1,	1,	0,	0,	0,	0,	1,	0,	1,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	0,	1,	1,	0,	0,	1,	-1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	-1,	-1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1
};
const int explosion4Sprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,
	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	-1,	-1,	-1,	1,	1,	-1,	-1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	0,	1,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	1,	1,	0,	1,	0,	1,	-1,	-1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	0,	1,	0,	1,	1,	0,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	0,	1,	1,	0,	1,	0,	1,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	1,	-1,	-1,	1,	0,	0,	0,	1,	0,	0,	1,	1,	0,	1,	-1,	-1,	-1,	1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	0,	0,	1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	0,	1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	0,	0,	0,	1,	-1,	1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	1,	1,	0,	1,	1,	-1,	-1,	1,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	1,	1,	1,	-1,	-1,	1,	0,	0,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	1,	-1,	-1,	-1,	-1,	-1,	1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1
};
const int explosion5Sprite[] =	{
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	1,	-1,	1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1
};

#endif

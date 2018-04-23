#ifndef LIB_UI_H_
#define LIB_UI_H_

#include <Renderer.h>
#include <Util.h>
#include "mbed.h"

class UI{
public:
  UI();
  void setDir(int dir);
  void setBars(int left, int right);
  void setFire(int left, int right);
  void render(int index, Renderer &renderer);

private:
  int dir;
  int leftBar;
  int rightBar;
  int leftFire;
  int rightFire;
};

#endif

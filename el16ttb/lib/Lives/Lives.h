#ifndef LIB_LIVES_H_
#define LIB_LIVES_H_

#include <Controller.h>
#include "mbed.h"

class Lives{
public:
  Lives();
  Lives(Controller &cont);
  void damage(float dam);
  bool isGameOver();
  void reset();
private:
  float life;
  void setLEDs();
  Controller *cont;
};

#endif

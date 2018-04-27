#ifndef LIB_LIVES_H_
#define LIB_LIVES_H_

#include <Controller.h>
#include "mbed.h"

class Lives{
public:
  Lives(Controller &cont);
  void damage(double dam);
  bool isGameOver();
  void reset();
private:
  double life;
  void setLEDs();
  Controller *cont;
};

#endif

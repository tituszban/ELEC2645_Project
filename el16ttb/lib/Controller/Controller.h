#ifndef CONTROLLER
#define CONTROLLER

#include "mbed.h"
#include <N5110.h>
#include <Gamepad.h>

using namespace std;
#include <map>

enum Button
{
  A,
  B,
  X,
  Y,
  L,
  R,
  START,
  BACK,
  JOYSTICK
};

class Controller
{
public:
  Controller();
  void init();
  bool buttonPressed(Button b);
  bool buttonReleased(Button b);
  bool buttonDown(Button b);

  void ledsOn();
  void ledsOff();
  void leds(float val);
  void led(int n, float val);
  float readPot();
  void tone(float frequency, float duration);
  float joystickMag();
  float joystickAngle();
  Direction joystickDirection();
  Vector2D joystickCoord();
  Vector2D joystickMapCoord();
  Polar joystickPolar();

  void lcdOff();
  void lcdClear();
  void lcdContrast(float contrast);
  void lcdNormalMode();
  void lcdInverseMode();
  void lcdSetBrightness(float brightness);
  void lcdPrintString(char const *str,
                  unsigned int const x,
                  unsigned int const y);
  void lcdPrintChar(char const c,
                  unsigned int const x,
                  unsigned int const y);
  void lcdSetPixel(unsigned int const x,
                  unsigned int const y,
                  bool const state);
  int lcdGetPixel(unsigned int const x, unsigned int y);
  void lcdRefresh();
  void lcdPlotArray(float const array[]);
  void lcdDrawCircle(unsigned int const x0,
                  unsigned int const y0,
                  unsigned int const radius,
                  FillType const     fill);
  void lcdDrawLine(unsigned int const x0,
                unsigned int const y0,
                unsigned int const x1,
                unsigned int const y1,
                unsigned int const type);
  void lcdDrawRect(unsigned int const x0,
                unsigned int const y0,
                unsigned int const width,
                unsigned int const height,
                FillType const     fill);
  void lcdDrawSprite(int x0,
                  int y0,
                  int nrows,
                  int ncols,
                  int *sprite);

private:
  std::map<Button, int> _buttons;

  Gamepad *pad;
  N5110 *lcd;

  void initButtons();

  void aDown();
  void bDown();
  void xDown();
  void yDown();
  void lDown();
  void rDown();
  void startDown();
  void backDown();
  void joyDown();

  void aUp();
  void bUp();
  void xUp();
  void yUp();
  void lUp();
  void rUp();
  void startUp();
  void backUp();
  void joyUp();

  InterruptIn *_button_A;
  InterruptIn *_button_B;
  InterruptIn *_button_X;
  InterruptIn *_button_Y;
  InterruptIn *_button_L;
  InterruptIn *_button_R;
  InterruptIn *_button_back;
  InterruptIn *_button_start;
  InterruptIn *_button_joystick;
};

#endif

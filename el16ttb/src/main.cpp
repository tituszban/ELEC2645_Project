/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds

Name: Tamas Titusz Ban
Username: el16ttb
Student ID Number: 201005198
Date: 05/03/2018
*/
#include "mbed.h"
#include <Controller.h>
#include <UnitTester.cpp>
#include <GameEngine.h>

Controller cont;

void DrawPoints();

float led = 0;
void alive(){
  led = 1 - led;
  cont.led(1, led);
}

Ticker t;

int main() {
  srand(time(NULL));
  cont.init();
  // cont.lcdInverseMode();
  // cont.ledsOn();
  cont.lcdContrast(0.5);

  // t.attach(&alive, 0.5);



  // XWingTest(cont);
  mainGame(cont);

  cont.lcdClear();
  cont.lcdRefresh();
  cont.ledsOff();
  cont.lcdSetBrightness(0);
}

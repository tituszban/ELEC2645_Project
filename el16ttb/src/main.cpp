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

// #define FINAL
// #define TESTING

Controller cont;

void DrawPoints();

float led = 0;
void alive(){
  led = 1 - led;
  cont.led(1, led);
}

Ticker t;

void details(){
  cont.lcdPrintString("Star Wars", 15, 2);
  cont.lcdPrintString("X-Wing Mission", 0, 3);
  cont.lcdRefresh();
  wait(2.5f);
  cont.lcdClear();
  cont.lcdPrintString("Created by:", 9, 1);
  cont.lcdPrintString("Tamas", 27, 2);
  cont.lcdPrintString("Titusz Ban", 12, 3);
  cont.lcdPrintString("201005198", 15, 4);
  cont.lcdRefresh();
  wait(2.5f);
}

int main() {
  srand(time(NULL));
  cont.init();
  // cont.lcdInverseMode();
  // cont.ledsOn();
  cont.muted = false;
  cont.contrast = 0.5;
  cont.lcdContrast(cont.contrast);
  cont.brightness = 0.8;
  cont.lcdSetBrightness(cont.brightness);
#ifdef FINAL
  details();
#endif
  // t.attach(&alive, 0.5);
#ifdef TESTING
  SoundManagerTest(cont);
#endif

  while(1){
    switch(mainMenu(cont)){
      case 0: cutscene(cont); gameManager(cont); break;
      case 1: tutorial(cont); break;
      case 2: showcase(cont); break;
    }
  }
}

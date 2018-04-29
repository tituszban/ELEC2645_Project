/*
ELEC2645 Embedded Systems Project
School of Electronic & Electrical Engineering
University of Leeds

Name: Tamas Titusz Ban
Username: el16ttb
Student ID Number: 201005198
Date: 05/03/2018
*/
using namespace std;

#include "mbed.h"
#include <Controller.h>
#include <Matrix.h>
#include <Camera.h>
#include <UnitTester.cpp>
#include <vector>

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
  // cont.lcdContrast(0.5);
  cont.lcdContrast(0.5);
  // cont.lcdDrawCircle(20, 20, 10, FILL_TRANSPARENT);
  // cont.lcdRefresh();
  // t.attach(&alive, 0.5);



  XWingTest(cont);
  // lcd.printString("Test completed", 0, 2);
  // lcd.refresh();
  //DrawPoints();

  cont.lcdSetBrightness(0);
}

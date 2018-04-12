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
#include <UnitTester.h>
#include <vector>

Controller cont;

void DrawPoints();

int main() {
  cont.init();
  cont.ledsOn();
  cont.lcdContrast(0.5);
  // lcd.printString("Matrix test", 0, 0);
  // lcd.refresh();
  // lcd.printString("Test start", 0, 1);
  // lcd.refresh();
  UnitTester::BlockRenderTest(cont);
  // lcd.printString("Test completed", 0, 2);
  // lcd.refresh();
  //DrawPoints();
}

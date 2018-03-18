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
#include <N5110.h>
#include <Gamepad.h>
#include <Matrix.h>
#include <UnitTester.h>
#include <vector>

N5110 lcd = N5110(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad pad;

int main() {
  lcd.init();
  pad.init();
  pad.leds_on();
  lcd.setContrast(0.5);
  lcd.printString("Matrix test", 0, 0);
  lcd.refresh();
  lcd.printString("Test start", 0, 1);
  lcd.refresh();
  UnitTester::MatrixErrorTest();
  lcd.printString("Test completed", 0, 2);
  lcd.refresh();
}

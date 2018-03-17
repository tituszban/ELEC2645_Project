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
#include <N5110.h>
#include <Gamepad.h>

N5110 lcd = N5110(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad pad;

int main() {
  lcd.init();
  pad.init();
  pad.leds_on();
  lcd.setContrast(0.5);
  lcd.printString("Hello World!", 1, 1);
  lcd.refresh();
}

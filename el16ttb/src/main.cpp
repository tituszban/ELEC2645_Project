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
#include <Camera.h>
#include <UnitTester.h>
#include <vector>

N5110 lcd = N5110(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11);
Gamepad pad;

// typedef Gamepad::GamepadEvent GEvent;

void DrawPoints();

int main() {
  lcd.init();
  pad.init();
  pad.leds_on();
  lcd.setContrast(0.5);
  // lcd.printString("Matrix test", 0, 0);
  // lcd.refresh();
  // lcd.printString("Test start", 0, 1);
  // lcd.refresh();
  UnitTester::CameraScaleTest(pad, lcd);
  // lcd.printString("Test completed", 0, 2);
  // lcd.refresh();
  //DrawPoints();
}

void DrawPoints()
{
  double posX = 0.5;
  double posZ = 0.5;

  double rotX = 0;
  double rotZ = 0;

  double points[8][4] = {
    {1, 1, 0, 1},
    {0, 1, 0, 1},
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 1, 1, 1},
    {0, 1, 1, 1},
    {1, 0, 1, 1},
    {0, 0, 1, 1}
  };
  Camera cam;
  cam.init();
  while(1){
    lcd.clear();
    posX += pad.get_coord().x * 0.1;
    //printf("Joystick: X:%.3f, Y:%.3f\n", pad.get_coord().x, pad.get_coord().y);
    if(pad.check_event(A_PRESSED)){
      rotX += 0.1;
    }
    if(pad.check_event(Y_PRESSED)){
      rotX -= 0.1;
    }
    if(pad.check_event(X_PRESSED)){
      rotZ += 0.1;
    }
    if(pad.check_event(B_PRESSED)){
      rotZ -= 0.1;
    }

    // printf("Position: X:%.3f, Z:%.3f\n", posX, posZ);
    //printf("Rotation: X:%.3f, Z:%.3f\n", rotX, rotZ);

    cam.SetPosition(posX, 2.8, posZ);
    cam.SetRotation(rotX, rotZ);
    // wait(1);
    for(int i = 0; i < 8; i++){
      Matrix point = Matrix(1, 4, points[i]);
      Matrix screenPoint = cam.GetScreenPosition(point);
      screenPoint = screenPoint / screenPoint.get(0, 2);
      //screenPoint.print_matrix();
      lcd.setPixel((int)screenPoint.get(0, 0),(int)screenPoint.get(0, 1),true);
    }

    lcd.refresh();
  }
}

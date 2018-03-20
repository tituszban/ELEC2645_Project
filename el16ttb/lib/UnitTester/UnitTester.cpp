using namespace std;
#include <vector>
#include "mbed.h"
#include "UnitTester.h"
#include <Matrix.h>
#include <Camera.h>
#include <math.h>


bool UnitTester::MatrixCreationTest(){
  printf("Starting Matrix Creation Test\n");
  printf("Testing M1\n");
  Matrix m1;
  printf("M1 shape: %d:%d\n", m1.shape.width, m1.shape.height);
  m1.print_matrix();

  printf("Testing M2\n");
  std::vector< std::vector<double> > m2Template(4, std::vector<double>(3));
  Matrix m2 = Matrix(m2Template);
  printf("M2 shape: %d:%d\n", m2.shape.width, m2.shape.height);
  m2.print_matrix();

  printf("Testing M3\n");
  Shape m3Shape = {3, 4};
  Matrix m3 = Matrix(m3Shape);
  printf("M3 shape: %d:%d\n", m3.shape.width, m3.shape.height);
  m3.print_matrix();

  printf("Testing M4\n");
  Matrix m4 = Matrix(1, 2);
  printf("M4 shape: %d:%d\n", m4.shape.width, m4.shape.height);
  m4.print_matrix();

  printf("Testing M5\n");
  double tempM5[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 0, 1
  };
  Matrix m5 = Matrix(3, 4, (double*) tempM5);
  printf("M5 shape: %d:%d\n", m5.shape.width, m5.shape.height);
  m5.print_matrix();
  printf("Test completed\n");
  return true;
}

bool UnitTester::MatrixReadWriteTest(){
  printf("Starting Matrix Read-Write Test\n");
  double temp[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 0, 1
  };
  Matrix m1 = Matrix(3, 4, temp);
  m1.print_matrix();
  printf("Read value at (0, 0): %f\n", m1.get(0, 0));
  printf("Read value at (1, 1): %f\n", m1.get(1, 1));
  printf("Read value at (2, 3): %f\n", m1.get(2, 3));
  printf("Write value 10 to (0, 0)\n");
  printf("Write value 14 to (1, 3)\n");
  m1.set(0, 0, 10.0);
  m1.set(1, 3, 14.0);
  m1.print_matrix();

  printf("Test completed\n");
  return true;
}

bool UnitTester::MatrixOperationsTest(){
  printf("Starting Matrix Operations Test\n");
  double temp1[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8
  };
  double temp2[] = {
    8, 7, 6,
    5, 4, 3,
    2, 1, 0
  };
  Matrix m1 = Matrix(3, 3, temp1);
  Matrix m2 = Matrix(3, 3, temp2);
  printf("M1:\n");
  m1.print_matrix();
  printf("M2:\n");
  m2.print_matrix();

  Matrix mp = m1 + m2;
  Matrix mpr = m2 + m1;
  printf("M1 + M2:\n");
  mp.print_matrix();
  printf("M2 + M1:\n");
  mpr.print_matrix();

  Matrix m1n = -m1;
  Matrix m2n = -m2;
  printf("-M1:\n");
  m1n.print_matrix();
  printf("-M2:\n");
  m2n.print_matrix();

  Matrix ms = m1 - m2;
  Matrix msr = m2 - m1;
  printf("M1 - M2:\n");
  ms.print_matrix();
  printf("M2 - M1:\n");
  msr.print_matrix();

  Matrix mm = m1 * m2;
  Matrix mmr = m2 * m1;
  printf("M1 * M2:\n");
  mm.print_matrix();
  printf("M2 * M1:\n");
  mmr.print_matrix();

  Matrix mcm = m1 * 10;
  Matrix mcd = m1 / 10;
  printf("M1 * 10:\n");
  mcm.print_matrix();
  printf("M2 / 10:\n");
  mcd.print_matrix();
  printf("Test completed\n");
  return true;
}

bool UnitTester::MatrixErrorTest(){
  printf("Starting Matrix Error Test\n");
  double temp1[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8
  };
  double temp2[] = {
    8, 7, 6,
    5, 4, 3
  };
  Matrix m1 = Matrix(3, 3, temp1);
  Matrix m2 = Matrix(3, 2, temp2);
  printf("M1:\n");
  m1.print_matrix();
  printf("M2:\n");
  m2.print_matrix();

  Matrix mp = m1 + m2;
  Matrix mn = m1 - m2;
  Matrix mm = m1 * m2;
  printf("Test completed\n");

  return true;
}

bool UnitTester::CameraValueTest(){
  Camera cam;
  cam.init();
  cam.SetPosition(0, 0, 6);
  double p[] = {1, 1, -1, 1};
  Matrix point = Matrix(1, 4, p);
  Matrix screenPoint = cam.GetScreenPosition(point);
  screenPoint.print_matrix();
  //double v =
  screenPoint = screenPoint / screenPoint.get(0, 2);
  screenPoint.print_matrix();
  return true;
}

bool UnitTester::CameraScaleTest(Gamepad &pad, N5110 &lcd){

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
    posX += pad.get_coord().x * 0.3;
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
    printf("Rotation: X:%.3f, Z:%.3f\n", rotX, rotZ);

    cam.SetPosition(posX, 2.8, posZ);
    cam.SetRotation(rotX, rotZ);
    // wait(1);
    for(int i = -12; i <= 12; i++){
      for(int j = -12; j <= 12; j++){
        for(int k = 0; k < 1; k++){
          if(sqrt(pow(i, 2) + pow(j, 2)) < 12){
            double p[] = {i, k, j, 1};
            Matrix point = Matrix(1, 4, p);
            Matrix screenPoint = cam.GetScreenPosition(point);
            if(screenPoint.get(0, 2) > 0){
              screenPoint = screenPoint / screenPoint.get(0, 2);
            //screenPoint.print_matrix();
              if(screenPoint.get(0, 0) > 0 && screenPoint.get(0, 0) < 84 && screenPoint.get(0, 1) > 0 && screenPoint.get(0, 1) < 48){
                lcd.setPixel((int)screenPoint.get(0, 0),(int)screenPoint.get(0, 1),true);
              }
            }
          }
        }
      }


    }

    lcd.refresh();
  }
  return true;
}

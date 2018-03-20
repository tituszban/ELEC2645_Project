#ifndef UT
#define  UT

#include <N5110.h>
#include <Gamepad.h>

class UnitTester{

public:
  static bool MatrixCreationTest();
  static bool MatrixReadWriteTest();
  static bool MatrixOperationsTest();
  static bool MatrixErrorTest();
  static bool CameraValueTest();
  static bool CameraScaleTest(Gamepad &pad, N5110 &lcd);
};

#endif

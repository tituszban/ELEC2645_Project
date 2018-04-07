#ifndef UT
#define  UT

#include <Controller.h>

class UnitTester{

public:
  static bool MatrixCreationTest();
  static bool MatrixReadWriteTest();
  static bool MatrixOperationsTest();
  static bool MatrixErrorTest();
  static bool CameraValueTest();
  static bool CameraScaleTest(Controller &cont);
  static bool RendererDisplayTest(Controller &cont);
  static bool FaceRenderTest(Controller &cont);
};

#endif

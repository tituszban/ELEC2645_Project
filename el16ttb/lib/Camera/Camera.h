#ifndef CAMERA
#define CAMERA

using namespace std;
#include <vector>
#include <Matrix.h>

#define KU 1500
#define KV 1275
#define WIDTH 84
#define HEIGHT 48


typedef std::vector<std::vector<double> > matrix_type;

class Camera{

public:
  void init();
  void SetPosition(double x, double y, double z);
  void SetRotation(double x, double z);
  void SetFocalLength(double f);
  Matrix GetScreenPosition(Matrix p);

private:
  double focalLength;
  Matrix position;
  Matrix homogPosition;
  Matrix rotation;

  Matrix Xunit;
  Matrix Zunit;

  Matrix rotationX;
  Matrix rotationZ;

  Matrix calibrationMatrix;
  Matrix projectionMatrix;
  Matrix cameraTransformation;

  Matrix RotationMatrix(Matrix u, double theta);

  void UpdateRotationMatrix();
  void UpdateCalibrationMatrix();
  void UpdateTransformationMatrix();
};




#endif

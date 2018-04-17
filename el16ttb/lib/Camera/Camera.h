#ifndef CAMERA
#define CAMERA

using namespace std;
#include <vector>
#include <Matrix.h>
#include <Util.h>

#define KU 1500
#define KV 1275
#define WIDTH 84
#define HEIGHT 48

#define ROTATION_RESOLUTION 5
#define ROTATION_X_MAX 90


typedef std::vector<std::vector<double> > matrix_type;

class Camera{

public:
  void init();
  void SetPosition(double x, double y, double z);
  void SetRotation(double x, double z);

  Matrix GetFacing();
  Matrix GetPosition();
  Matrix GetScreenPosition(Matrix p);

private:
  double focalLength;
  Matrix position;
  Matrix homogPosition;
  Matrix rotation;

  Matrix Xunit;
  Matrix Zunit;

  Matrix rotationMatrix;

  Matrix calibrationMatrix;
  Matrix projectionMatrix;
  Matrix cameraTransformation;
  Matrix calProjMatrix;
  Matrix cameraMatrix;

  Matrix RotationMatrix(Matrix u, double theta);

  vector<vector<Matrix> > rotationMatrices;

  void SetFocalLength(double f);

  void UpdateRotationMatrix();
  void UpdateCalibrationMatrix();
  void UpdateTransformationMatrix();

  Matrix NormalisePoint(Matrix p);

  void GenerateRotationMatrices();
};




#endif

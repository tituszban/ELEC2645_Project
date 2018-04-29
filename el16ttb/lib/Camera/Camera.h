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


typedef std::vector<std::vector<float> > matrix_type;

class Camera{

public:
  void init();
  void setPosition(float x, float y, float z);
  void setRotation(float x, float z);

  Matrix getFacing();
  Matrix getUp();
  Matrix getPosition();
  Matrix getScreenPosition(Matrix p);

private:
  float focalLength;
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

  Matrix rotateAboutU(Matrix u, float theta);
  Matrix rotateAboutX(float theta);
  Matrix rotateAboutY(float theta);

  vector<vector<Matrix> > rotationMatrices;

  void setFocalLength(float f);

  void updateRotationMatrix();
  void updateCalibrationMatrix();
  void updateTransformationMatrix();

  Matrix normalisePoint(Matrix p);
};




#endif

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
  void setPosition(double x, double y, double z);
  void setRotation(double x, double z);

  Matrix getFacing();
  Matrix getUp();
  Matrix getPosition();
  Matrix getScreenPosition(Matrix p);

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

  Matrix rotateAboutU(Matrix u, double theta);
  Matrix rotateAboutX(double theta);
  Matrix rotateAboutY(double theta);

  vector<vector<Matrix> > rotationMatrices;

  void setFocalLength(double f);

  void updateRotationMatrix();
  void updateCalibrationMatrix();
  void updateTransformationMatrix();

  Matrix normalisePoint(Matrix p);
};




#endif

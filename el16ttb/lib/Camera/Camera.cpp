#include "mbed.h"
#include "Camera.h"
#include <math.h>

void Camera::init()
{
  position = Matrix(3, 1);
  homogPosition = Matrix(1, 4);
  rotation = Matrix(3, 1);
  Xunit = Matrix(3, 1);
  Xunit.set(0, 0, 1);
  Zunit = Matrix(3, 1);
  Zunit.set(1, 0, 1);
  rotationMatrix = Matrix(3, 3);
  calibrationMatrix = Matrix(3, 3);
  projectionMatrix = Matrix(4, 3);
  projectionMatrix.set(0, 0, 1);
  projectionMatrix.set(1, 1, 1);
  projectionMatrix.set(2, 2, 1);
  cameraTransformation = Matrix(4, 4);
  setFocalLength(0.028);
  setPosition(0, 0, 0);
  setRotation(0, 0);
}

void Camera::setPosition(double x, double y, double z)
{
  position.set(0, 0, x);
  position.set(1, 0, y);
  position.set(2, 0, z);
  homogPosition.set(0, 0, x);
  homogPosition.set(0, 1, y);
  homogPosition.set(0, 2, z);
  homogPosition.set(0, 3, 1);
  updateTransformationMatrix();
}

void Camera::setRotation(double x, double y)
{
  rotation.set(0, 0, x);
  rotation.set(1, 0, y);
  rotation.set(2, 0, 0);
  updateRotationMatrix();
  updateTransformationMatrix();
}

void Camera::setFocalLength(double f)
{
  focalLength = f;
  updateCalibrationMatrix();
}

Matrix Camera::rotateAboutU(Matrix u, double theta)
{
  double ux = u.get(0, 0);
  double uy = u.get(1, 0);
  double uz = u.get(2, 0);
  double co = cos(theta);
  double si = sin(theta);
  double R[] = {
    co + pow(ux,2)*(1-co), ux*uy*(1-co) - uz*si, ux*uz*(1-co) + uy*si,
    uy*ux*(1-co)+uz*si, co + pow(uy, 2)*(1-co), uy*uz*(1-co) - ux*si,
    uz*ux*(1-co) - uy*si, uz*uy*(1-co)+ux*si, co + pow(uz, 2)*(1-co)
  };
  return Matrix(3, 3, R);
}

Matrix Camera::rotateAboutX(double theta){
  double si = sin(theta);
  double co = cos(theta);
  double R[] = {
    1, 0, 0,
    0, co, -si,
    0, si, co
  };
  return Matrix(3, 3, R);
}

Matrix Camera::rotateAboutY(double theta){
  double si = sin(theta);
  double co = cos(theta);
  double R[] = {
    co, 0, si,
    0, 1, 0,
    -si, 0, co
  };
  return Matrix(3, 3, R);
}

void Camera::updateRotationMatrix()
{
  double rotX = rotation.get(0, 0);// / PI * 180);
  double rotY = rotation.get(1, 0);// / PI * 180);
  rotationMatrix = rotateAboutX(rotX) * rotateAboutY(rotY);
}

void Camera::updateCalibrationMatrix()
{
  double C[] = {
    focalLength * KU, 0, WIDTH / 2,
    0, -focalLength * KV, HEIGHT / 2,
    0, 0, 1
  };
  calibrationMatrix = Matrix(3, 3, C);
  calProjMatrix = calibrationMatrix * projectionMatrix;
}

void Camera::updateTransformationMatrix()
{
  Matrix R = rotationMatrix;
  Matrix T = position.transpose();
  double RT[] = {
    R.get(0, 0), R.get(1, 0), R.get(2, 0), T.get(0, 0),
    R.get(0, 1), R.get(1, 1), R.get(2, 1), T.get(0, 1),
    R.get(0, 2), R.get(1, 2), R.get(2, 2), T.get(0, 2),
    0, 0, 0, 1
  };
  cameraTransformation = Matrix(4, 4, RT);
  cameraMatrix = calProjMatrix * cameraTransformation;
  // cameraMatrix.print_matrix();
}

Matrix Camera::normalisePoint(Matrix p){
  p.set(0, 0, p.get(0, 0) / p.get(0, 2));
  p.set(0, 1, p.get(0, 1) / p.get(0, 2));
  return p;
}

Matrix Camera::getScreenPosition(Matrix p)
{
  if(p.shape.width != 1 || p.shape.height != 4){
    return Matrix(1, 3);
  }
  p = p - homogPosition;
  // p.set(0, 3, 1);
  // p.print_matrix();
  return normalisePoint(cameraMatrix * p);
}

Matrix Camera::getFacing()
{
  double forw[] = {0, 0, 1};
  Matrix forward = Matrix(1, 3, forw);
  double rotX = rotation.get(0, 0);// / PI * 180);
  double rotY = rotation.get(1, 0);// / PI * 180);
  Matrix facing = rotateAboutX(rotX) * forward;
  facing =  rotateAboutY(rotY) * facing;
  // rotationMatrix = rotateAboutX(rotX) * rotateAboutY(rotZ);
  // Matrix facing = rotationMatrix * forward;
  facing.set(0, 0, -facing.get(0, 0));
  facing.set(0, 1, -facing.get(0, 1));
  return facing;
}

Matrix Camera::getUp()
{
  double u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  double rotX = rotation.get(0, 0);// / PI * 180);
  double rotY = rotation.get(1, 0);// / PI * 180);
  Matrix cUp = rotateAboutX(rotX) * up;
  cUp =  rotateAboutY(rotY) * cUp;
  // Matrix cUp = rotationMatrix * up;
  // cUp.set(0, 0, -cUp.get(0, 0));
  cUp.set(0, 2, -cUp.get(0, 2));
  return cUp;
}

Matrix Camera::getPosition(){
  return position.copy();
}

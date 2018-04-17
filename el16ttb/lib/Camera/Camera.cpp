#include "mbed.h"
#include "Camera.h"
#include <math.h>

void Camera::init()
{
  this->position = Matrix(3, 1);
  this->homogPosition = Matrix(1, 4);
  this->rotation = Matrix(3, 1);
  this->Xunit = Matrix(3, 1);
  this->Xunit.set(0, 0, 1);
  this->Zunit = Matrix(3, 1);
  this->Zunit.set(1, 0, 1);
  this->rotationMatrix = Matrix(3, 3);
  this->calibrationMatrix = Matrix(3, 3);
  this->projectionMatrix = Matrix(4, 3);
  this->projectionMatrix.set(0, 0, 1);
  this->projectionMatrix.set(1, 1, 1);
  this->projectionMatrix.set(2, 2, 1);
  this->cameraTransformation = Matrix(4, 4);
  this->SetFocalLength(0.028);
  this->SetPosition(0, 0, 0);
  this->SetRotation(0, 0);
}

void Camera::SetPosition(double x, double y, double z)
{
  this->position.set(0, 0, x);
  this->position.set(1, 0, y);
  this->position.set(2, 0, z);
  this->homogPosition.set(0, 0, x);
  this->homogPosition.set(0, 1, y);
  this->homogPosition.set(0, 2, z);
  this->homogPosition.set(0, 3, 1);
  this->UpdateTransformationMatrix();
}

void Camera::SetRotation(double x, double z)
{
  this->rotation.set(0, 0, x);
  this->rotation.set(1, 0, 0);
  this->rotation.set(2, 0, z);
  this->UpdateRotationMatrix();
  this->UpdateTransformationMatrix();
}

void Camera::SetFocalLength(double f)
{
  this->focalLength = f;
  this->UpdateCalibrationMatrix();
}

Matrix Camera::RotationMatrix(Matrix u, double theta)
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

void Camera::UpdateRotationMatrix()
{
  double rotX = this->rotation.get(0, 0);// / PI * 180);
  double rotZ = this->rotation.get(2, 0);// / PI * 180);
  Matrix matZ = this->RotationMatrix(this->Zunit, rotZ);
  Matrix matX = this->RotationMatrix(this->Xunit * matZ, rotX);
  this->rotationMatrix = matZ * matX;
}

void Camera::UpdateCalibrationMatrix()
{
  double C[] = {
    this->focalLength * KU, 0, WIDTH / 2,
    0, -this->focalLength * KV, HEIGHT / 2,
    0, 0, 1
  };
  this->calibrationMatrix = Matrix(3, 3, C);
  this->calProjMatrix = this->calibrationMatrix * this->projectionMatrix;
}

void Camera::UpdateTransformationMatrix()
{
  Matrix R = this->rotationMatrix;
  Matrix T = this->position.transpose();
  double RT[] = {
    R.get(0, 0), R.get(1, 0), R.get(2, 0), T.get(0, 0),
    R.get(0, 1), R.get(1, 1), R.get(2, 1), T.get(0, 1),
    R.get(0, 2), R.get(1, 2), R.get(2, 2), T.get(0, 2),
    0, 0, 0, 1
  };
  this->cameraTransformation = Matrix(4, 4, RT);
  this->cameraMatrix = this->calProjMatrix * this->cameraTransformation;
  // this->cameraMatrix.print_matrix();
}

Matrix Camera::NormalisePoint(Matrix p){
  p.set(0, 0, p.get(0, 0) / p.get(0, 2));
  p.set(0, 1, p.get(0, 1) / p.get(0, 2));
  return p;
}

Matrix Camera::GetScreenPosition(Matrix p)
{
  if(p.shape.width != 1 || p.shape.height != 4){
    return Matrix(1, 3);
  }
  p = p - this->homogPosition;
  // p.set(0, 3, 1);
  // p.print_matrix();
  return this->NormalisePoint(this->cameraMatrix * p);
}

Matrix Camera::GetFacing()
{
  Matrix R = this->rotationMatrix;
  double forw[] = {0, 0, 1};
  Matrix forward = Matrix(1, 3, forw);
  return R * forward;
}
Matrix Camera::GetPosition(){
  return this->position.copy();
}

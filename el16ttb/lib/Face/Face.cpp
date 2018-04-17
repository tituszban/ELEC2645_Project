#include "Face.h"

Face::Face(){

}

void Face::setTexture(Texture texture){
  this->texture = texture;
}

void Face::updateCorners(){
  this->texture = this->getEmptyTexture();
  // pair<Matrix, Matrix> perpVectors = getPerpVectors(facing);
  // replace with cross product
  Matrix c1 = pos2homogPos(position + perpVectors.first * 0.5 + perpVectors.second * 0.5);
  Matrix c2 = pos2homogPos(position + perpVectors.first * 0.5 + perpVectors.second * -0.5);
  Matrix c3 = pos2homogPos(position + perpVectors.first * -0.5 + perpVectors.second * 0.5);
  Matrix c4 = pos2homogPos(position + perpVectors.first * -0.5 + perpVectors.second * -0.5);
  pair<pair<Matrix, Matrix>, pair<Matrix, Matrix> > c(pair<Matrix, Matrix>(c1, c2), pair<Matrix, Matrix>(c3, c4));
  this->corners = c;
  this->faceChanged = false;
}

void Face::setDirection(Matrix normal, Matrix up){
  this->normal = normal;
  this->up = up;
  this->faceChanged = true;
}

void Face::setPosition(Matrix position){
  this->position = position;
  this->faceChanged = true;
}

void Face::render(Camera &cam, Renderer &renderer){
  Matrix rel = this->position - cam.GetPosition().transpose();
  rel = rel / rel.distance(Matrix(1, 3));
  double facing_angle = this->normal.dot(rel);
  if(facing_angle > 0)
    return;
  Matrix cAT = cam.GetScreenPosition(this->corners.first.first);
  Matrix cAB = cam.GetScreenPosition(this->corners.first.second);
  Matrix cBT = cam.GetScreenPosition(this->corners.second.first);
  Matrix cBB = cam.GetScreenPosition(this->corners.second.second);
  double distA = cAT.homogDistance(cAB);
  double distB = cBT.homogDistance(cBB);
  int mDist = ceil(max(distA, distB));
  // printf("mDist found: %d\n", mDist);
  if(mDist > 100){
    return;
  }
  vector<double> lXA = lerp(cAT.get(0, 0), cAB.get(0, 0), mDist);
  vector<double> lYA = lerp(cAT.get(0, 1), cAB.get(0, 1), mDist);
  vector<double> lZA = lerp(cAT.get(0, 2), cAB.get(0, 2), mDist);
  vector<double> lXB = lerp(cBT.get(0, 0), cBB.get(0, 0), mDist);
  vector<double> lYB = lerp(cBT.get(0, 1), cBB.get(0, 1), mDist);
  vector<double> lZB = lerp(cBT.get(0, 2), cBB.get(0, 2), mDist);
  // printf("edges found\n");
  renderer.addLine(cAT, cAB, 1);
  renderer.addLine(cAT, cBT, 1);
  renderer.addLine(cAB, cBB, 1);
  renderer.addLine(cBT, cBB, 1);
  // printf("edges drawn\n");
  for(int i = 0; i < mDist; i++)
  {
    double p = (double)i / (double)mDist;
    int pT = floor(p * this->texture.height);
    vector<int> line_texture = this->texture.texture[pT];
    double cAn[] = {lXA[i], lYA[i], lZA[i]};
    Matrix cA = Matrix(1, 3, cAn);
    double cBn[] = {lXB[i], lYB[i], lZB[i]};
    Matrix cB = Matrix(1, 3, cBn);
    renderer.addPatternLine(cA, cB, line_texture);
  }
}

Texture Face::getEmptyTexture(){
  vector<vector<int> > textu(1, vector<int>(1, 0));
  Texture empty = {1, 1, textu};
  return empty;
}

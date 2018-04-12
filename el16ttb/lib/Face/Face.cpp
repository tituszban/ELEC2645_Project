#include "Face.h"

Face::Face(){

}

Face::Face(Matrix position, Matrix facing){
  this->position = position;
  this->facing = facing;
  this->texture = this->getEmptyTexture();
  pair<Matrix, Matrix> perpVectors = getPerpVectors(facing);
  Matrix c1 = pos2homogPos(position + perpVectors.first * 0.5 + perpVectors.second * 0.5);
  Matrix c2 = pos2homogPos(position + perpVectors.first * 0.5 + perpVectors.second * -0.5);
  Matrix c3 = pos2homogPos(position + perpVectors.first * -0.5 + perpVectors.second * 0.5);
  Matrix c4 = pos2homogPos(position + perpVectors.first * -0.5 + perpVectors.second * -0.5);
  pair<pair<Matrix, Matrix>, pair<Matrix, Matrix> > c(pair<Matrix, Matrix>(c1, c2), pair<Matrix, Matrix>(c3, c4));
  this->corners = c;
}

void Face::setTexture(Texture texture){
  this->texture = texture;
}

void Face::render(Camera &cam, Renderer &renderer){
  Matrix rel = this->position - cam.GetPosition().transpose();
  rel = rel / rel.distance(Matrix(1, 3));
  double facing_angle = this->facing.dot(rel);
  if(facing_angle > 0)
    return;
  Matrix cAT = cam.GetScreenPosition(this->corners.first.first);
  Matrix cAB = cam.GetScreenPosition(this->corners.first.second);
  Matrix cBT = cam.GetScreenPosition(this->corners.second.first);
  Matrix cBB = cam.GetScreenPosition(this->corners.second.second);
  double distA = cAT.homogDistance(cAB);
  double distB = cBT.homogDistance(cBB);
  int mDist = ceil(max(distA, distB));
  vector<double> lXA = lerp(cAT.get(0, 0), cAB.get(0, 0), mDist);
  vector<double> lYA = lerp(cAT.get(0, 1), cAB.get(0, 1), mDist);
  vector<double> lZA = lerp(cAT.get(0, 2), cAB.get(0, 2), mDist);
  vector<double> lXB = lerp(cBT.get(0, 0), cBB.get(0, 0), mDist);
  vector<double> lYB = lerp(cBT.get(0, 1), cBB.get(0, 1), mDist);
  vector<double> lZB = lerp(cBT.get(0, 2), cBB.get(0, 2), mDist);
  for(int i = 0; i < mDist; i++)
  {
    double p = (double)i / (double)mDist;
    int pT = floor(p * this->texture.height);
    // vector<int> texture(5, 1);
    // int pattern[] = {0, 1, 0};
    // vector<int> texture(pattern, pattern + sizeof(pattern) / sizeof(int));
    // vector<int> texture(this->texture.texture.begin() + pT * this->texture.width,
    //                     this->texture.texture.begin() + (pT + 1) * this->texture.width);
    vector<int> line_texture = this->texture.texture[pT];
    double cAn[] = {lXA[i], lYA[i], lZA[i] + 0.1};
    Matrix cA = Matrix(1, 3, cAn);
    double cBn[] = {lXB[i], lYA[i], lZA[i] + 0.1};
    Matrix cB = Matrix(1, 3, cBn);
    renderer.addPatternLine(cA, cB, line_texture);
  }
  renderer.addLine(cAT, cAB, 1);
  renderer.addLine(cAT, cBT, 1);
  renderer.addLine(cAB, cBB, 1);
  renderer.addLine(cBT, cBB, 1);
}

Texture Face::getEmptyTexture(){
  vector<vector<int> > textu(1, vector<int>(1, 0));
  Texture empty = {1, 1, textu};
  return empty;
}

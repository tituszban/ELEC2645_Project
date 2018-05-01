#include "Face.h"

Face::Face(){
  forceRender = false;
}

void Face::setTexture(Texture texture){
  this->texture = texture;
}

void Face::updateCorners(){
  // this->texture = this->getEmptyTexture();
  Matrix c1 = pos2homogPos(position + this->left * this->halfWidth + this->up * this->halfHeight);
  Matrix c2 = pos2homogPos(position + this->left * this->halfWidth + this->up * -this->halfHeight);
  Matrix c3 = pos2homogPos(position + this->left * -this->halfWidth + this->up * this->halfHeight);
  Matrix c4 = pos2homogPos(position + this->left * -this->halfWidth + this->up * -this->halfHeight);
  pair<pair<Matrix, Matrix>, pair<Matrix, Matrix> > c(pair<Matrix, Matrix>(c1, c2), pair<Matrix, Matrix>(c3, c4));
  this->corners = c;
  this->faceChanged = false;
}

void Face::setDirection(Matrix normal, Matrix up){
  this->normal = normal;
  this->up = up;
  this->left = normal.cross(up);
  this->faceChanged = true;
}

void Face::setPosition(Matrix position){
  this->position = position;
  this->faceChanged = true;
}

void Face::setSize(float width, float height){
  this->halfWidth = width * 0.5;
  this->halfHeight = height * 0.5;
  this->faceChanged = true;
}

void Face::render(Camera &cam, Renderer &renderer){
  Matrix rel = this->position - cam.getPosition().transpose();
  rel = rel / rel.distance(Matrix(1, 3));
  float facing_angle = this->normal.dot(rel);
  if(facing_angle > 0 && !forceRender)
    return;
  if(cam.getFacing().dot(rel) < 0.55 && !forceRender)
     return;
  if(this->faceChanged)
    this->updateCorners();
  Matrix cAT = cam.getScreenPosition(this->corners.first.first);
  Matrix cAB = cam.getScreenPosition(this->corners.first.second);
  Matrix cBT = cam.getScreenPosition(this->corners.second.first);
  Matrix cBB = cam.getScreenPosition(this->corners.second.second);
  float distA = cAT.homogDistance(cAB);
  float distB = cBT.homogDistance(cBB);
  int mDist = ceil(max(distA, distB));
  if((mDist > 100 && !forceRender) || mDist > 200){
    return;
  }
  vector<float> lXA = lerp(cAT.get(0, 0), cAB.get(0, 0), mDist);
  vector<float> lYA = lerp(cAT.get(0, 1), cAB.get(0, 1), mDist);
  vector<float> lZA = lerp(cAT.get(0, 2), cAB.get(0, 2), mDist);
  vector<float> lXB = lerp(cBT.get(0, 0), cBB.get(0, 0), mDist);
  vector<float> lYB = lerp(cBT.get(0, 1), cBB.get(0, 1), mDist);
  vector<float> lZB = lerp(cBT.get(0, 2), cBB.get(0, 2), mDist);
  for(int i = 0; i < mDist; i++)
  {
    float p = (float)i / (float)mDist;
    int pT = floor(p * this->texture.height);
    vector<int> line_texture = this->texture.texture[pT];
    float cAn[] = {lXA[i], lYA[i], lZA[i]};
    Matrix cA = Matrix(1, 3, cAn);
    float cBn[] = {lXB[i], lYB[i], lZB[i]};
    Matrix cB = Matrix(1, 3, cBn);
    renderer.addPatternLine(cA, cB, line_texture);
  }
}

Texture Face::getEmptyTexture(){
  vector<vector<int> > textu(1, vector<int>(1, 0));
  Texture empty = {1, 1, textu};
  return empty;
}

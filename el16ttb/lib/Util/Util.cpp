#include "Util.h"

Matrix pos2homogPos(Matrix pos){
  Matrix mat = Matrix(1, 4);

  if(pos.shape.width != 1 && pos.shape.height != 3){
    return mat;
  }

  mat.set(0, 0, pos.get(0, 0));
  mat.set(0, 1, pos.get(0, 1));
  mat.set(0, 2, pos.get(0, 2));
  mat.set(0, 3, 1);
  return mat;
}

vector<float> lerp(float a, float b, int length)
{
  vector<float> data(length);
  float step = (b - a) / (float)length;
  for(int i = 0; i < length; i++){
    data[i] = a + step * i;
  }
  return data;
}

pair<Matrix, Matrix> getPerpVectors(Matrix fwd)
{
  pair<Matrix, Matrix> p(Matrix(1, 3), Matrix(1, 3));
  if(fwd.shape.height != 3 || fwd.shape.width != 1){
    return p;
  }
  if(fwd.get(0, 0) == 0 && fwd.get(0, 1) == 0){
    p.first.set(0, 0, 1);
    p.second.set(0, 1, 1);
  }
  else{
    float X = fwd.get(0, 0);
    float Y = fwd.get(0, 1);
    float Z = fwd.get(0, 2);
    p.first.set(0, 0, abs(-Y));
    p.first.set(0, 1, abs(X));
    p.second.set(0, 0, abs(-X*Z));
    p.second.set(0, 1, abs(-Y*Z));
    p.second.set(0, 2, X*X+Y*Y);
  }
  if(p.first.get(0, 1) > p.second.get(0, 1)){ // set X, Y order
    Matrix temp = p.first.copy();
    p.first = p.second;
    p.second = temp;
  }
  return p;
}

void memoryBenchmark(string id){
  // perform free memory check
  // printf("%s\n", id);
  int blockSize = 16;
  int i = 1;
  // printf("Checking memory with blocksize %d char ...\n", blockSize);
  while (true) {
      char *p = (char *) malloc(i * blockSize);
      if (p == NULL)
          break;
      free(p);
      ++i;
  }
  printf("id: %s\tmemory left: %d char\n", id.c_str(), (i - 1) * blockSize);
}


Texture arrayToTexture(int width, int height, const int* array){
  vector<vector<int> > textu;
  for(int h = 0; h < height; h++){
    vector<int> line;
    for(int w = 0; w < width; w++){
      line.push_back(array[h * width + w]);
    }
    textu.push_back(line);
  }
  Texture texture = {width, height, textu};
  return texture;
}

Texture flipTexture(Texture tx, int d){
  if(d == 0){
    for(int w = 0; w < tx.width / 2; w++){
      for(int h = 0; h < tx.height; h++){
        int temp = tx.texture[h][w];
        tx.texture[h][w] = tx.texture[h][tx.width - w - 1];
        tx.texture[h][tx.width - w - 1] = temp;
      }
    }
  }
  else if(d == 1){
    for(int h = 0; h < tx.height / 2; h++){
      for(int w = 0; w < tx.width; w++){
        int temp = tx.texture[h][w];
        tx.texture[h][w] = tx.texture[tx.height - h - 1][w];
        tx.texture[tx.height - h - 1][w] = temp;
      }
    }
  }
  else if(d == 2)
  {
    return flipTexture(flipTexture(tx, 0), 1);
  }
  return tx;
}

#include <Explosion.h>

Explosion::Explosion(){
  explosionTime = 0.5;
  timer = 0;
  toBeRemoved = false;
  setSize(1.5);
  textures.push_back(arrayToTexture(20, 20, explosion0Sprite));
  textures.push_back(arrayToTexture(20, 20, explosion1Sprite));
  textures.push_back(arrayToTexture(20, 20, explosion2Sprite));
  textures.push_back(arrayToTexture(20, 20, explosion3Sprite));
  textures.push_back(arrayToTexture(20, 20, explosion4Sprite));
  textures.push_back(arrayToTexture(20, 20, explosion5Sprite));
  explosion.setTexture(textures[0]);
}

void Explosion::setPosition(Matrix position){
  this->position = position;
  explosion.setPosition(position);
}

void Explosion::setSize(double size){
  explosion.setSize(size, size);
}

void Explosion::update(double dt){
  timer += dt;
  if(timer >= explosionTime){
    toBeRemoved = true;
    return;
  }
  int explosionIndex = floor(timer / explosionTime * 6.0);
  explosion.setTexture(textures[explosionIndex]);
}

void Explosion::render(Camera &cam, Renderer &renderer){
  double u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  Matrix rel = position - cam.getPosition().transpose();
  rel = rel / rel.distance(Matrix(1, 3));
  explosion.setDirection(-rel, up);
  explosion.render(cam, renderer);
}

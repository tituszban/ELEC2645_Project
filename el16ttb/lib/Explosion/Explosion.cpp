#include <Explosion.h>

Explosion::Explosion(){
  reset();
}

Explosion::Explosion(Matrix position, float size){
  reset();
  setPosition(position);
  setSize(size);
}

void Explosion::reset(){
  explosionTime = 0.5;
  timer = 0;
  toBeRemoved = false;
  explosionIndexPre = -1;
  setSize(1.5);
}

void Explosion::setPosition(Matrix position){
  this->position = position;
  explosion.setPosition(position);
}

void Explosion::setSize(float size){
  explosion.setSize(size, size);
}

void Explosion::update(float dt){
  timer += dt;
  if(timer >= explosionTime){
    toBeRemoved = true;
    return;
  }
  int explosionIndex = floor(timer / explosionTime * 6.0);
  if(explosionIndex != explosionIndexPre){
    switch(explosionIndex){
      case 0: explosion.setTexture(arrayToTexture(20, 20, explosion0Sprite)); break;
      case 1: explosion.setTexture(arrayToTexture(20, 20, explosion1Sprite)); break;
      case 2: explosion.setTexture(arrayToTexture(20, 20, explosion2Sprite)); break;
      case 3: explosion.setTexture(arrayToTexture(20, 20, explosion3Sprite)); break;
      case 4: explosion.setTexture(arrayToTexture(20, 20, explosion4Sprite)); break;
      case 5: explosion.setTexture(arrayToTexture(20, 20, explosion5Sprite)); break;
    }
  }
  explosionIndexPre = explosionIndex;
}

void Explosion::render(Camera &cam, Renderer &renderer){
  float u[] = {0, 1, 0};
  Matrix up = Matrix(1, 3, u);
  Matrix rel = position - cam.getPosition().transpose();
  rel = rel / rel.distance(Matrix(1, 3));
  explosion.setDirection(-rel, up);
  explosion.render(cam, renderer);
}

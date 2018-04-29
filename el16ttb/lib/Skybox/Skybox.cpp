#include <Skybox.h>

void Skybox::render(Camera &cam, Renderer &renderer){
  for(int i = 0; i < STAR_COUNT; i++){
    float st[] = {stars[i][0], stars[i][1], stars[i][2]}; // const do dynamic
    Matrix star = Matrix(1, 3, st);
    if(cam.getFacing().dot(star) < 0.75)
      renderer.addSkyboxPoint(cam.getScreenPosition(pos2homogPos(star + cam.getPosition().transpose())), 1);
  }
}

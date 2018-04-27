#include <Skybox.h>

void Skybox::render(Camera &cam, Renderer &renderer){
  for(int i = 0; i < STAR_COUNT; i++){
    double st[] = {stars[i][0], stars[i][1], stars[i][2]};
    Matrix star = Matrix(1, 3, st) + cam.GetPosition().transpose();
    if(cam.GetFacing().dot(star) > 0.5){
      renderer.addSkyboxPoint(cam.GetScreenPosition(pos2homogPos(star)), 1);
    }
  }
}

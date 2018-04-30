#include <GameEngine.h>

void mainGame(Controller &cont){
  // SETUP
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;
  XWing xwing = XWing(Matrix(1, 3), cont);
  Empire empire;

  bool gameOver = false;

  std::clock_t framePrev = std::clock();

  while(!gameOver)
  {
    // RESET
    cont.lcdClear();
    renderer.clearBuffer();

    std::clock_t now = std::clock();
    float dt = (now - framePrev) / (float) CLOCKS_PER_SEC * 0.25;
    framePrev = now;

    gameOver = cont.buttonPressed(START) || xwing.isGameOver() != 0 || empire.isGameOver();

    // COLLISION DETECTION
    empire.checkCollisions(xwing);

    // UPDATE TARGETS
    xwing.updateTargets(empire.getTargets(), empire.getTargetPositions());

    // UPDATE
    xwing.update(dt, cont, cam, empire.getShuttlePosition());
    empire.update(dt, xwing.getPosition(), xwing.getFlatFacing());

    // RENDER
    skybox.render(cam, renderer);
    xwing.render(cam, renderer);
    empire.render(cam, renderer);

    // ENDLOOP
    renderer.render(cont);
    cont.lcdRefresh();
    // wait(0.05);
  }

  // ENDGAME
}

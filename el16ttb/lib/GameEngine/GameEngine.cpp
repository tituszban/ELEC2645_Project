#include <GameEngine.h>

void gameManager(Controller &cont){
  int play = 0;
  while(play == 0){
    play = mainGame(cont);
  }
}

int mainGame(Controller &cont){
  // SETUP
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;
  XWing xwing = XWing(Matrix(1, 3), cont);
  Empire empire;

  int gameResult = -1;
  /*
  -1 game in progress
  0 quit
  1 restart
  2 success
  3 destroyed
  4 shuttle destroyed
  */

  std::clock_t framePrev = std::clock();

  int empireAction = 0;

  while(gameResult < 0)
  {
    // RESET
    cont.lcdClear();
    renderer.clearBuffer();

    // GET FRAME TIME
    std::clock_t now = std::clock();
    float dt = (now - framePrev) / (float) CLOCKS_PER_SEC * 0.25;
    framePrev = now;

    // gameOver = cont.buttonPressed(BACK) || xwing.isGameOver() != 0 || empire.isGameOver();  // check game over states

    // COLLISION DETECTION
    empire.checkCollisions(xwing);

    // UPDATE TARGETS
    xwing.updateTargets(empire.getTargets(), empire.getTargetPositions());

    // UPDATE
    xwing.update(dt, cont, cam, empireAction);
    empireAction = empire.update(dt, xwing.getPosition(), xwing.getFlatFacing());

    // RENDER
    skybox.render(cam, renderer);
    xwing.render(cam, renderer);
    empire.render(cam, renderer);

    // ENDLOOP
    renderer.render(cont);
    cont.lcdRefresh();

    int pauseResult = 0;
    if(cont.buttonPressed(START)){
      pauseResult = pause(cont, renderer);
      framePrev = std::clock();
    }
    int xWingResult = xwing.isGameOver();
    gameResult = (pauseResult == 3 || cont.buttonPressed(BACK)) ? 0 :
      (pauseResult == 1 ? 1 :
      (xWingResult == 1 ? 2 :
      (xWingResult == -1 ? 3 :
      (empire.isGameOver() ? 4 : -1))));
  }
  printf("gameResult: %d\n", gameResult);
  // ENDGAME
  return gameResult != 1;
}

int pause(Controller &cont, Renderer &renderer){
  int selected = -1;
  int optionSelected = -1;
  int menuSelected = 0;
  Direction dirPre = CENTRE;
  int pointerPositions[] = {8, 17, 26, 36};
  while(selected < 0){
    renderer.addUISprite(3, 2, 79, 44, menuframeSprite);
    if(optionSelected >= 0){
      renderer.addUISprite(3, 2, 79, 44, menuoptionsSprite);
      if(optionSelected == 0){renderer.addUISprite(3, 2, 79, 44, cont.muted ? menuoptionss0Sprite : menuoptionss1Sprite);}
      else if(optionSelected == 1){renderer.addUISprite(3, 2, 79, 44, menuoptionss2Sprite);}
      else if(optionSelected == 2){renderer.addUISprite(3, 2, 79, 44, menuoptionss3Sprite);}
      else if(optionSelected == 3){renderer.addUISprite(3, 2, 79, 44, menuoptionss4Sprite);}
      Direction dir = cont.joystickDirection();
      if(dirPre != dir){
        dirPre = cont.joystickDirection();
        optionSelected = mod(optionSelected - (dirPre == N) + (dirPre == S), 4);
        if(optionSelected == 0 && (dirPre == W || dirPre == E)){cont.muted = !cont.muted;}
      }

      if(optionSelected == 1){cont.contrast = max(min(cont.contrast - ((dir == W) - (dir == E)) * CONTR_STEP, CONTR_MAX), CONTR_MIN); cont.lcdContrast(cont.contrast);}
      if(optionSelected == 2){cont.brightness = max(min(cont.brightness - ((dir == W) - (dir == E)) * BRIGHT_STEP, BRIGH_MAX), BRIGHT_MIN); cont.lcdSetBrightness(cont.brightness);}
      if((optionSelected == 3 && cont.buttonPressed(A)) || cont.buttonPressed(START) || cont.buttonPressed(BACK)){optionSelected = -1;}
    }
    else{
      renderer.addUISprite(3, 2, 79, 44, menutextSprite);
      if(dirPre != cont.joystickDirection()){
        dirPre = cont.joystickDirection();
        menuSelected = mod(menuSelected - (dirPre == N) + (dirPre == S), 4);
      }
      renderer.addUISprite(18, pointerPositions[menuSelected], 5, 3, menupointerSprite);
      if(cont.buttonPressed(A)){
        if(menuSelected == 2){optionSelected = 0;}
        else{selected = menuSelected;}
      }
      if(cont.buttonPressed(START)){selected = 0;}
      if(cont.buttonPressed(BACK)){selected = 3;}
    }
    wait(0.05);
    renderer.render(cont);
    cont.lcdRefresh();
  }
  return selected;
}

int mainMenu(Controller &cont)
{
  Renderer renderer;
  Camera cam;
  cam.init();
  cam.setPosition(0, 0, 0);
  cam.setRotation(0, 0);
  float crawlAngle = PI * 0.1;
  float cs[] = {0, -0.2, 2};
  Matrix crawlStart = Matrix(1, 3, cs);
  float cu[] = {0, cos(crawlAngle), sin(crawlAngle)};
  Matrix crawlUp = Matrix(1, 3, cu);
  float cn[] = {0, sin(crawlAngle), -cos(crawlAngle)};

  Face crawlH;
  crawlH.forceRender = true;
  crawlH.setDirection(Matrix(1, 3, cn), crawlUp);
  crawlH.setSize(5, 3);
  Face crawlF;
  crawlF.forceRender = true;
  crawlF.setDirection(Matrix(1, 3, cn), crawlUp);
  crawlF.setSize(5, 2);

  float dist = 0;
  int selected = -1;
  int menuPoint = 0;

  Direction dirPre = CENTRE;

  while(selected == -1){
    cont.lcdClear();
    renderer.clearBuffer();

    if(dist < 2.5)
      dist += 0.03;
    crawlH.setPosition(crawlStart + crawlUp * dist);
    crawlH.setTexture(flipTexture(arrayToTexture(84, 50, crawl0Sprite), 0));
    crawlH.render(cam, renderer);
    crawlF.setPosition(crawlStart + crawlUp * (dist - 2.5));
    crawlF.setTexture(flipTexture(arrayToTexture(84, 34, menuPoint == 0 ? crawl1Sprite :
      (menuPoint == 1 ? crawl2Sprite : crawl3Sprite)), 0));
    crawlF.render(cam, renderer);

    if(cont.joystickDirection() != dirPre){
      dirPre = cont.joystickDirection();
      menuPoint = mod(menuPoint - (dirPre == N) + (dirPre == S), 3);
      // if(dirPre == N){
      //   menuPoint = mod(menuPoint - 1, 3);
      // }
      // if(dirPre == S){
      //   menuPoint = mod(menuPoint + 1, 3);
      // }
    }
    if(cont.buttonPressed(A) || cont.buttonPressed(START)){
      selected = menuPoint;
    }

    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }

  return selected;
}

void cutscene(Controller &cont){

}

void tutorial(Controller &cont){

}

void showcase(Controller &cont){
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;

  float rot = 2;
  float tfPos[] = {0, 0, 1.7};
  float shPos[] = {10, 0, 2.5};

  TieFighter tf = TieFighter(Matrix(1, 3, tfPos), rot);
  ImperialShuttle sh = ImperialShuttle(Matrix(1, 3, shPos), rot);

  cam.setRotation(0, 0);

  bool mode = 0;

  float pos = 0;
  float startPos = 0;
  float targetPos = 10;
  float transitionTimer = 0;

  while(!cont.buttonPressed(A)){
    cont.lcdClear();
    cont.lcdPrintString("Showcase", 17, 0);
    cont.lcdPrintString("A-Change mode", 4, 2);
    cont.lcdPrintString("X/B-Ship,Angle", 1, 3);
    cont.lcdPrintString("BACK-main menu", 1, 5);
    cont.lcdRefresh();
  }

  while(!cont.buttonPressed(BACK)){
    cont.lcdClear();
    renderer.clearBuffer();

    if(transitionTimer > 0){
      transitionTimer -= 0.1;
      pos = (targetPos - startPos) * transitionTimer + startPos;
    }

    cam.setPosition(pos, 0, 0);

    mode = (mode + cont.buttonPressed(A)) % 2;

    if(mode == 0){
      rot += 0.05;
      if(cont.buttonPressed(X) || cont.buttonPressed(B)){
        startPos = targetPos;
        targetPos = 10 - targetPos;
        transitionTimer = 1;
      }
    }
    else {rot += (cont.buttonDown(X) - cont.buttonDown(B)) * 0.05;}
    tf.setRotation(rot);
    sh.setRotation(rot);

    tf.render(cam, renderer);
    sh.render(cam, renderer);

    skybox.render(cam, renderer);
    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
}

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
  SoundManager sm;
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
    float dt = (now - framePrev) / (float) CLOCKS_PER_SEC * SPEED_FACTOR;
    framePrev = now;

    // COLLISION DETECTION
    empire.checkCollisions(xwing);

    // UPDATE TARGETS
    xwing.updateTargets(empire.getTargets(), empire.getTargetPositions());

    // UPDATE
    xwing.update(dt, cont, cam, sm, empireAction);
    empireAction = empire.update(dt, xwing.getPosition(), xwing.getFlatFacing());

    // RENDER
    skybox.render(cam, renderer);
    xwing.render(cam, renderer);
    empire.render(cam, renderer);

    // ENDLOOP
    renderer.render(cont);
    cont.lcdRefresh();

    sm.update(dt / SPEED_FACTOR, cont);

    cont.muted = (cont.forceMuted && cont.muted) || (!cont.forceMuted && cont.readPot() < 0.2f);

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
  cont.toneContinous(0);
  if(gameResult == 2 || gameResult == 3 || gameResult == 4){
    renderer.addUISprite(0, 0, 84, 48, gameResult == 2 ? missionsuccessSprite : (
      gameResult == 3 ? missionfailedxwingSprite : missionfailedshuttleSprite
    ));
  }

  renderer.render(cont);
  cont.lcdRefresh();
  if(gameResult != 0 && gameResult != 1){
    while(!cont.buttonPressed(A) && !cont.buttonPressed(A) && !cont.buttonPressed(START) && !cont.buttonPressed(BACK)){
      wait(0.1);
    }
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
        if(optionSelected == 0 && (dirPre == W || dirPre == E)){cont.muted = !cont.muted; cont.forceMuted = true; }
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
    cont.muted = (cont.forceMuted && cont.muted) || (!cont.forceMuted && cont.readPot() < 0.2f);
    wait(0.05);
    renderer.render(cont);
    cont.lcdRefresh();
  }
  return selected;
}

int mainMenu(Controller &cont)
{
  // playTheme(cont);
  Renderer renderer;
  Camera cam;
  cam.init();
  cam.setPosition(0, 0, 0);
  cam.setRotation(0, 0);
  float crawlAngle = PI * 0.05;
  float cs[] = {0, -1.2, 2.3};
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

  cont.muted = (cont.forceMuted && cont.muted) || (!cont.forceMuted && cont.readPot() < 0.2f);
  std::clock_t noteStart = std::clock();
  int noteIndex = 0;
  cont.tone(SWTheme[noteIndex][0], (float)SWTheme[noteIndex][1] / 1000);

  while(selected == -1){
    cont.lcdClear();
    renderer.clearBuffer();

    if(dist < 2.8f)
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
    }
    if(cont.buttonPressed(A) || cont.buttonPressed(START)){
      selected = menuPoint;
    }
    cont.muted = (cont.forceMuted && cont.muted) || (!cont.forceMuted && cont.readPot() < 0.2f);
    std::clock_t now = std::clock();
    if((now - noteStart) / (float) CLOCKS_PER_SEC * 1000 >= SWTheme[noteIndex][1]){
      noteStart = std::clock();
      noteIndex++;
      if(SWTheme[noteIndex][0] != DELAY)
        cont.tone(SWTheme[noteIndex][0], (float)SWTheme[noteIndex][1] / 1000);
      // else
      //   cont.tone(0, (float)SWTheme[noteIndex][1] / 1000);
    }

    renderer.render(cont);
    cont.lcdRefresh();
    // wait(0.05);
  }

  return selected;
}

void waitPress(Controller &cont){
  while(!cont.buttonPressed(A)){
    wait(0.1);
  }
}

void scene1(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("Welcome!", 18, 1);
  cont.lcdPrintString("Press A", 21, 3);
  cont.lcdPrintString("to continue!", 6, 4);
  cont.lcdRefresh();
  waitPress(cont);
}

void scene2(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("Pilot!", 24, 0);
  cont.lcdPrintString("You have been", 3, 2);
  cont.lcdPrintString("tasked with a", 3, 3);
  cont.lcdPrintString("secret", 24, 4);
  cont.lcdPrintString("mission!", 18, 5);
  cont.lcdRefresh();
  waitPress(cont);
}

void scene3(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("The rebel", 15, 0);
  cont.lcdPrintString("allience needs", 0, 1);
  cont.lcdPrintString("an IMPERIAL", 9, 2);
  cont.lcdPrintString("SHUTTLE for", 9, 3);
  cont.lcdPrintString("their upcoming", 0, 4);
  cont.lcdPrintString("attack", 24, 5);
  cont.lcdRefresh();
  waitPress(cont);
}

void scene4(Controller &cont){
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;
  cam.setPosition(0, 0, 0);
  cam.setRotation(0, 0);

  float rot = 4.1;
  float shPos[] = {7, 0, 15.5};

  ImperialShuttle sh = ImperialShuttle(Matrix(1, 3, shPos), rot);
  float timer = 0;
  float timerPre = 0;
  float speed = 0.4;
  while(!cont.buttonPressed(A) && timer < 4){
    cont.lcdClear();
    renderer.clearBuffer();
    timer += 0.05;
    if(timer > 1 && timerPre <= 1){cam.setFocalLength(0.056);}
    if(timer > 2 && timerPre <= 2){cam.setFocalLength(0.140);}
    timerPre = timer;
    Matrix shPos = sh.getPosition();
    sh.setPosition(shPos + sh.getFacing() * speed);
    float angle = atan2(shPos.get(0, 0), shPos.get(0, 2));
    cam.setRotation(0, -angle);

    skybox.render(cam, renderer);
    sh.render(cam, renderer);
    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
}

void scene5(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("You need to", 9, 0);
  cont.lcdPrintString("hack the", 18, 1);
  cont.lcdPrintString("shuttle so", 12, 2);
  cont.lcdPrintString("Botham spies", 6, 3);
  cont.lcdPrintString("can find and", 6, 4);
  cont.lcdPrintString("collect it!", 9, 5);
  cont.lcdRefresh();
  waitPress(cont);
}

void scene6(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("Watch out!", 12, 0);
  cont.lcdPrintString("The shuttle is", 0, 1);
  cont.lcdPrintString("escorted by", 9, 2);
  cont.lcdPrintString("TIE FIGHTERS", 6, 3);
  cont.lcdPrintString("equiped with", 6, 4);
  cont.lcdPrintString("jammers", 18, 5);
  cont.lcdRefresh();
  waitPress(cont);
}

void scene7(Controller &cont){
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;
  cam.setPosition(0, 0, 0);
  cam.setRotation(0, 0);

  float shRot = PI;
  float shPos[] = {-1, -0.5, 4};
  float tf1Rot = PI * 1.15;
  float tf1Pos[] = {2, 0, 6};
  float tf1Steer = 0;
  float tf2Rot = PI * 1.05;
  float tf2Pos[] = {-4, 1, 8};

  ImperialShuttle sh = ImperialShuttle(Matrix(1, 3, shPos), shRot);
  TieFighter tf1 = TieFighter(Matrix(1, 3, tf1Pos), tf1Rot);
  TieFighter tf2 = TieFighter(Matrix(1, 3, tf2Pos), tf2Rot);

  float timer = 0;
  float shSpeed = 0.01;
  while(!cont.buttonPressed(A) && timer < 2.1){
    cont.lcdClear();
    renderer.clearBuffer();
    timer += 0.05;
    Matrix shPos = sh.getPosition();
    sh.setPosition(shPos + sh.getFacing() * shSpeed);
    float angle = atan2(shPos.get(0, 0), shPos.get(0, 2)) + 0.1 * timer;
    cam.setRotation(0, -angle);

    if(timer > 0.8 && timer < 1.4){tf1Steer = -0.5;}
    else{tf1Steer = 0;}

    tf1.update(0.03, tf1Steer, 0, false);
    tf2.update(0.03, 0, 0, false);

    skybox.render(cam, renderer);
    sh.render(cam, renderer);
    tf1.render(cam, renderer);
    tf2.render(cam, renderer);
    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
}

void scene8(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("Take down the", 3, 1);
  cont.lcdPrintString("fighters and", 6, 2);
  cont.lcdPrintString("hack the", 18, 3);
  cont.lcdPrintString("shuttle!", 18, 4);
  cont.lcdRefresh();
  waitPress(cont);
}

void scene9(Controller &cont){
  cont.lcdClear();
  cont.lcdPrintString("Good luck, and", 0, 1);
  cont.lcdPrintString("may the force", 3, 2);
  cont.lcdPrintString("be with you!", 6, 3);
  cont.lcdRefresh();
  waitPress(cont);
}

void cutscene(Controller &cont){
  scene1(cont);
  scene2(cont);
  scene3(cont);
  scene4(cont);
  scene5(cont);
  scene6(cont);
  scene7(cont);
  scene8(cont);
  scene9(cont);
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

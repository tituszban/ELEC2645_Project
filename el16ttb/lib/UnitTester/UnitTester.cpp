using namespace std;
#include <vector>
#include <algorithm>
#include "mbed.h"
// #include "UnitTester.h"
#include "Matrix.h"
#include "Camera.h"
#include <math.h>
#include "Renderer.h"
#include "Util.h"
#include "Face.h"
#include "Controller.h"
#include "TieFighter.h"
#include "ImperialShuttle.h"
#include "UI.h"
#include "Skybox.h"
#include "Lives.h"
#include "Laser.h"
#include "Explosion.h"
#include "XWing.h"

#include <ctime>


bool MatrixCreationTest(){
  printf("Starting Matrix Creation Test\n");
  printf("Testing M1\n");
  Matrix m1;
  printf("M1 shape: %d:%d\n", m1.shape.width, m1.shape.height);
  m1.print_matrix();

  printf("Testing M2\n");
  std::vector< std::vector<double> > m2Template(4, std::vector<double>(3));
  Matrix m2 = Matrix(m2Template);
  printf("M2 shape: %d:%d\n", m2.shape.width, m2.shape.height);
  m2.print_matrix();

  printf("Testing M3\n");
  Shape m3Shape = {3, 4};
  Matrix m3 = Matrix(m3Shape);
  printf("M3 shape: %d:%d\n", m3.shape.width, m3.shape.height);
  m3.print_matrix();

  printf("Testing M4\n");
  Matrix m4 = Matrix(1, 2);
  printf("M4 shape: %d:%d\n", m4.shape.width, m4.shape.height);
  m4.print_matrix();

  printf("Testing M5\n");
  double tempM5[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 0, 1
  };
  Matrix m5 = Matrix(3, 4, (double*) tempM5);
  printf("M5 shape: %d:%d\n", m5.shape.width, m5.shape.height);
  m5.print_matrix();
  printf("Test completed\n");
  return true;
}

bool MatrixReadWriteTest(){
  printf("Starting Matrix Read-Write Test\n");
  double temp[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 0, 1
  };
  Matrix m1 = Matrix(3, 4, temp);
  m1.print_matrix();
  printf("Read value at (0, 0): %f\n", m1.get(0, 0));
  printf("Read value at (1, 1): %f\n", m1.get(1, 1));
  printf("Read value at (2, 3): %f\n", m1.get(2, 3));
  printf("Write value 10 to (0, 0)\n");
  printf("Write value 14 to (1, 3)\n");
  m1.set(0, 0, 10.0);
  m1.set(1, 3, 14.0);
  m1.print_matrix();

  printf("Test completed\n");
  return true;
}

bool MatrixOperationsTest(){
  printf("Starting Matrix Operations Test\n");
  double temp1[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8
  };
  double temp2[] = {
    8, 7, 6,
    5, 4, 3,
    2, 1, 0
  };
  Matrix m1 = Matrix(3, 3, temp1);
  Matrix m2 = Matrix(3, 3, temp2);
  printf("M1:\n");
  m1.print_matrix();
  printf("M2:\n");
  m2.print_matrix();

  Matrix mp = m1 + m2;
  Matrix mpr = m2 + m1;
  printf("M1 + M2:\n");
  mp.print_matrix();
  printf("M2 + M1:\n");
  mpr.print_matrix();

  Matrix m1n = -m1;
  Matrix m2n = -m2;
  printf("-M1:\n");
  m1n.print_matrix();
  printf("-M2:\n");
  m2n.print_matrix();

  Matrix ms = m1 - m2;
  Matrix msr = m2 - m1;
  printf("M1 - M2:\n");
  ms.print_matrix();
  printf("M2 - M1:\n");
  msr.print_matrix();

  Matrix mm = m1 * m2;
  Matrix mmr = m2 * m1;
  printf("M1 * M2:\n");
  mm.print_matrix();
  printf("M2 * M1:\n");
  mmr.print_matrix();

  Matrix mcm = m1 * 10;
  Matrix mcd = m1 / 10;
  printf("M1 * 10:\n");
  mcm.print_matrix();
  printf("M2 / 10:\n");
  mcd.print_matrix();
  printf("Test completed\n");
  return true;
}

bool MatrixErrorTest(){
  printf("Starting Matrix Error Test\n");
  double temp1[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8
  };
  double temp2[] = {
    8, 7, 6,
    5, 4, 3
  };
  Matrix m1 = Matrix(3, 3, temp1);
  Matrix m2 = Matrix(3, 2, temp2);
  printf("M1:\n");
  m1.print_matrix();
  printf("M2:\n");
  m2.print_matrix();

  Matrix mp = m1 + m2;
  Matrix mn = m1 - m2;
  Matrix mm = m1 * m2;
  printf("Test completed\n");

  return true;
}

bool CameraValueTest(){
  Camera cam;
  cam.init();
  cam.setPosition(0, 0, 6);
  double p[] = {1, 1, -1, 1};
  Matrix point = Matrix(1, 4, p);
  Matrix screenPoint = cam.getScreenPosition(point);
  screenPoint.print_matrix();
  //double v =
  screenPoint = screenPoint / screenPoint.get(0, 2);
  screenPoint.print_matrix();
  return true;
}

bool CameraScaleTest(Controller &cont){
  double posX = 0.5;
  double posZ = 0.5;

  double rotX = 0;
  double rotZ = 0;
  Camera cam;
  cam.init();

  while(!cont.buttonPressed(START)){
    cont.lcdClear();

    rotZ += pow(cont.joystickCoord().x, 3) * -0.4;
    rotX += pow(cont.joystickCoord().y, 3) * -0.15;

    double moveX = (cont.buttonDown(A) ? -1 : 0) + (cont.buttonDown(Y) ? 1 : 0);
    double moveZ = (cont.buttonDown(X) ? -1 : 0) + (cont.buttonDown(B) ? 1 : 0);

    posZ += (moveX * cos(-rotZ) + moveZ * sin(-rotZ)) * 0.3;
    posX += (moveX * sin(-rotZ) + moveZ * cos(-rotZ)) * 0.3;

    cam.setPosition(posX, 1.6, posZ);
    cam.setRotation(rotX, rotZ);

    bool doPrint = cont.buttonPressed(BACK);
    for(int i = -10; i <= 10; i++){
      for(int j = -10; j <= 10; j++){
        for(int k = 0; k < 1; k++){
          if(sqrt(pow(i, 2) + pow(j, 2)) < 10){
            double p[] = {(double)i, (double)k, (double)j, 1};
            Matrix point = Matrix(1, 4, p);
            Matrix screenPoint = cam.getScreenPosition(point);
            if(screenPoint.get(0, 2) > 0){
              //screenPoint = screenPoint / screenPoint.get(0, 2);
              if(screenPoint.get(0, 0) > 0 && screenPoint.get(0, 0) < 84 && screenPoint.get(0, 1) > 0 && screenPoint.get(0, 1) < 48){
                cont.lcdSetPixel((int)screenPoint.get(0, 0),(int)screenPoint.get(0, 1),true);
              }
              // double dist = sqrt(pow(posZ - j, 2) + pow(posX - i, 2) + pow(1.8 - k, 2));
              if(doPrint && i == 0){
                screenPoint.print_matrix();
                //printf("actual distance: %.4f, depth: %.4f\n", dist, screenPoint.get(0, 2));
              }
            }
          }
        }
      }
    }
    cont.lcdRefresh();
  }
  return true;
}

bool RendererDisplayTest(Controller &cont){
  double points_d[][3] = {
    {0, 0, 0},
    {10, 10, 0},
    {30, 10, 5},
    {10, 20, 15},
    {40, 40, 0},
    {10, 40, 0}
  };
  Matrix points[6];
  for(int i = 0; i < 6; i++){
    points[i] = Matrix(1, 3, points_d[i]);
  }
  Renderer renderer;

  int pattern[][9] = {
    {1, 1, 0, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 1, 1, 0, 1, 1, 0},
    {0, 1, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1}
  };
  int indexer = 0;
  while(!cont.buttonPressed(START)){
    cont.lcdClear();
    renderer.clearBuffer();

    for(int i = 0; i < 6; i++){
      renderer.addPoint(points[i], 1);
    }
    renderer.addLine(points[0], points[1], 1);
    renderer.addLine(points[1], points[2], 1);
    renderer.addLine(points[1], points[3], 1);

    vector<int> patt(pattern[indexer], pattern[indexer] + sizeof(pattern[indexer]) / sizeof(int));

    renderer.addPatternLine(points[1], points[4], patt);
    renderer.addPatternLine(points[3], points[5], patt);

    renderer.render(cont);
    cont.lcdRefresh();

    indexer = (indexer + 1) % 9;
  }
  return true;
}

bool FaceRenderTest(Controller &cont){
  printf("Start Test\n\n");
  Renderer renderer;
  Camera cam;
  cam.init();

  double pos[][3] = {
    {1.8, 3, 2.2},
    {1.2, 3, 2.8},
    {1.4, 3, 2.4},
    {1, 2, 3.5}
  };

  double nor[][3] = {
    {0.707, 0, -0.707},
    {0.707, 0, -0.707},
    {-0.707, 0, -0.707},
    {0, 0, -1}
  };

  double up[][3] = {
    {0, 1, 0},
    {0, 1, 0},
    {0, 1, 0}
  };

  double size[][2] = {
    {1, 1.5},
    {1, 1.5},
    {0.85, 0.4}
  };

  vector<vector<int> > textu(1, vector<int>(1, 0));
  Texture empty = {1, 1, textu};
  vector<vector<int> > textuFull(1, vector<int>(1, 1));
  Texture full = {1, 1, textuFull};

  for(int i = 0; i < 3; i++){
    Matrix face_pos = Matrix(1, 3, pos[i]);
    Matrix face_nor = Matrix(1, 3, nor[i]);
    Matrix face_up = Matrix(1, 3, up[i]);
    Face face;
    face.setPosition(face_pos);
    face.setDirection(face_nor, face_up);
    face.setSize(size[i][0], size[i][1]);
    face.setTexture(full);

    cam.setPosition(1, 3, 1);
    cam.setRotation(0, 0);

    face.render(cam, renderer);
  }
  renderer.render(cont);
  cont.lcdRefresh();
  printf("Test completed\n\n");
  return true;
}

#define FLYBY

bool TieFighterRenderTest(Controller &cont){
  printf("Start Test!\n\n");
  memoryBenchmark("Start");
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;

  UI ui = UI();
  int index = 0;
  int indexTick = 0;

  cam.setPosition(1, 3, 0);
  cam.setRotation(0, 0);
  memoryBenchmark("Create camera and renderer");
  double dir[] = {-0.766, 0, -0.642};
#ifdef FLYBY
  double shPos[] = {9.5, 3, 15};
  double tf1Pos[] = {10.5, 3.5, 16.7};
  double tf2Pos[] = {7.2, 2.5, 14.6};
  Matrix tf1Position = Matrix(1, 3, tf1Pos);
  Matrix tf2Position = Matrix(1, 3, tf2Pos);
#else
  double shPos[] = {1, 3, 15};
#endif
  Matrix shPosition = Matrix(1, 3, shPos);
  Matrix direction = Matrix(1, 3, dir);
  // TieFighter tf = TieFighter();
  memoryBenchmark("Create data");
  ImperialShuttle sh = ImperialShuttle();
  memoryBenchmark("create shuttle");
#ifdef FLYBY
  TieFighter tf1 = TieFighter();
  TieFighter tf2 = TieFighter();
  memoryBenchmark("Create tie fighters");
#endif

  double rot = PI * 11.0 / 9.0;
  while(!cont.buttonPressed(START)){
    cont.lcdClear();
    renderer.clearBuffer();
    // renderer.addUISprite(Matrix(1, 2), sprite);
    sh.setPosition(shPosition);
    sh.setRotation(rot);
#ifdef FLYBY
    tf1.setPosition(tf1Position);
    tf2.setPosition(tf2Position);
    tf1.setRotation(rot);
    tf2.setRotation(rot);
    // printf("Set all tie fighter positions\n");
    shPosition = shPosition + direction * 0.12;
    tf1Position = tf1Position + direction * 0.12;
    tf2Position = tf2Position + direction * 0.12;
    if(shPosition.get(0, 0) < -5){
      shPosition.set(0, 0, 9.5);
      shPosition.set(0, 2, 15);
    }
    if(tf1Position.get(0, 0) < -5){
      tf1Position.set(0, 0, 10.5);
      tf1Position.set(0, 2, 16.7);
    }
    if(tf2Position.get(0, 0) < -5){
      tf2Position.set(0, 0, 7.2);
      tf2Position.set(0, 2, 14.6);
    }
#else
    rot += 0.05;
#endif
  skybox.render(cam, renderer);
    // printf("Start render\n");
    sh.render(cam, renderer);
    // printf("Mark1\n");
#ifdef FLYBY
    tf1.render(cam, renderer);
    // printf("Mark2\n");
    tf2.render(cam, renderer);
    // printf("Mark3\n");
#endif
    ui.render(index, renderer);
    // printf("Render finished\n");
    if(indexTick++ % 10 == 0)
      index++;

    renderer.render(cont);
    cont.lcdRefresh();
  }
  printf("Test completed\n\n");
  return true;
}

bool SpriteDrawTest(Controller &cont){
  printf("Start Test\n\n");
  Renderer renderer;

  UI ui = UI();
  int index = 0;
  int indexTick = 0;

  double speed = 0;

  int fireTick = 11;

  while(!cont.buttonPressed(START)){
    speed = min(max(speed + (cont.buttonDown(Y) ? 0.05 : 0) + (cont.buttonDown(A) ? -0.05 : 0), 0.0), 1.0);
    int bar = int(5.0 * speed);
    ui.setBars(bar, bar);

    if(cont.buttonDown(R) && fireTick > 11){
      fireTick = 0;
    }
    switch(fireTick){
      case 0: ui.setFire(1, 0); cont.lcdSetBrightness(1); break;
      case 1: cont.lcdSetBrightness(0.5); break;
      case 3: ui.setFire(0, 0); cont.lcdSetBrightness(1); break;
      case 4: cont.lcdSetBrightness(0.5); break;
      case 8: ui.setFire(0, 1); break;
      case 11: ui.setFire(1, 1); break;
    }
    fireTick++;

    ui.setDir(index);

    ui.render(index, renderer);
    if(indexTick++ % 10 == 0)
      index++;
    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
  printf("Test completed\n\n");
  return true;
}

bool SkyboxandLaserTest(Controller &cont){
  printf("Start Test!\n\n");
  Renderer renderer;
  double rotX = 0;
  double rotZ = 0;
  Camera cam;
  cam.init();

  Skybox skybox;

  vector<Laser> lasers;
  vector<Explosion> explosions;

  double l[] = {0.5, -0.1, 0.0};
  double r[] = {-0.5, -0.1, 0.2};
  Matrix left = Matrix(1, 3, l);
  Matrix right = Matrix(1, 3, r);
  double x[] = {0, 0, 5};
  Matrix explosionPos = Matrix(1, 3, x);

  while(!cont.buttonPressed(START)){
    cont.lcdClear();
    renderer.clearBuffer();

    rotZ += pow(cont.joystickCoord().x, 3) * -0.4;
    rotX += pow(cont.joystickCoord().y, 3) * -0.15;

    cam.setPosition(0, 0, 0);
    cam.setRotation(rotX, rotZ);

    skybox.render(cam, renderer);
    if(cont.buttonPressed(R)){
      Laser lLaser = Laser();
      lLaser.setPosition(left);
      lLaser.setVelocity(cam.getFacing(), cam.getUp());

      Laser rLaser = Laser();
      rLaser.setPosition(right);
      rLaser.setVelocity(cam.getFacing() * 3, cam.getUp());
      lasers.push_back(rLaser);
      lasers.push_back(lLaser);

    }

    unsigned int i = 0;
    while(i < lasers.size()){
      // printf("remove?: %d\n", lasers[i].toBeRemoved);
      if(lasers[i].toBeRemoved){
        lasers.erase(lasers.begin() + i);
      }
      else{
        lasers[i].update(0.05);
        lasers[i].render(cam, renderer);
        i++;
      }
    }

    if(cont.buttonPressed(L)){
      Explosion explosion = Explosion();
      explosion.setPosition(explosionPos);
      explosion.setSize(2.5);
      explosions.push_back(explosion);
    }
    unsigned int j = 0;
    while(j < explosions.size()){
      if(explosions[j].toBeRemoved){
        explosions.erase(explosions.begin() + j);
      }
      else{
        explosions[j].update(0.05);
        explosions[j].render(cam, renderer);
        j++;
      }
    }


    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
  printf("Test completed\n\n");
  return true;
}

bool LivesTest(Controller &cont){
  printf("Start Test!\n\n");
  Lives lives = Lives(cont);

  while(!lives.isGameOver()){
    if(cont.buttonPressed(A)){
      printf("Button pressed\n");
      lives.damage(10);
    }
  }

  printf("Test completed\n\n");
  return true;
}

bool TieFighterControlTest(Controller &cont){
  printf("Start Test!\n\n");
  memoryBenchmark("Start");
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;


  cam.setPosition(0, 3, 0);
  cam.setRotation(0, 0);

  double tfPos[] = {0, 0, 3};
  Matrix tfPosition = Matrix(1, 3, tfPos);

  TieFighter tf = TieFighter();
  tf.setPosition(tfPosition);
  tf.setRotation(0);

  while(!cont.buttonPressed(START)){
    cont.lcdClear();
    renderer.clearBuffer();
    skybox.render(cam, renderer);

    double steer = pow(cont.joystickCoord().x, 3);
    double elev = pow(cont.joystickCoord().y, 3);


    if(cont.buttonPressed(B)){
      tf.detectCollision(tf.getPosition());
    }
    tf.update(0.05, steer, elev, cont.buttonPressed(A));

    tf.render(cam, renderer);

    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
  printf("Test completed\n\n");
  return true;
}

bool ImperialShuttleControlTest(Controller &cont){
  printf("Start Test!\n\n");
  memoryBenchmark("Start");
  Renderer renderer;
  Camera cam;
  cam.init();
  Skybox skybox;


  cam.setPosition(0, 1.5, 0);
  cam.setRotation(0, 0);

  double shPos[] = {0, 0, 3};
  Matrix shPosition = Matrix(1, 3, shPos);

  ImperialShuttle sh = ImperialShuttle();
  sh.setPosition(shPosition);
  sh.setRotation(0);

  while(!cont.buttonPressed(START)){
    cont.lcdClear();
    renderer.clearBuffer();
    skybox.render(cam, renderer);

    double steer = pow(cont.joystickCoord().x, 3);


    if(cont.buttonPressed(B)){
      sh.detectCollision(sh.getPosition() + cam.getFacing().cross(cam.getUp()));
    }
    sh.update(0.05, steer);

    sh.render(cam, renderer);

    renderer.render(cont);
    cont.lcdRefresh();
    wait(0.05);
  }
  printf("Test completed\n\n");
  return true;
}

bool XWingTest(Controller &cont){
printf("Start Test!\n\n");
Renderer renderer;
Camera cam;
cam.init();
Skybox skybox;
XWing xwing = XWing(Matrix(1, 3), cont);

double tfPos[] = {0, 0, 3};
TieFighter tf = TieFighter(Matrix(1, 3, tfPos), 0);

while(!cont.buttonPressed(START))
{
  cont.lcdClear();
  renderer.clearBuffer();

  if(cont.buttonPressed(BACK))
    xwing.detectCollision(xwing.getPosition());

  for(unsigned int i = 0; i < xwing.lasers.size(); i++){
    if(tf.detectCollision(xwing.lasers[i].getPosition())){
      xwing.lasers[i].toBeRemoved = true;
    }
  }

  tf.update(0.05, 0, 0, false);


  xwing.update(0.05, cont, cam);

  skybox.render(cam, renderer);
  xwing.render(cam, renderer);
  tf.render(cam, renderer);

  renderer.render(cont);
  cont.lcdRefresh();
  wait(0.05);
}
printf("Test completed\n\n");
return true;
}

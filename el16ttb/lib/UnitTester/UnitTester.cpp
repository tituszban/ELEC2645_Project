using namespace std;
#include <vector>
#include "mbed.h"
#include "UnitTester.h"
#include <Matrix.h>
#include <Camera.h>
#include <math.h>
#include <Renderer.h>
#include <Block.h>
#include <Util.h>
#include <Face.h>
#include <Block.h>

#include <ctime>


bool UnitTester::MatrixCreationTest(){
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

bool UnitTester::MatrixReadWriteTest(){
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

bool UnitTester::MatrixOperationsTest(){
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

bool UnitTester::MatrixErrorTest(){
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

bool UnitTester::CameraValueTest(){
  Camera cam;
  cam.init();
  cam.SetPosition(0, 0, 6);
  double p[] = {1, 1, -1, 1};
  Matrix point = Matrix(1, 4, p);
  Matrix screenPoint = cam.GetScreenPosition(point);
  screenPoint.print_matrix();
  //double v =
  screenPoint = screenPoint / screenPoint.get(0, 2);
  screenPoint.print_matrix();
  return true;
}

bool UnitTester::CameraScaleTest(Controller &cont){
  double posX = 0.5;
  double posZ = 0.5;

  double rotX = 0;
  double rotZ = 0;
  Camera cam;
  cam.init();

  while(1){
    cont.lcdClear();

    rotZ += pow(cont.joystickCoord().x, 3) * -0.4;
    rotX += pow(cont.joystickCoord().y, 3) * -0.15;

    double moveX = (cont.buttonDown(A) ? -1 : 0) + (cont.buttonDown(Y) ? 1 : 0);
    double moveZ = (cont.buttonDown(X) ? -1 : 0) + (cont.buttonDown(B) ? 1 : 0);

    posZ += (moveX * cos(-rotZ) + moveZ * sin(-rotZ)) * 0.3;
    posX += (moveX * sin(-rotZ) + moveZ * cos(-rotZ)) * 0.3;

    cam.SetPosition(posX, 1.6, posZ);
    cam.SetRotation(rotX, rotZ);

    bool doPrint = cont.buttonPressed(BACK);
    for(int i = -10; i <= 10; i++){
      for(int j = -10; j <= 10; j++){
        for(int k = 0; k < 1; k++){
          if(sqrt(pow(i, 2) + pow(j, 2)) < 10){
            double p[] = {(double)i, (double)k, (double)j, 1};
            Matrix point = Matrix(1, 4, p);
            Matrix screenPoint = cam.GetScreenPosition(point);
            // printf("draw point %d,%d,%d\n", i, k, j);
            // printf("Adding point\n");
            //ren.addPoint(screenPoint, 1);
            // prePoint.print_matrix();
            // screenPoint.print_matrix();
            // printf("Point added\n");

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

bool UnitTester::RendererDisplayTest(Controller &cont){
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
  while(1){
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

bool UnitTester::FaceRenderTest(Controller &cont){
  printf("Start Test\n\n");
  Renderer renderer;
  Camera cam;
  cam.init();

  double pos[][3] = {
    {1.5, 1.5, 2},
    {1.5, 2, 2.5},
    {1, 1.5, 2.5},
    {1, 2, 3.5}
  };

  double fac[][3] = {
    {0, 0, -1},
    {0, 1, 0},
    {-1, 0, 0},
    {0, 0, -1}
  };
  for(int i = 0; i < 4; i++){
    Matrix face_pos = Matrix(1, 3, pos[i]);
    Matrix face_fac = Matrix(1, 3, fac[i]);
    Face face = Face(face_pos, face_fac);

    cam.SetPosition(0.5, 2.6, 0);
    cam.SetRotation(0, 0);

    face.render(cam, renderer);
  }
  renderer.render(cont);
  cont.lcdRefresh();
  printf("Test completed\n\n");
  return true;
}

void memoryBenchmark(char* id){
  return;
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
  printf("id: %s\tmemory left: %d char\n", id, (i - 1) * blockSize);
  // printf(id);
  // printf("%s:\tA: %p, A2: %p, B: %p\tA - B: %d\n", id, a, a2, b, (a - b)/1024);
  // delete b;
  // printf("B - A: %d\n", (a - b) / 1024);
}

bool UnitTester::BlockRenderTest(Controller &cont){
  printf("\nStart Test\n");

  memoryBenchmark("Start");
  Renderer renderer;
  memoryBenchmark("Renderer");
  Camera cam;
  cam.init();
  memoryBenchmark("Camera");
  // printf("Camera inited\n");
  vector<vector<int> > textu(1, vector<int>(1, 0));
  Texture empty = {1, 1, textu};
  vector<vector<int> > textuFull(1, vector<int>(1, 1));
  Texture full = {1, 1, textuFull};
  BlockTexture emptyBlock = {full, empty, empty, empty, empty, empty};

  double pos[][3] = {
    {0, 1, 3},
    {1, 1, 3},
    {1, 1, 2},
    {-1, 2, 2},
    {0, 0, 2},
    {-1, 0, 2},
    {-1, 0, 3},
    {0, 1, 1},
    {0, 2, 4},
    {1, 2, 4},
    {-2, 0, 2},
    {-2, 0, 3},
    {-1, 3, 2}
  };
  memoryBenchmark("Textures");
  // Block blocks[10];
  // printf("vector created\n");
  // for(int i = 0; i < 10; i++){
  //   Matrix block_pos = Matrix(1, 3, pos[i]);
  //
  //   Block block = Block(block_pos, BlockFacing(-cam.GetFacing()), emptyBlock);
  //   printf("Block created\n");
  //   blocks[i] = block;
  //
  //   printf("Block pushed\n");
  // }
  // printf("vector filled\n");

  double posX = 0.5;
  double posZ = 0.5;

  double rotX = 0;
  double rotZ = 0;
  while(1){
    cont.lcdClear();
    renderer.clearBuffer();
    printf("Start frame\n");

    // int n = 0;
    // int *a = &n;
    // int *b = new int();
    // printf("A: %p, B: %p\n", a, b);
    // printf("B - A: %d\n", (b - a) / 1024);
    memoryBenchmark("Runtime1");
    memoryBenchmark("Runtime2");

    rotZ += pow(cont.joystickCoord().x, 3) * -0.4;
    rotX += pow(cont.joystickCoord().y, 3) * -0.15;

    double moveX = (cont.buttonDown(A) ? -1 : 0) + (cont.buttonDown(Y) ? 1 : 0);
    double moveZ = (cont.buttonDown(X) ? -1 : 0) + (cont.buttonDown(B) ? 1 : 0);

    posZ += (moveX * cos(rotZ) + moveZ * sin(rotZ)) * 0.3;
    posX += (moveX * sin(-rotZ) + moveZ * cos(rotZ)) * 0.3;

    cam.SetPosition(posX, 2.6, posZ);
    cam.SetRotation(rotX, rotZ);
    // cam.SetPosition(0.5, 2.6, 0);
    // cam.SetRotation(0, 0);
    for(int i = 0; i < 3; i++){
      // printf("Rendering block: %d\n", i);
      Matrix block_pos = Matrix(1, 3, pos[i]);

      Block block = Block(block_pos, BlockFacing(-cam.GetFacing()), emptyBlock);
      //printf("size: %d\n", sizeof(block));
      block.render(cam, renderer);
      // printf("Block rendererd\n");
      // error("Something went wrong\n");
    }

    renderer.render(cont);
    cont.lcdRefresh();
    printf("End frame\n");
    wait(0.1);
  }

  printf("Test completed\n\n");
  return true;
}

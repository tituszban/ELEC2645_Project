#ifndef BLOCK
#define BLOCK

#include <Matrix.h>
#include "mbed.h"
#include <Face.h>
#include <Camera.h>
#include <Renderer.h>

using namespace std;
#include <vector>

#define CORNER_N 8
#define EDGE_N 12

struct BlockTexture{
  Texture top;
  Texture front;
  Texture sideL;
  Texture sideR;
  Texture back;
  Texture bottom;
};

enum Facing{
  No,          // Z+
  We,          // X+
  So,          // Z-
  Ea           // X-
};

class BlockFacing{
public:
  Facing facing;
  BlockFacing();
  BlockFacing(Facing facing);
  BlockFacing(Matrix heading);
  Matrix left();
  Matrix up();
  Matrix forward();
};

class Block{
public:
  Block(Matrix pos, BlockFacing facing, BlockTexture texture);
  Block();
  void render(Camera &cam, Renderer &renderer);

private:
  Matrix position;
  Matrix centrePosition;
  BlockFacing facing;
  BlockTexture texture;

  Face top;
  Face front;
  Face sideL;
  Face sideR;
  Face back;
  Face bottom;
};

#endif

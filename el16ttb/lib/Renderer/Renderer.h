#ifndef RENDERER
#define RENDERER

#define WIDTH 84
#define HEIGHT 48
#define RENDER_DISTANCE 30.0

using namespace std;

#include <Controller.h>
#include "Matrix.h"
#include <vector>
#include <utility>
#include <math.h>
#include "Util.h"


class Renderer{
public:
  Renderer();
  void clearBuffer();
  void render(Controller &cont);
  void addPoint(Matrix point, int value);
  void addPoint(int x, int y, float d, int value);
  void addUIPoint(Matrix point, int value);
  void addUIPoint(int x, int y, int value);
  void addSkyboxPoint(Matrix point, int value);
  void addSkyboxPoint(int x, int y, int value);
  void addLine(Matrix point1, Matrix point2, int value);
  void addPatternLine(Matrix point1, Matrix point2, vector<int> pattern);
  void addUISprite(Matrix point, Texture sprite);
  void addUISprite(int x, int y, Texture sprite);
  void addUISprite(int x, int y, int w, int h, const int* texture);
  void addUISpriteToSubArea(int aX, int aY, int x, int y, int aW, int aH, int w, int h, const int* texture);

private:
  vector< vector< pair<int, float> > > _buffer;
  vector<int> map(vector<int> pattern, int length);
};

#endif

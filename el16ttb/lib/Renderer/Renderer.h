#ifndef RENDERER
#define RENDERER

#define WIDTH 84
#define HEIGHT 48
#define RENDER_DISTANCE 10.0

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
  void addPoint(int x, int y, double d, int value);
  void addUIPoint(Matrix point, int value);
  void addUIPoint(int x, int y, int value);
  void addLine(Matrix point1, Matrix point2, int value);
  void addPatternLine(Matrix point1, Matrix point2, vector<int> pattern);
  void addUISprite(Matrix point, Texture sprite);
  void addUISprite(int x, int y, Texture sprite);

private:
  vector< vector< pair<int, double> > > _buffer;
  vector<int> map(vector<int> pattern, int length);
};

#endif

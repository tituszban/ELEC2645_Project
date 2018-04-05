#ifndef RENDERER
#define RENDERER

#define WIDTH 84
#define HEIGHT 48
#define RENDER_DISTANCE 10.0

#include <Controller.h>
#include <Matrix.h>


using namespace std;
#include <vector>
#include <utility>


class Renderer{
public:
  Renderer();
  void clearBuffer();
  void render(Controller &cont);
  void addPoint(Matrix point, int value);
  void addPoint(int x, int y, double d, int value);
  void addLine(Matrix point1, Matrix point2, int value);
  void addPatternLine(Matrix point1, Matrix point2, vector<int> pattern);

private:
  vector< vector< pair<int, double> > > _buffer;
  vector<double> lerp(double a, double b, int length);
  vector<int> map(vector<int> pattern, int length);
};

#endif RENDERER

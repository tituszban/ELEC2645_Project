#include <Renderer.h>


Renderer::Renderer()
{
  vector< vector< pair<int, double> > > bf(WIDTH, vector< pair<int, double> >(HEIGHT));
  this->_buffer = bf;

  this->clearBuffer();
}

void Renderer::clearBuffer(){
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      this->_buffer[x][y].first = 0;
      this->_buffer[x][y].second = RENDER_DISTANCE;
    }
  }
}

void Renderer::render(Controller &cont){
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      int v = this->_buffer[x][y].first;
      // if(v == 1)
      //   printf("v=1: %d, %d\n", x, y);
      cont.lcdSetPixel(x, y, v);
    }
  }
}

void Renderer::addPoint(Matrix point, int value)
{
  int d = point.get(0, 2);
  int x = round(point.get(0, 0));
  int y = round(point.get(0, 1));
  this->addPoint(x, y, d, value);
}
void Renderer::addPoint(int x, int y, double d, int value)
{
  if(d < 0)
    return;
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return;
  if(d < this->_buffer[x][y].second || (d <= this->_buffer[x][y].second && value == 1)){
    this->_buffer[x][y].first = value;
    this->_buffer[x][y].second = d;
  }
}

void Renderer::addLine(Matrix point1, Matrix point2, int value){
  int distance = ceil(point1.homogDistance(point2));
  // printf("distance found: %d\n", distance);
  if(distance > 100){
    return;
  }

  vector<double> lX = lerp(point1.get(0, 0), point2.get(0, 0), distance);
  vector<double> lY = lerp(point1.get(0, 1), point2.get(0, 1), distance);
  vector<double> lZ = lerp(point1.get(0, 2), point2.get(0, 2), distance);
  // printf("lerped\n");
  for(int i = 0; i < distance; i++){
    this->addPoint(round(lX[i]), round(lY[i]), lZ[i], value);
  }
  // printf("line added\n");
  this->addPoint(round(point1.get(0, 0)), round(point1.get(0, 1)), point1.get(0, 2), value);
  this->addPoint(round(point2.get(0, 0)), round(point2.get(0, 1)), point2.get(0, 2), value);
  // printf("ends added\n");
}

void Renderer::addPatternLine(Matrix point1, Matrix point2, vector<int> pattern){
  int distance = ceil(point1.homogDistance(point2));
  vector<double> lX = lerp(point1.get(0, 0), point2.get(0, 0), distance);
  vector<double> lY = lerp(point1.get(0, 1), point2.get(0, 1), distance);
  vector<double> lZ = lerp(point1.get(0, 2), point2.get(0, 2), distance);

  for(int i = 0; i < distance; i++){
    int scaled_indexer = floor((double) i / (double) distance * pattern.size());
    int value = pattern[scaled_indexer];
    this->addPoint(round(lX[i]), round(lY[i]), lZ[i], value);
  }
  this->addPoint(round(point1.get(0, 0)), round(point1.get(0, 1)), point1.get(0, 2), pattern[0]);
  this->addPoint(round(point2.get(0, 0)), round(point2.get(0, 1)), point2.get(0, 2), pattern[pattern.size() - 1]);
}

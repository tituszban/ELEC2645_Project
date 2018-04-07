#include <Renderer.h>


Renderer::Renderer()
{
//  vector<vector<pair<int, double> buffer[WIDTH][HEIGHT];
//  this->_buffer = buffer;
  vector< vector< pair<int, double> > > bf(WIDTH, vector< pair<int, double> >(HEIGHT));
  this->_buffer = bf;

  this->clearBuffer();
}

void Renderer::clearBuffer(){
  for(int x = 0; x < WIDTH; x++){
    for(int y = 0; y < HEIGHT; y++){
      // printf("clearing: %d, %d\n", x, y);
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
  if(d < this->_buffer[x][y].second){
    this->_buffer[x][y].first = value;
    this->_buffer[x][y].second = d;
  }
}

void Renderer::addLine(Matrix point1, Matrix point2, int value){
  int distance = ceil(point1.homogDistance(point2));
   // sqrt(pow(point1.get(0, 0) - point2.get(0, 0), 2) +
   //                         pow(point1.get(0, 1) - point2.get(0, 1), 2)));
  vector<double> lX = lerp(point1.get(0, 0), point2.get(0, 0), distance);
  vector<double> lY = lerp(point1.get(0, 1), point2.get(0, 1), distance);
  vector<double> lZ = lerp(point1.get(0, 2), point2.get(0, 2), distance);


  for(int i = 0; i < distance; i++){
    this->addPoint(round(lX[i]), round(lY[i]), lZ[i], value);
  }
}

void Renderer::addPatternLine(Matrix point1, Matrix point2, vector<int> pattern){
  int distance = ceil(point1.homogDistance(point2));
   // sqrt(pow(point1.get(0, 0) - point2.get(0, 0), 2) +
   //                         pow(point1.get(0, 1) - point2.get(0, 1), 2)));
  vector<double> lX = lerp(point1.get(0, 0), point2.get(0, 0), distance);
  vector<double> lY = lerp(point1.get(0, 1), point2.get(0, 1), distance);
  vector<double> lZ = lerp(point1.get(0, 2), point2.get(0, 2), distance);

  for(int i = 0; i < distance; i++){
    int scaled_indexer = floor((double) i / (double) distance * pattern.size());
    int value = pattern[scaled_indexer];
    this->addPoint(round(lX[i]), round(lY[i]), lZ[i], value);
  }
}

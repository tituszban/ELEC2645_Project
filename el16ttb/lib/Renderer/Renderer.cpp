#include <Renderer.h>


Renderer::Renderer()
{
  vector< vector< pair<int, float> > > bf(WIDTH, vector< pair<int, float> >(HEIGHT));
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
void Renderer::addPoint(int x, int y, float d, int value)
{
  if(d < 0)
    return;
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return;
  if(value == -1)
    return;
  if(d < this->_buffer[x][y].second || (d <= this->_buffer[x][y].second && value == 1)){
    this->_buffer[x][y].first = value;
    this->_buffer[x][y].second = d;
  }
}

void Renderer::addUIPoint(Matrix point, int value){
  int x = round(point.get(0, 0));
  int y = round(point.get(0, 1));
  this->addUIPoint(x, y, value);
}

void Renderer::addUIPoint(int x, int y, int value){
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return;
  if(value == -1)
    return;
  this->_buffer[x][y].first = value;
  this->_buffer[x][y].second = 0;
}

void Renderer::addSkyboxPoint(Matrix point, int value){
  int x = round(point.get(0, 0));
  int y = round(point.get(0, 1));
  this->addSkyboxPoint(x, y, value);
}

void Renderer::addSkyboxPoint(int x, int y, int value){
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
    return;
  if(value == -1)
    return;
  if(this->_buffer[x][y].second < RENDER_DISTANCE)
    return;
  this->_buffer[x][y].first = value;
  this->_buffer[x][y].second = RENDER_DISTANCE;
}

void Renderer::addLine(Matrix point1, Matrix point2, int value){
  int distance = ceil(point1.homogDistance(point2));
  if(distance > 100){
    return;
  }
  vector<float> lX = lerp(point1.get(0, 0), point2.get(0, 0), distance);
  vector<float> lY = lerp(point1.get(0, 1), point2.get(0, 1), distance);
  vector<float> lZ = lerp(point1.get(0, 2), point2.get(0, 2), distance);
  for(int i = 0; i < distance; i++){
    this->addPoint(round(lX[i]), round(lY[i]), lZ[i], value);
  }
  this->addPoint(round(point1.get(0, 0)), round(point1.get(0, 1)), point1.get(0, 2), value);
  this->addPoint(round(point2.get(0, 0)), round(point2.get(0, 1)), point2.get(0, 2), value);
}

void Renderer::addPatternLine(Matrix point1, Matrix point2, vector<int> pattern){
  int distance = ceil(point1.homogDistance(point2));
  vector<float> lX = lerp(point1.get(0, 0), point2.get(0, 0), distance);
  vector<float> lY = lerp(point1.get(0, 1), point2.get(0, 1), distance);
  vector<float> lZ = lerp(point1.get(0, 2), point2.get(0, 2), distance);

  for(int i = 0; i < distance; i++){
    int scaled_indexer = floor((float) i / (float) distance * pattern.size());
    int value = pattern[scaled_indexer];
    this->addPoint(round(lX[i]), round(lY[i]), lZ[i], value);
  }
  this->addPoint(round(point1.get(0, 0)), round(point1.get(0, 1)), point1.get(0, 2), pattern[0]);
  this->addPoint(round(point2.get(0, 0)), round(point2.get(0, 1)), point2.get(0, 2), pattern[pattern.size() - 1]);
}

void Renderer::addUISprite(Matrix point, Texture sprite){
  int x = round(point.get(0, 0));
  int y = round(point.get(0, 1));
  for(int i = 0; i < sprite.width; i++){
    for(int j = 0; j < sprite.height; j++){
      this->addUIPoint(x + i, y + j, sprite.texture[j][i]);
    }
  }
}

void Renderer::addUISprite(int x, int y, Texture sprite){
  for(int i = 0; i < sprite.width; i++){
    for(int j = 0; j < sprite.height; j++){
      this->addUIPoint(x + i, y + j, sprite.texture[j][i]);
    }
  }
}

void Renderer::addUISprite(int x, int y, int w, int h, const int* texture){
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      // printf("x: %d, y: %d, x+i: %d, y+j: %d, j*h + i: %d, t: %d\n", x, y, x+j, y+h, i*w + j, texture[i * w + j]);
      this->addUIPoint(x + j, y + i, texture[i * w + j]);
    }
  }
}

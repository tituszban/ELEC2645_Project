#include "Block.h"

BlockFacing::BlockFacing(){
  this->facing = No;
}
BlockFacing::BlockFacing(Facing facing){
  this->facing = facing;
}
BlockFacing::BlockFacing(Matrix heading){
  if(abs(heading.get(0, 0)) > abs(heading.get(0, 2))){
    if(heading.get(0, 0) > 0){
      this->facing = We;
    }
    else{
      this->facing = Ea;
    }
  }
  else{
    if(heading.get(0, 2) > 0){
      this->facing = No;
    }
    else{
      this->facing = So;
    }
  }
}
Matrix BlockFacing::left(){
  double temp[3] = {0, 0, 0};
  switch(this->facing){
    case No: temp[0] = 1; break;
    case We: temp[2] = -1; break;
    case So: temp[0] = -1; break;
    case Ea: temp[2] = 1; break;
  }
  return Matrix(1, 3, temp);
}
Matrix BlockFacing::up(){
  double temp[] = {0, 1, 0};
  return Matrix(1, 3, temp);
}
Matrix BlockFacing::forward(){
  double temp[3] = {0, 0, 0};
  switch(this->facing){
    case No: temp[2] = 1; break;
    case We: temp[0] = 1; break;
    case So: temp[2] = -1; break;
    case Ea: temp[0] = -1; break;
  }
  return Matrix(1, 3, temp);
}

Block::Block(Matrix pos, BlockFacing facing, BlockTexture texture){
  this->position = pos;
  double offsetTemp[] = {0.5, 0.5, 0.5};
  this->centrePosition = pos + Matrix(1, 3, offsetTemp);
  this->facing = facing;
  this->texture = texture;

  this->top = Face(this->centrePosition + facing.up() / 2, facing.up());
  this->front = Face(this->centrePosition + facing.forward() / 2, facing.forward());
  this->sideL = Face(this->centrePosition + facing.left() / 2, facing.left());
  this->bottom = Face(this->centrePosition - facing.up() / 2, -facing.up());
  this->back = Face(this->centrePosition - facing.forward() / 2, -facing.forward());
  this->sideR = Face(this->centrePosition - facing.left() / 2, -facing.left());

  this->top.setTexture(texture.top);
  this->front.setTexture(texture.front);
  this->sideL.setTexture(texture.sideL);
  this->bottom.setTexture(texture.bottom);
  this->back.setTexture(texture.back);
  this->sideR.setTexture(texture.sideR);
}
Block::Block(){

}


void Block::render(Camera &cam, Renderer &renderer)
{
  // printf("Starting rendering\n");
  this->top.render(cam, renderer);
  this->front.render(cam, renderer);
  this->sideL.render(cam, renderer);
  this->bottom.render(cam, renderer);
  this->back.render(cam, renderer);
  this->sideR.render(cam, renderer);
  // printf("finished rendering\n");
}

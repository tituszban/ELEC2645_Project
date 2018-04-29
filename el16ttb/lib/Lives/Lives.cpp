#include "Lives.h"

Lives::Lives(){

}

Lives::Lives(Controller &cont){
  this->cont = &cont;
  reset();
}

void Lives::damage(float dam){
  life -= dam;
  setLEDs();
}

bool Lives::isGameOver(){
  return life <= 0;
}

void Lives::reset(){
  life = 100;
  setLEDs();
}

void Lives::setLEDs(){
  for(int i = 1; i < 7; i++){
    cont->led(i, (life - (i - 1) * 16.67) / 16.67);
  }
}

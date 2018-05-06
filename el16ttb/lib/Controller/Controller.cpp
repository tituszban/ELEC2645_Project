#include "Controller.h"
#include "mbed.h"

Controller::Controller():
  _button_A(new InterruptIn(PTB9)),
  _button_B(new InterruptIn(PTD0)),
  _button_X(new InterruptIn(PTC17)),
  _button_Y(new InterruptIn(PTC12)),
  _button_L(new InterruptIn(PTB18)),
  _button_R(new InterruptIn(PTB3)),
  _button_back(new InterruptIn(PTB19)),
  _button_start(new InterruptIn(PTC5)),
  _button_joystick(new InterruptIn(PTC16)),
  lcd(new N5110(PTC9,PTC0,PTC7,PTD2,PTD1,PTC11)),
  pad(new Gamepad())
{
  this->_buttons[A] = 0;
  this->_buttons[B] = 0;
  this->_buttons[X] = 0;
  this->_buttons[Y] = 0;
  this->_buttons[L] = 0;
  this->_buttons[R] = 0;
  this->_buttons[START] = 0;
  this->_buttons[BACK] = 0;
  this->_buttons[JOYSTICK] = 0;
  this->forceMuted = false;
}

void Controller::init()
{
  this->initButtons();
  this->pad->init();
  this->lcd->init();
}

void Controller::initButtons()
{
  _button_A->mode(PullDown);
  _button_B->mode(PullDown);
  _button_X->mode(PullDown);
  _button_Y->mode(PullDown);
  _button_back->mode(PullDown);
  _button_start->mode(PullDown);
  _button_L->mode(PullDown);
  _button_R->mode(PullDown);
  _button_joystick->mode(PullDown);
  // therefore setup rising edge interrupts
  _button_A->rise(callback(this,&Controller::aDown));
  _button_B->rise(callback(this,&Controller::bDown));
  _button_X->rise(callback(this,&Controller::xDown));
  _button_Y->rise(callback(this,&Controller::yDown));
  _button_L->rise(callback(this,&Controller::lDown));
  _button_R->rise(callback(this,&Controller::rDown));
  _button_start->rise(callback(this,&Controller::startDown));
  _button_back->rise(callback(this,&Controller::backDown));
  _button_joystick->rise(callback(this,&Controller::joyDown));

  _button_A->fall(callback(this,&Controller::aUp));
  _button_B->fall(callback(this,&Controller::bUp));
  _button_X->fall(callback(this,&Controller::xUp));
  _button_Y->fall(callback(this,&Controller::yUp));
  _button_L->fall(callback(this,&Controller::lUp));
  _button_R->fall(callback(this,&Controller::rUp));
  _button_start->fall(callback(this,&Controller::startUp));
  _button_back->fall(callback(this,&Controller::backUp));
  _button_joystick->fall(callback(this,&Controller::joyUp));
}

bool Controller::buttonPressed(Button b){
  if(this->_buttons[b] == 2){
    this->_buttons[b] = 3;
    return true;
  }
  return false;
}
bool Controller::buttonReleased(Button b){
  if(this->_buttons[b] == 0)
  {
    this->_buttons[b] = 1;
    return true;
  }
  return false;
}
bool Controller::buttonDown(Button b)
{
  return this->_buttons[b] == 2 || this->_buttons[b] == 3;
}


void Controller::aDown()
{
  this->_buttons[A] = 2;
}
void Controller::bDown()
{
  this->_buttons[B] = 2;
}
void Controller::xDown()
{
  this->_buttons[X] = 2;
}
void Controller::yDown()
{
  this->_buttons[Y] = 2;
}
void Controller::lDown()
{
  this->_buttons[L] = 2;
}
void Controller::rDown()
{
  this->_buttons[R] = 2;
}
void Controller::startDown()
{
  this->_buttons[START] = 2;
}
void Controller::backDown()
{
  this->_buttons[BACK] = 2;
}
void Controller::joyDown()
{
  this->_buttons[JOYSTICK] = 2;
}
void Controller::aUp()
{
  this->_buttons[A] = 0;
}
void Controller::bUp()
{
  this->_buttons[B] = 0;
}
void Controller::xUp()
{
  this->_buttons[X] = 0;
}
void Controller::yUp()
{
  this->_buttons[Y] = 0;
}
void Controller::lUp()
{
  this->_buttons[L] = 0;
}
void Controller::rUp()
{
  this->_buttons[R] = 0;
}
void Controller::startUp()
{
  this->_buttons[START] = 0;
}
void Controller::backUp()
{
  this->_buttons[BACK] = 0;
}
void Controller::joyUp()
{
  this->_buttons[JOYSTICK] = 0;
}

void Controller::ledsOn(){
  this->pad->leds_on();
}
void Controller::ledsOff(){
  this->pad->leds_off();
}
void Controller::leds(float val){
  this->pad->leds(val);
}
void Controller::led(int n, float val){
  this->pad->led(n, val);
}
float Controller::readPot(){
  return this->pad->read_pot();
}
void Controller::tone(float frequency, float duration){
  if(!muted){
    this->pad->tone(frequency, duration);
  }
}
void Controller::toneContinous(float frequency){
  if(!muted){
    this->pad->toneContinous(frequency);
  }
}

float Controller::joystickMag(){
  return this->pad->get_mag();
}
float Controller::joystickAngle(){
  return this->pad->get_angle();
}
Direction Controller::joystickDirection(){
  return this->pad->get_direction();
}
Vector2D Controller::joystickCoord(){
  return this->pad->get_coord();
}
Vector2D Controller::joystickMapCoord(){
  return this->pad->get_mapped_coord();
}
Polar Controller::joystickPolar(){
  return this->pad->get_polar();
}

void Controller::lcdOff(){
  this->lcd->turnOff();
}
void Controller::lcdClear(){
  this->lcd->clear();
}
void Controller::lcdContrast(float contrast){
  this->lcd->setContrast(contrast);
}
void Controller::lcdNormalMode(){
  this->lcd->normalMode();
}
void Controller::lcdInverseMode(){
  this->lcd->inverseMode();
}
void Controller::lcdSetBrightness(float brightness){
  this->lcd->setBrightness(brightness);
}
void Controller::lcdPrintString(char const *str,
                unsigned int const x,
                unsigned int const y){
  this->lcd->printString(str, x, y);
}
void Controller::lcdPrintChar(char const c,
                unsigned int const x,
                unsigned int const y){
  this->lcd->printChar(c, x,y);
}
void Controller::lcdSetPixel(unsigned int const x,
                unsigned int const y,
                bool const state){
  this->lcd->setPixel(x, y, state);
}
int Controller::lcdGetPixel(unsigned int const x, unsigned int y){
  return this->lcd->getPixel(x, y);
}
void Controller::lcdRefresh(){
  this->lcd->refresh();
}
void Controller::lcdPlotArray(float const array[]){
  this->lcd->plotArray(array);
}
void Controller::lcdDrawCircle(unsigned int const x0,
                unsigned int const y0,
                unsigned int const radius,
                FillType const     fill){
  this->lcd->drawCircle(x0, y0, radius, fill);
}
void Controller::lcdDrawLine(unsigned int const x0,
              unsigned int const y0,
              unsigned int const x1,
              unsigned int const y1,
              unsigned int const type){
  this->lcd->drawLine(x0, y0, x1, y1, type);
}
void Controller::lcdDrawRect(unsigned int const x0,
              unsigned int const y0,
              unsigned int const width,
              unsigned int const height,
              FillType const     fill){
  this->lcd->drawRect(x0, y0, width, height, fill);
}
void Controller::lcdDrawSprite(int x0,
                int y0,
                int nrows,
                int ncols,
                int *sprite){
  this->lcd->drawSprite(x0, y0, nrows, ncols, sprite);
}

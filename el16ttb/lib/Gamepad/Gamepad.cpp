#include "Gamepad.h"

#include "mbed.h"

//////////// constructor/destructor ////////////
Gamepad::Gamepad()
    :
    _led1(new PwmOut(PTA1)),
    _led2(new PwmOut(PTA2)),
    _led3(new PwmOut(PTC2)),
    _led4(new PwmOut(PTC3)),
    _led5(new PwmOut(PTC4)),
    _led6(new PwmOut(PTD3)),

    _button_A(new InterruptIn(PTB9)),
    _button_B(new InterruptIn(PTD0)),
    _button_X(new InterruptIn(PTC17)),
    _button_Y(new InterruptIn(PTC12)),
    _button_L(new InterruptIn(PTB18)),
    _button_R(new InterruptIn(PTB3)),
    _button_back(new InterruptIn(PTB19)),
    _button_start(new InterruptIn(PTC5)),
    _button_joystick(new InterruptIn(PTC16)),

    _vert(new AnalogIn(PTB10)),
    _horiz(new AnalogIn(PTB11)),

    _buzzer(new PwmOut(PTC10)),
    _pot(new AnalogIn(PTB2)),

    _timeout(new Timeout()),

    _event_state(0),

    _x0(0),
    _y0(0)
{}

Gamepad::~Gamepad()
{
    delete _led1,_led2,_led3,_led4,_led5,_led6;
    delete _button_A,_button_B,_button_joystick,_vert,_horiz;
    delete _button_X,_button_Y,_button_back,_button_start;
    delete _button_L,_button_R, _buzzer, _pot, _timeout;
}

///////////////// public methods /////////////////

void Gamepad::init()
{
    leds_off();
    init_buttons();

    // read centred values of joystick
    _x0 = _horiz->read();
    _y0 = _vert->read();

    // clear all flags
    _event_state = 0;
}

void Gamepad::leds_off()
{
    leds(0.0);
}

void Gamepad::leds_on()
{
    leds(1.0);
}

void Gamepad::leds(float val) const
{
    if (val < 0.0f) {
        val = 0.0f;
    }
    if (val > 1.0f) {
        val = 1.0f;
    }

    // leds are active-low, so subtract from 1.0
    // 0.0 corresponds to fully-off, 1.0 to fully-on
    val = 1.0f - val;

    _led1->write(val);
    _led2->write(val);
    _led3->write(val);
    _led4->write(val);
    _led5->write(val);
    _led6->write(val);
}

void Gamepad::led(int n,float val) const
{
    // ensure they are within vlaid range
    if (val < 0.0f) {
        val = 0.0f;
    }
    if (val > 1.0f) {
        val = 1.0f;
    }

    switch (n) {

        // check for valid LED number and set value

        case 1:
            _led1->write(1.0f-val);   // active-low so subtract from 1
            break;
        case 2:
            _led2->write(1.0f-val);   // active-low so subtract from 1
            break;
        case 3:
            _led3->write(1.0f-val);   // active-low so subtract from 1
            break;
        case 4:
            _led4->write(1.0f-val);   // active-low so subtract from 1
            break;
        case 5:
            _led5->write(1.0f-val);   // active-low so subtract from 1
            break;
        case 6:
            _led6->write(1.0f-val);   // active-low so subtract from 1
            break;

    }
}

float Gamepad::read_pot() const
{
    return _pot->read();
}

void Gamepad::tone(float frequency, float duration)
{
    _buzzer->period(1.0f/frequency);
    _buzzer->write(0.5);  // 50% duty cycle - square wave
    _timeout->attach(callback(this, &Gamepad::tone_off), duration );
}

void Gamepad::toneContinous(float frequency)
{
  if(frequency > 0){
    _buzzer->period(1.0f/frequency);
    _buzzer->write(0.5);  // 50% duty cycle - square wave
  }
  else{
    tone_off();
  }
}

bool Gamepad::check_event(GamepadEvent const id)
{
    // Check whether event flag is set
    if (_event_state[id]) {
        _event_state.reset(id);  // clear flag
        return true;
    } else {
        return false;
    }
}

// this method gets the magnitude of the joystick movement
float Gamepad::get_mag()
{
    Polar p = get_polar();
    return p.mag;
}

// this method gets the angle of joystick movement (0 to 360, 0 North)
float Gamepad::get_angle()
{
    Polar p = get_polar();
    return p.angle;
}

Direction Gamepad::get_direction()
{
    float angle = get_angle();  // 0 to 360, -1 for centred

    Direction d;
    // partition 360 into segments and check which segment the angle is in
    if (angle < 0.0f) {
        d = CENTRE;   // check for -1.0 angle
    } else if (angle < 22.5f) {  // then keep going in 45 degree increments
        d = N;
    } else if (angle < 67.5f) {
        d = NE;
    } else if (angle < 112.5f) {
        d = E;
    } else if (angle < 157.5f) {
        d = SE;
    } else if (angle < 202.5f) {
        d = S;
    } else if (angle < 247.5f) {
        d = SW;
    } else if (angle < 292.5f) {
        d = W;
    } else if (angle < 337.5f) {
        d = NW;
    } else {
        d = N;
    }

    return d;
}

///////////////////// private methods ////////////////////////

void Gamepad::tone_off()
{
    // called after timeout
    _buzzer->write(0.0);
}

void Gamepad::init_buttons()
{
    // turn on pull-downs as other side of button is connected to 3V3
    // button is 0 when not pressed and 1 when pressed
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
    _button_A->rise(callback(this,&Gamepad::a_isr));
    _button_B->rise(callback(this,&Gamepad::b_isr));
    _button_X->rise(callback(this,&Gamepad::x_isr));
    _button_Y->rise(callback(this,&Gamepad::y_isr));
    _button_L->rise(callback(this,&Gamepad::l_isr));
    _button_R->rise(callback(this,&Gamepad::r_isr));
    _button_start->rise(callback(this,&Gamepad::start_isr));
    _button_back->rise(callback(this,&Gamepad::back_isr));
    _button_joystick->rise(callback(this,&Gamepad::joy_isr));
}

// button interrupts ISRs
// Each of these simply sets the appropriate event bit in the _event_state
// variable
void Gamepad::a_isr()
{
    _event_state.set(A_PRESSED);
}
void Gamepad::b_isr()
{
    _event_state.set(B_PRESSED);
}
void Gamepad::x_isr()
{
    _event_state.set(X_PRESSED);
}
void Gamepad::y_isr()
{
    _event_state.set(Y_PRESSED);
}
void Gamepad::l_isr()
{
    _event_state.set(L_PRESSED);
}
void Gamepad::r_isr()
{
    _event_state.set(R_PRESSED);
}
void Gamepad::back_isr()
{
    _event_state.set(BACK_PRESSED);
}
void Gamepad::start_isr()
{
    _event_state.set(START_PRESSED);
}
void Gamepad::joy_isr()
{
    _event_state.set(JOY_PRESSED);
}

// get raw joystick coordinate in range -1 to 1
// Direction (x,y)
// North     (0,1)
// East      (1,0)
// South     (0,-1)
// West      (-1,0)
Vector2D Gamepad::get_coord()
{
    // read() returns value in range 0.0 to 1.0 so is scaled and centre value
    // substracted to get values in the range -1.0 to 1.0
    float x = 2.0f*( _horiz->read() - _x0 );
    float y = 2.0f*( _vert->read()  - _y0 );

    // Note: the x value here is inverted to ensure the positive x is to the
    // right. This is simply due to how the potentiometer on the joystick
    // I was using was connected up. It could have been corrected in hardware
    // by swapping the power supply pins. Instead it is done in software so may
    // need to be changed depending on your wiring setup

    Vector2D coord = {-x,y};
    return coord;
}

// This maps the raw x,y coord onto a circular grid.
// See:  http://mathproofs.blogspot.co.uk/2005/07/mapping-square-to-circle.html
Vector2D Gamepad::get_mapped_coord()
{
    Vector2D coord = get_coord();

    // do the transformation
    float x = coord.x*sqrt(1.0f-pow(coord.y,2.0f)/2.0f);
    float y = coord.y*sqrt(1.0f-pow(coord.x,2.0f)/2.0f);

    Vector2D mapped_coord = {x,y};
    return mapped_coord;
}

// this function converts the mapped coordinates into polar form
Polar Gamepad::get_polar()
{
    // get the mapped coordinate
    Vector2D coord = get_mapped_coord();

    // at this point, 0 degrees (i.e. x-axis) will be defined to the East.
    // We want 0 degrees to correspond to North and increase clockwise to 359
    // like a compass heading, so we need to swap the axis and invert y
    float x = coord.y;
    float y = coord.x;

    float mag = sqrt(x*x+y*y);  // pythagoras
    float angle = RAD2DEG*atan2(y,x);
    // angle will be in range -180 to 180, so add 360 to negative angles to
    // move to 0 to 360 range
    if (angle < 0.0f) {
        angle+=360.0f;
    }

    // the noise on the ADC causes the values of x and y to fluctuate slightly
    // around the centred values. This causes the random angle values to get
    // calculated when the joystick is centred and untouched. This is also when
    // the magnitude is very small, so we can check for a small magnitude and then
    // set the angle to -1. This will inform us when the angle is invalid and the
    // joystick is centred

    if (mag < TOL) {
        mag = 0.0f;
        angle = -1.0f;
    }

    Polar p = {mag,angle};
    return p;
}

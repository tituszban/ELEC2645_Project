#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <bitset>

// Forward declaration of the classes that we use from the mbed library
// This avoids the need for us to include the huge mbed.h header inside our
// own library API
namespace mbed
{
class AnalogIn;
class InterruptIn;
class PwmOut;
class Timeout;
}

#define TOL 0.1f
#define RAD2DEG 57.2957795131f

/** Enum for direction */
enum Direction {
    CENTRE,  /**< joystick centred */
    N,       /**< pushed North (0)*/
    NE,      /**< pushed North-East (45) */
    E,       /**< pushed East (90) */
    SE,      /**< pushed South-East (135) */
    S,       /**< pushed South (180) */
    SW,      /**< pushed South-West (225) */
    W,       /**< pushed West (270) */
    NW       /**< pushed North-West (315) */
};

/** Vector 2D struct */
struct Vector2D {
    float x; /**< float for x value */
    float y; /**< float for y value */
};

/** Polar coordinate struct */
struct Polar {
    float mag;  /**< float for magnitude */
    float angle; /**< float for angle (in degrees) */
};

enum GamepadEvent {
    A_PRESSED,     ///< Button A has been pressed
    B_PRESSED,     ///< Button B has been pressed
    X_PRESSED,     ///< Button X has been pressed
    Y_PRESSED,     ///< Button Y has been pressed
    L_PRESSED,     ///< Button L has been pressed
    R_PRESSED,     ///< Button R has been pressed
    BACK_PRESSED,  ///< Button "Back" has been pressed
    START_PRESSED, ///< Button "Start" has been pressed
    JOY_PRESSED,   ///< Joystick button has been pressed
    N_EVENTS       ///< A dummy flag that marks the end of the list
};

/** Gamepad Class
 * @brief Library for interfacing with ELEC2645 Gamepad PCB, University of Leeds
 * @author Dr Craig A. Evans
 * @author Dr Alex Valavanis
 */
class Gamepad
{
public:
/** Gamepad events
 * @brief List of events that can be registered on the gamepad
 */


private:
    mbed::PwmOut *_led1;
    mbed::PwmOut *_led2;
    mbed::PwmOut *_led3;
    mbed::PwmOut *_led4;
    mbed::PwmOut *_led5;
    mbed::PwmOut *_led6;

    mbed::InterruptIn *_button_A;
    mbed::InterruptIn *_button_B;
    mbed::InterruptIn *_button_X;
    mbed::InterruptIn *_button_Y;
    mbed::InterruptIn *_button_L;
    mbed::InterruptIn *_button_R;
    mbed::InterruptIn *_button_back;
    mbed::InterruptIn *_button_start;
    mbed::InterruptIn *_button_joystick;

    mbed::AnalogIn *_vert;
    mbed::AnalogIn *_horiz;

    mbed::PwmOut   *_buzzer;
    mbed::AnalogIn *_pot;

    mbed::Timeout *_timeout;

    std::bitset<N_EVENTS> _event_state; ///< A binary list of buttons that has been pressed

    // centred x,y values
    float _x0;
    float _y0;

public:
    /** Constructor */
    Gamepad();

    /** Destructor */
    ~Gamepad();

    /** Initialise all peripherals and configure interrupts */
    void init();

    /** Turn all LEDs on */
    void leds_on();

    /** Turn all LEDs off */
    void leds_off();

    /** Set all LEDs to duty-cycle
    *@param value in range 0.0 to 1.0
    */
    void leds(float val) const;

    /** Set LED to duty-cycle
    *@param led number (0 to 5)
    *@param value in range 0.0 to 1.0
    */
    void led(int n,float val) const;

    /** Read potentiometer
    *@returns potentiometer value in range 0.0 to 1.0
    */
    float read_pot() const;

    /** Play tone on piezo
    * @param frequency in Hz
    * @param duration of tone in seconds
    */
    void tone(float frequency, float duration);

    /** Play tone on piezo continously
    * @param frequency in Hz
    */
    void toneContinous(float frequency);

    /**
     * @brief Check whether an event flag has been set and clear it
     * @param id[in] The ID of the event to test
     * @return true if the event occurred
     */
    bool check_event(GamepadEvent const id);

    /**
     * @brief   Get the raw binary event state
     * @return  The event state as a binary code
     * @details The check_event() function is likely to be more useful than
     *          this, for testing whether a given event has occurred. It can be
     *          useful for debugging via the terminal, however, for example:
     *          @code
     *          std::cout << gamepad.get_raw_event_state() << std::endl;
     *          @endcode
     */
    inline std::bitset<N_EVENTS> get_raw_event_state() const {
        return _event_state;
    }

    /** Get magnitude of joystick movement
    * @returns value in range 0.0 to 1.0
    */
    float get_mag();

    /** Get angle of joystick movement
    * @returns value in range 0.0 to 359.9. 0.0 corresponds to N, 180.0 to S. -1.0 is central
    */
    float get_angle();

    /** Gets joystick direction
    * @returns an enum: CENTRE, N, NE, E, SE, S, SW, W, NW,
    */
    Direction get_direction();    // N,NE,E,SE etc.

    /** Gets raw cartesian co-ordinates of joystick
    * @returns a struct with x,y members, each in the range 0.0 to 1.0
    */
    Vector2D get_coord();         // cartesian co-ordinates x,y

    /** Gets cartesian coordinates mapped to circular grid
    * @returns a struct with x,y members, each in the range 0.0 to 1.0
    */
    Vector2D get_mapped_coord();  // x,y mapped to circle

    /** Gets polar coordinates of the joystick
    * @returns a struct contains mag and angle
    */
    Polar get_polar();            // mag and angle in struct form

private:
    void init_buttons();
    void tone_off();

    void a_isr();
    void b_isr();
    void x_isr();
    void y_isr();
    void l_isr();
    void r_isr();
    void back_isr();
    void start_isr();
    void joy_isr();
};

#endif

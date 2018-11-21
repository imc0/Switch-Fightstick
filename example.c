/* Example applet to demonstrate the use of Switch-Fightstick as a
   Joystick library.
   This applet will press A and B alternately once per second,
   holding each button for 0.2 seconds.  
   While a button is pressed, the LED on the Teensy will light.
*/

#include <avr/io.h>    /* needed for the I/O pins */
#include <Joystick.h>  /* needed to use the Joystick code */

/* Teensy++ 2.0 has the LED on pin D6.  The following macros help us
   operate the LED by flipping this pin. */
#define BITLED  (1<<6)
#define LEDON   (PORTD |= BITLED)
#define LEDOFF  (PORTD &= ~BITLED)
/* This macro sets the pinout direction for the LED to output */
#define LEDPREP (DDRD |= BITLED)

/* These constants control the counter which decides whether to press
   a button on the joystick.  Experiment has shown that that the joystick
   is polled 125 times per second, so a count of 125 means one second
   and count of 25 means 0.2 seconds. */
#define PRESS_INTERVAL 125
#define PRESS_TIME      25

/* This will be our handling function */
void makeInputs(USB_JoystickReport_Input_t* const ReportData);

/* The main entrypoint for this app performs setup and then calls the
   Joystick function (which never returns).  The Joystick function
   takes our handling function as a parameter. */
int main(void) {
    LEDOFF;
    LEDPREP;
    Joystick(makeInputs);
    /*NOTREACHED*/
}

/* Below is the handling function.  This is called every time the USB
   interface asks what the status of the joystick is.  The handling
   function is supplied with a JoystickReport structure which has
   already been cleared to "no input", and it should fill in any buttons
   that it wants to be pressed.

   The format of the joystick structure can be found in Joystick.h.
   For any button which is pressed, we will set the corresponding bit
   in .Button to true.  These bits are defined in JoystickButtons_t
   in Joystick.h.  In addition we can set the HAT switch to one of
   the directional values defined in Joystick.h and we can set the
   analogue sticks (LX,LY) and (RX,RY) to any value from 0 to 255
   indicating how far the stick has been moved in the X or Y direction.
   For convenience, the constants STICK_MIN and STICK_MAX are defined
   to be the minimum and maximum stick values, and STICK_CENTER is
   the value that represents no movement.
*/

/* But first a couple of counters.  These count the number of times
   the handler has been called. */
static int ctr_lo = -1;
static int ctr_hi = 0;

void makeInputs(USB_JoystickReport_Input_t* const ReportData) {
    /* Count the number of times this has been called.
       ctr_lo is the count modulo PRESS_INTERVAL and so represents
                 the time within the current press
       ctr_hi is the count div PRESS_INTERVAL and so represents
                 the number of presses so far. */
    if (++ctr_lo == PRESS_INTERVAL) {
        ctr_lo = 0;
        ctr_hi++;
    }
    if (ctr_lo < PRESS_TIME) {
        /* The button will be pressed and LED lit for PRESS_TIME counts. */
        /* The button to be pressed is A when count is even and B when odd. */
        ReportData->Button |= (ctr_hi&1) ? SWITCH_B : SWITCH_A;
        LEDON;
    } else {
        /* otherwise don't press anything and turn the LED off. */
        LEDOFF;
    }
}

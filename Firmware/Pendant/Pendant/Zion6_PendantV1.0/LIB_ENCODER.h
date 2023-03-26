/* Encoder Library - SpeedTest - for measuring maximum Encoder speed
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */


// This SpeedTest example provides a simple way to verify how much
// CPU time Encoder is consuming.  Connect a DC voltmeter to the
// output pin and measure the voltage while the encoder is stopped
// or running at a very slow speed.  Even though the pin is rapidly
// pulsing, a DC voltmeter will show the average voltage.  Due to
// software timing, it will read a number much less than a steady
// logic high, but this number will give you a baseline reading
// for output with minimal interrupt overhead.  Then increase the
// encoder speed.  The voltage will decrease as the processor spends
// more time in Encoder's interrupt routines counting the pulses
// and less time pulsing the output pin.  When the voltage is
// close to zero and will not decrease any farther, you have reached
// the absolute speed limit.  Or, if using a mechanical system where
// you reach a speed limit imposed by your motors or other hardware,
// the amount this voltage has decreased, compared to the baseline,
// should give you a good approximation of the portion of available
// CPU time Encoder is consuming at your maximum speed.

// Encoder requires low latency interrupt response.  Available CPU
// time does NOT necessarily prove or guarantee correct performance.
// If another library, like NewSoftSerial, is disabling interrupts
// for lengthy periods of time, Encoder can be prevented from
// properly counting the intput signals while interrupt are disabled.


// This optional setting causes Encoder to use more optimized code,
// but the downside is a conflict if any other part of your sketch
// or any other library you're using requires attachInterrupt().
// It must be defined before Encoder.h is included.
//#define ENCODER_OPTIMIZE_INTERRUPTS
#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>

void encoderInit();
void loopencoder();

Encoder myEnc(A8, A9);
boolean Encoder_SW,oldEncoder_SW;
long EncoderPosition ,oldEncoderPosition;

#define encoderPinSW 16





void encoderInit(){
  pinMode(encoderPinSW,INPUT_PULLUP);
  //pinMode(16,INPUT_PULLUP);
  EncoderPosition=0;
  oldEncoderPosition=1;
  Encoder_SW=true;
  oldEncoder_SW=true;
}


void loopencoder() {
  boolean enc=digitalRead(encoderPinSW);
  if (enc!=Encoder_SW){
    Encoder_SW=enc;
  }  
  long newPosition = myEnc.read();
  if (newPosition != EncoderPosition) {
    EncoderPosition = newPosition;
    Serial.println(EncoderPosition);
  }
}

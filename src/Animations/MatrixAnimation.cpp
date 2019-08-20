#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/MatrixAnimation.h"

#define qsubd(x, b)  ((x>b)?b:0)                              // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)

namespace Catharsis
{

MatrixAnimation::MatrixAnimation() {}

void MatrixAnimation::setup() {}

inline void matrix_ray(uint8_t colorIndex, Context *context, CRGBPalette16 curPalette) {                                                 // Send a PWM'd sinewave instead of a random happening of LED's down the strand.

  static uint8_t thisdir = 0;                                                         // We could change the direction if we want to. Static means to assign that value only once.
  static int thisphase = 0;                                                           // Phase change value gets calculated. Static means to assign that value only once.
  uint8_t thiscutoff;                                                                 // You can change the cutoff value to display this wave. Lower value = longer wave.

  thisphase += beatsin8(1,20, 50);                                                    // You can change direction and speed individually.
  thiscutoff = beatsin8(50,164,248);                                                  // This variable is used for the PWM of the lighting with the qsubd command below.
  
  int thisbright = qsubd(cubicwave8(thisphase), thiscutoff);                          // It's PWM time. qsubd sets a minimum value called thiscutoff. If < thiscutoff, then thisbright = 0. Otherwise, thisbright = thiscutoff.
 
  if (thisdir == 0) {                                                                 // Depending on the direction, we'll put that brightness in one end of the array. Andrew Tuline wrote this.
    context->leds[0] = ColorFromPalette(curPalette, colorIndex, thisbright, LINEARBLEND); 
    memmove(context->leds+1, context->leds, (NUM_LEDS-1)*3);                                            // Oh look, the FastLED method of copying LED values up/down the strand.
  } else {
    context->leds[NUM_LEDS-1] = ColorFromPalette( curPalette, colorIndex, thisbright, LINEARBLEND);
    memmove(context->leds, context->leds+1, (NUM_LEDS-1)*3);    
  }

} // matrix_ray()

void MatrixAnimation::loop(Context *context, CRGBPalette16 curPalette)
{

  EVERY_N_MILLIS_I(thisTimer,100) {                           // This only sets the Initial timer delay. To change this value, you need to use thisTimer.setPeriod(); You could also call it thatTimer and so on.
        uint8_t timeval = beatsin8(10,20,50);                     // Create/modify a variable based on the beastsin8() function.
        thisTimer.setPeriod(timeval);                             // Use that as our update timer value.

        matrix_ray(millis()>>4, context, curPalette);                                  // This is the main function that's called. We could have not passed the millis()>>4, but it's a quick example of passing an argument.
    }
}

} // namespace Catharsis
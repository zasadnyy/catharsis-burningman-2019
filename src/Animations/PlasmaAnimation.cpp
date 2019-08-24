#include <Arduino.h>
#include <FastLED.h>

#include "Animations/PlasmaAnimation.h"

#define qsubd(x, b)  ((x>b)?b:0)                              // Digital unsigned subtraction macro. if result <0, then => 0. Otherwise, take on fixed value.
#define qsuba(x, b)  ((x>b)?x-b:0)

namespace Catharsis
{
PlasmaAnimation::PlasmaAnimation()
{
}

void PlasmaAnimation::setup()
{
}

inline void plasma(Context *context, CRGBPalette16 currentPalette) {                                                 // This is the heart of this program. Sure is short. . . and fast.

  int thisPhase = beatsin8(6,-64,64);                           // Setting phase change for a couple of waves.
  int thatPhase = beatsin8(7,-64,64);

  for (int k=0; k<NUM_LEDS; k++) {                              // For each of the LED's in the strand, set a brightness based on a wave as follows:

    int colorIndex = cubicwave8((k*23)+thisPhase)/2 + cos8((k*15)+thatPhase)/2;           // Create a wave and add a phase change and add another wave with its own phase change.. Hey, you can even change the frequencies if you wish.
    int thisBright = qsuba(colorIndex, beatsin8(7,0,96));                                 // qsub gives it a bit of 'black' dead space by setting sets a minimum value. If colorIndex < current value of beatsin8(), then bright = 0. Otherwise, bright = colorIndex..

    context->leds[k] = ColorFromPalette(currentPalette, colorIndex, thisBright, LINEARBLEND);  // Let's now add the foreground colour.
  }

} // plasma()

void PlasmaAnimation::loop(Context *context, CRGBPalette16 curPalette)
{
    EVERY_N_MILLISECONDS(100) {                                  // FastLED based non-blocking delay to update/display the sequence.
        plasma(context, curPalette);
    }
}
} // namespace Catharsis
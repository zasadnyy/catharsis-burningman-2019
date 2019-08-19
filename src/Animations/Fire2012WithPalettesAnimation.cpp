#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/Fire2012WithPalettesAnimation.h"

namespace Catharsis
{

Fire2012WithPalettesAnimation::Fire2012WithPalettesAnimation() {}

void Fire2012WithPalettesAnimation::setup() {}

void Fire2012WithPalettesAnimation::loop(Context *context, CRGBPalette16 curPalette)
{
    EVERY_N_MILLISECONDS(100) {
        Fire2012WithPalette(context, curPalette);                                    // run simulation frame, using palette colors
    }
}

uint8_t cooling = 100;                                        // Less cooling = taller flames.  More cooling = shorter flames. Default 55, suggested range 20-100.
uint8_t sparking = 120;                                        // Higher chance = more roaring fire.  Lower chance = more flickery fire. Default 120, suggested range 50-200.


void Fire2012WithPalettesAnimation::Fire2012WithPalette(Context *context, CRGBPalette16 curPalette) {
  static byte heat[NUM_LEDS];                                 // Array of temperature readings at each simulation cell

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < sparking ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      context->leds[j] = ColorFromPalette(curPalette, colorindex);
    }
} // Fire2012WithPalette()

} // namespace Catharsis
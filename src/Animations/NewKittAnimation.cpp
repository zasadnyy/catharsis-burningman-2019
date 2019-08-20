#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Utils/LedUtils.h"
#include "Animations/NewKittAnimation.h"


namespace Catharsis
{


NewKittAnimation::NewKittAnimation() {}

void NewKittAnimation::setup() {
}

// uint8_t gHue = 0;


void NewKittAnimation::loop(Context *context, CRGBPalette16 currentPalette)
{
    // EVERY_N_MILLISECONDS( 20 ) { gHue++; }

    // uint8_t BeatsPerMinute = 62;
    // uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
    // for( int i = 0; i < NUM_LEDS; i++) { //9948
    //     context->leds[i] = ColorFromPalette(curPalette, gHue+(i*2), beat-gHue+(i*10));
    // }
  
    uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
    uint8_t beatB = beatsin8(13, 0, 255);
    fill_rainbow(context->leds, NUM_LEDS, (beatA+beatB)/2, 8);
}

} // namespace Catharsis
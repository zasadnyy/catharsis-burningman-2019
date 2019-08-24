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

uint8_t gHue = 0;


void NewKittAnimation::loop(Context *context, CRGBPalette16 currentPalette)
{
    EVERY_N_MILLISECONDS( 20 ) { gHue++; }

    uint8_t BeatsPerMinute = 10;
    uint8_t beat = beatsin8( BeatsPerMinute, 0, 255);
    for( int i = 0; i < NUM_LEDS; i++) { //9948
        context->leds[i] = ColorFromPalette(currentPalette, gHue+(i*2), beat-gHue+(i*10));
    }

}

} // namespace Catharsis
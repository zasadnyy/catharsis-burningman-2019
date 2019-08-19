#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/BeatWaveAnimation.h"

namespace Catharsis
{

BeatWaveAnimation::BeatWaveAnimation() {}

void BeatWaveAnimation::setup() {}

void BeatWaveAnimation::loop(Context *context, CRGBPalette16 curPalette)
{
    uint8_t wave1 = beatsin8(9, 0, 255);                        // That's the same as beatsin8(9);
    uint8_t wave2 = beatsin8(8, 0, 255);
    uint8_t wave3 = beatsin8(7, 0, 255);
    uint8_t wave4 = beatsin8(6, 0, 255);

    for (int i=0; i<NUM_LEDS; i++) {
        context->leds[i] = ColorFromPalette(curPalette, i+wave1+wave2+wave3+wave4, 255, LINEARBLEND); 
    }                            // run simulation frame, using palette colors
}

} // namespace Catharsis
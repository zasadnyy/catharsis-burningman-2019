#include <Arduino.h>
#include <FastLED.h>
#include "Animations/Animation.h"
#include "Utils/LedUtils.h"

namespace Catharsis
{
Animation::Animation() {}

void Animation::setup() {}

void Animation::loop(Context *context, CRGBPalette16 curPalette)
{
    fillLedsWithColor(context, CRGB::DeepPink);

    static uint32_t loopCount = 0;
    
    // Set strip number
    for (int strip = 0; strip < NUM_STRIPS; strip++)
    {
        for (int led = 0; led <= NUM_LEDS_PER_STRIP; led++)
        {
            bool isBlack = (led / (strip + 1) % 2) == 0; 
            if (isBlack) {
                int hueIJ = (255 / NUM_LEDS_PER_STRIP * strip + led + loopCount) % 255;
                context->leds[(strip * NUM_LEDS_PER_STRIP) + led] = CHSV(200, 230, hueIJ);
            }
        }
    }

    loopCount++;
}
} // namespace Catharsis
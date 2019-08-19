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

    // Set one pixel to black
    static uint32_t loopCount = 0;
    uint8_t ledToBlack = loopCount % (NUM_LEDS_PER_STRIP * NUM_STRIPS);
    context->leds[ledToBlack] = CRGB::Black;
    loopCount++;

    // Set strip number
    for (int strip = 0; strip < NUM_STRIPS; strip++)
    {
        for (int led = 0; led <= strip; led++)
        {
            context->leds[(strip * NUM_LEDS_PER_STRIP) + led] = CRGB::White;
        }
    }
}
} // namespace Catharsis
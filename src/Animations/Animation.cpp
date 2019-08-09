#include <Arduino.h>
#include <FastLED.h>
#include "Animations/Animation.h"

namespace Catharsis
{
Animation::Animation()
{
}

void Animation::setup() {}

void Animation::loop(Context *context) {
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            context->leds[(i * NUM_LEDS_PER_STRIP) + j] = CRGB::White;
        }
    }
}
} // namespace Catharsis
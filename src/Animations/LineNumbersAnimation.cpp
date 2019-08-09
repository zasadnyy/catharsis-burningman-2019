#include <FastLED.h>
#include "Config.h"
#include "Animations/LineNumbersAnimation.h"

namespace Catharsis
{

LineNumbersAnimation::LineNumbersAnimation() {}

void LineNumbersAnimation::loop(Context *context)
{
    // Set the first n leds on each strip to show which strip it is
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            context->leds[(i * NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
        }
    }
}

} // namespace Catharsis

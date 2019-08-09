#include <FastLED.h>
#include "Config.h"
#include "Animations/RainbowAnimation.h"

namespace Catharsis
{

static uint8_t hue = 0;

RainbowAnimation::RainbowAnimation() {}

void RainbowAnimation::loop(Context *context)
{
    for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    {
        for (int i = 0; i < NUM_STRIPS; i++)
        {
            int hueIJ = (255 / NUM_LEDS_PER_STRIP * i + j + hue) % 255;
            context->leds[i * NUM_LEDS_PER_STRIP + j] = CHSV(hueIJ, 255, 255);
        }
    }
    hue++;
}

} // namespace Catharsis

#include <FastLED.h>
#include "Config.h"
#include "Animations/RainbowAnimation.h"

namespace Catharsis
{

static uint8_t hue = 0;

RainbowAnimation::RainbowAnimation() {}

void RainbowAnimation::loop(Context *context, CRGBPalette16 currentPalette)
{
    // for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
    // {
    //     for (int i = 0; i < NUM_STRIPS; i++)
    //     {
    //         int hueIJ = (255 / NUM_LEDS_PER_STRIP * i + j + hue) % 255;
    //         context->leds[i * NUM_LEDS_PER_STRIP + j] = CHSV(hueIJ, 255, 255);
    //     }
    // }
    // hue++;

    uint8_t beatA = beatsin8(17, 0, 255);                        // Starting hue
    uint8_t beatB = beatsin8(13, 0, 255);
    fill_rainbow(context->leds, NUM_LEDS, (beatA+beatB)/2, 8);
}

} // namespace Catharsis

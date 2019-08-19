#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/PalletCrossfadeAnimation.h"

namespace Catharsis
{
PalletCrossfadeAnimation::PalletCrossfadeAnimation()
{
}

void PalletCrossfadeAnimation::setup()
{
}

// void PalletCrossfadeAnimation::loop(Context *context)
// {
//     EVERY_N_MILLISECONDS(20) {
//         static uint8_t startIndex = 0;
//         startIndex += 1;                                 // motion speed
//         FillLEDsFromPaletteColors(startIndex, context, RainbowColors_p);
//     }

// }

void PalletCrossfadeAnimation::loop(Context *context, CRGBPalette16 curPalette)
{
    EVERY_N_MILLISECONDS(20) {
        static uint8_t startIndex = 0;
        startIndex += 1;                                 // motion speed
        FillLEDsFromPaletteColors(startIndex, context, curPalette);
    }

}

void PalletCrossfadeAnimation::FillLEDsFromPaletteColors(uint8_t colorIndex, Context *context, CRGBPalette16 curPalette) {
  for(int i = 0; i < NUM_LEDS; i++) {
    context->leds[i] = ColorFromPalette(curPalette, colorIndex + sin8(i*16), 255);
    colorIndex += 3;
  }

} // FillLEDsFromPaletteColors()
  

} // namespace Catharsis
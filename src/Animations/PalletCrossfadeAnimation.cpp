#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/PalletCrossfadeAnimation.h"

namespace Catharsis
{
PalletCrossfadeAnimation::PalletCrossfadeAnimation()
{
}


CRGBPalette16 currentPaletteTemp(CRGB::Black);
CRGBPalette16 targetPalette(PartyColors_p );
TBlendType    currentBlending;
uint8_t thisdelay = 20;


void PalletCrossfadeAnimation::setup()
{
    currentBlending = LINEARBLEND;
}

void PalletCrossfadeAnimation::loop(Context *context)
{
    //  ChangePalettePeriodically();
 
  // nblendPaletteTowardPalette() will crossfade current palette slowly toward the target palette.
  //
  // Each time that nblendPaletteTowardPalette is called, small changes
  // are made to currentPaletteTemp to bring it closer to matching targetPalette.
  // You can control how many changes are made in each call:
  //   - the default of 24 is a good balance
  //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  //   - "0" means do not change the currentPaletteTemp at all; freeze

    // EVERY_N_MILLISECONDS(100) {
    //     uint8_t maxChanges = 24; 
    //     nblendPaletteTowardPalette(currentPaletteTemp, targetPalette, maxChanges);
    // }

    EVERY_N_MILLISECONDS(thisdelay) {
        static uint8_t startIndex = 0;
        startIndex += 1;                                 // motion speed
        FillLEDsFromPaletteColors(startIndex, context);
    }

}

void PalletCrossfadeAnimation::ChangePalettePeriodically() {
  
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  
  if(lastSecond != secondHand) {
    lastSecond = secondHand;
    CRGB p = CHSV(HUE_PURPLE, 255, 255);
    CRGB g = CHSV(HUE_GREEN, 255, 255);
    CRGB b = CRGB::Black;
    CRGB w = CRGB::White;
    if(secondHand ==  0)  { targetPalette = RainbowColors_p; }
    if(secondHand == 10)  { targetPalette = CRGBPalette16(g,g,b,b, p,p,b,b, g,g,b,b, p,p,b,b); }
    if(secondHand == 20)  { targetPalette = CRGBPalette16(b,b,b,w, b,b,b,w, b,b,b,w, b,b,b,w); }
    if(secondHand == 30)  { targetPalette = LavaColors_p; }
    if(secondHand == 40)  { targetPalette = CloudColors_p; }
    if(secondHand == 50)  { targetPalette = PartyColors_p; }
  }

}

void PalletCrossfadeAnimation::FillLEDsFromPaletteColors(uint8_t colorIndex, Context *context) {
  int16_t NUM_LEDS = NUM_STRIPS * NUM_LEDS_PER_STRIP;

  for(int i = 0; i < NUM_LEDS; i++) {
    context->leds[i] = ColorFromPalette(context->currentPalette, colorIndex + sin8(i*16), 255);
    colorIndex += 3;
  }

} // FillLEDsFromPaletteColors()
  

} // namespace Catharsis
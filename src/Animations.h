#include <FastLED.h>

#ifndef ANIMATIONS_H

TBlendType    currentBlending = LINEARBLEND;

CRGB* beatwave(CRGBPalette16 currentPalette) {
  static CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];
  
  uint8_t wave1 = beatsin8(9, 0, 255);                        // That's the same as beatsin8(9);
  uint8_t wave2 = beatsin8(8, 0, 255);
  uint8_t wave3 = beatsin8(7, 0, 255);
  uint8_t wave4 = beatsin8(6, 0, 255);

  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, i+wave1+wave2+wave3+wave4, 255, currentBlending); 
  }
  return leds;
}

CRGB* palletCrossfade(CRGBPalette16 currentPalette) {
  static CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

  int colorIndex = 1;
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i*16), 255);
    colorIndex += 3;
  }
  return leds;
}
  


#endif
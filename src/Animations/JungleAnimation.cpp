#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/JungleAnimation.h"

namespace Catharsis
{

static int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
static int brightness = 0; 

JungleAnimation::JungleAnimation() {}

void JungleAnimation::setup() {}

// Routine specific variables
uint8_t    numdots =   16;                                     // Number of dots in use.
uint8_t   thisfade =   1;                                     // How long should the trails be. Very low value = longer trails.
uint8_t   thisdiff =  16;                                     // Incremental change in hue between each dot.
uint8_t    thishue =   0;                                     // Starting hue.
uint8_t     curhue =   0;                                     // The current hue
uint8_t    thissat = 255;                                     // Saturation of the colour.
uint8_t thisbright = 255;                                     // How bright should the LED/display be.
uint8_t   thisbeat =   2;                                     // Higher = faster movement.


inline void juggle_pal(Context *context, CRGBPalette16 curPalette) {                                           // Several colored dots, weaving in and out of sync with each other
  
  curhue = thishue;                                           // Reset the hue values.
  fadeToBlackBy(context->leds, NUM_LEDS, thisfade);
  
  for( int i = 0; i < numdots; i++) {
    context->leds[beatsin16(thisbeat+i+numdots,0,NUM_LEDS)] += ColorFromPalette(curPalette, curhue , thisbright, LINEARBLEND);    // Munge the values and pick a colour from the palette
    curhue += thisdiff;
  }
  
} // juggle_pal()


inline void ChangeMe() {                                             // A time (rather than loop) based demo sequencer. This gives us full control over the length of each sequence.
  
  uint8_t secondHand = (millis() / 1000) % 30;                // IMPORTANT!!! Change '30' to a different value to change duration of the loop.
  static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
  
  if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch(secondHand) {
      case  0: numdots = 1; thisbeat = 20; thisdiff = 16; thisfade = 2; thishue = 0; break;                  // You can change values here, one at a time , or altogether.
      case 10: numdots = 4; thisbeat = 10; thisdiff = 16; thisfade = 8; thishue = 128; break;
      case 20: numdots = 8; thisbeat =  3; thisdiff =  0; thisfade = 8; thishue=random8(); break;           // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 30: break;
    }
  }
  
} // ChangeMe()
void JungleAnimation::loop(Context *context, CRGBPalette16 curPalette)
{

   ChangeMe();
  juggle_pal(context, curPalette);
}

} // namespace Catharsis
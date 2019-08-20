#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
#include "Animations/FadePulseGlowAnimation.h"

namespace Catharsis
{

int fadeAmount = 5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0; 

FadePulseGlowAnimation::FadePulseGlowAnimation() {}

void FadePulseGlowAnimation::setup() {}

inline void fadePulse(Context *context, CRGBPalette16 curPalette) {
    for(int i = 0; i < NUM_LEDS; i++ )
    {
        context->leds[i] = CRGB::Red;  // Set Color HERE!!!
        context->leds[i].fadeLightBy(brightness);
    }

    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade: 
    if(brightness == 0 || brightness == 255)
    {
        fadeAmount = -fadeAmount ; 
    }    
}

void FadePulseGlowAnimation::loop(Context *context, CRGBPalette16 curPalette)
{
    EVERY_N_MILLISECONDS(50) {                                  // FastLED based non-blocking delay to update/display the sequence.
        fadePulse(context, curPalette);
    }

    //  fillLedsWithColor(context, CRGB::Orange);
    // float breath = (exp(sin(millis()/2000.0*PI)) - 0.36787944)*108.0;
    // FastLED.setBrightness(breath);
}

} // namespace Catharsis
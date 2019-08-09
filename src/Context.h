#ifndef CONTEXT_H
#define CONTEXT_H

#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"

namespace Catharsis
{

struct Context
{
    u_int8_t brightness;
    u_int8_t animationsCount;
    u_int8_t currentAnimation;
    CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

    // String toString() {
    //     String toString = "Context: \n";
    //     toString.append("  Brightness: ").append(brightness);
    // }
};

}

#endif /* CONTEXT_H */

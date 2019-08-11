#ifndef CONTEXT_H
#define CONTEXT_H

#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"

namespace Catharsis
{

#define MENU_NONE 0
#define MENU_ANIMATION 1
#define MENU_BRIGHTNESS 2
#define MENU_FPS 3

struct Context
{
    u_int8_t fps;
    u_int8_t brightness;
    u_int8_t currentAnimation;
    u_int8_t animationsCount;
    u_int8_t currentMenu;
    u_int8_t menusCount;
    
    CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

};

}

#endif /* CONTEXT_H */

#ifndef CONTEXT_H
#define CONTEXT_H

#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"

namespace Catharsis
{

#define MENU_NONE 0
#define MENU_ANIMATION 1
#define MENU_ANIMATION_TIMEOUT 2
#define MENU_PALETTE_TIMEOUT 3
#define MENU_BRIGHTNESS 4
#define MENU_FPS 5

struct Context
{
    u_int16_t fps;
    u_int16_t brightness;

    u_int8_t currentAnimationIndex;
    u_int8_t animationsCount;
    u_int8_t animationTimeout;
    CEveryNSeconds animationTimer;

    u_int8_t currentPaletteIndex;
    u_int8_t palettesCount;
    u_int16_t paletteTimeout;
    CEveryNSeconds paletteTimer;

    u_int8_t currentMenu;
    u_int8_t menusCount;
    CRGB leds[NUM_LEDS];
};

}

#endif /* CONTEXT_H */

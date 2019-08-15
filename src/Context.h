#ifndef CONTEXT_H
#define CONTEXT_H

#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"
// #include "Animations/Animation.h"

namespace Catharsis
{

    #define MENU_NONE 0
    #define MENU_ANIMATION 1
    #define MENU_BRIGHTNESS 2
    #define MENU_FPS 3

    class Context
    {
    public:
        Context(u_int8_t animationsCount, CRGBPalette16 *palettes[]);

        u_int16_t fps;
        u_int8_t brightness;
        u_int8_t currentAnimation;
        u_int8_t currentPalette;
        u_int8_t currentMenu;
        u_int8_t menusCount;

        CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

        // Animation getCurrentAnimation();
        CRGBPalette16 getCurrentPalette();
        u_int8_t getAnimationsCount();

    private:
        // Animation *_animations[];
        CRGBPalette16 *_palettes[];
        u_int8_t _animationsCount;
    };
}

#endif /* CONTEXT_H */

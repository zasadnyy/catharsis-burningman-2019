#include <Arduino.h>
#include <FastLED.h>
#include "Animations/TmpAnimation.h"
#include "Utils/LedUtils.h"

namespace Catharsis
{
TmpAnimation::TmpAnimation() {}
void TmpAnimation::setup() {}

CRGBPalette16 currentPalette(LavaColors_p);

//mostly from the fastLED examples
void cylon(Context *context)
{

    static uint8_t hue = 0;
    // First slide the led in one direction
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        // Set the i'th led strip to red
        for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
        {
            context->leds[i * NUM_LEDS_PER_STRIP + j] = CHSV(hue++, 255, 255);
        }
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // _context->leds[i] = CRGB::Black;
        fadeall(context);

        // Wait a little bit before we loop around and do it again
        delay(100);
    }

    // Now go in the other direction.
    for (int i = NUM_STRIPS - 1; i >= 0; i--)
    {
        // Set the i'th led strip to red
        for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
        {
            context->leds[i * NUM_LEDS_PER_STRIP + j] = CHSV(hue++, 255, 255);
        }
        // Show the leds
        FastLED.show();
        // now that we've shown the leds, reset the i'th led to black
        // _context->leds[i] = CRGB::Black;
        fadeall(context);

        // Wait a little bit before we loop around and do it again
        delay(100);
    }
}

void random_walk(Context *context)
{

    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
    {
        context->leds[i] = ColorFromPalette(currentPalette, random8());
        // Show the leds
        FastLED.show();

        // // Break immediately if the change animation button was pressed
        // if (break_flag)
        // {
        //     break_flag = 0;
        //     fadeall();
        //     break;
        // }

        // Wait a little bit before we loop around and do it again
        delay(100);
    }
    delay(300);
    fadeall(context);
    delay(100);
}

// define percent likely a random cell will be alive for Conway' Game of Life
#define LIFECHANCE 20
int conway_life_seed()
{
    uint8_t rndNum = random8(99);
    if (rndNum > LIFECHANCE)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}


void TmpAnimation::loop(Context *context)
{
    //cylon(context);
    // random_walk(context);
}
} // namespace Catharsis
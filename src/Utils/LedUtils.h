#ifndef LEDUTILS_H
#define LEDUTILS_H

#include "Config.h"
#include "Context.h"

namespace Catharsis
{

static void fillLedsWithColor(Context *context, CRGB color)
{
    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
    {
        context->leds[i] = color;
    }
}

static void clearLeds(Context *context)
{
    fillLedsWithColor(context, CRGB::Black);
}

static void fadeall(Context *context)
{
    for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
    {
        context->leds[i].nscale8(256);
    }
}



} // namespace Catharsis

#endif /* LEDUTILS_H */

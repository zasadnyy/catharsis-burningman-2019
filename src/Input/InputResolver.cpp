#include <Arduino.h>
#include <cmath>
#include "Input/InputResolver.h"
#include "Utils/LedUtils.h"

namespace Catharsis
{

void InputResolver::updateContext(Input input, Context *context)
{
    Serial.print("Updating context with: ");
    Serial.println(input);

    switch (input)
    {
    case Input::BUTTON_DOWN:
    {
        context->currentMenu++;
        context->currentMenu %= context->menusCount;
        break;
    }
    case Input::BUTTON_UP:
    {
        int newIndex = context->currentMenu - 1;
        if (newIndex < 0)
        {
            newIndex = context->menusCount - 1;
        }
        context->currentMenu = newIndex;
        break;
    }
    case Input::BUTTON_LEFT:
    {
        changeMenuValue(context, -1);
        break;
    }
    case Input::BUTTON_RIGHT:
    {
        changeMenuValue(context, +1);
        break;
    }
    default:
        Serial.println("Not implemented");
        break;
    }
}

void InputResolver::changeMenuValue(Context *context, int8_t increment)
{
    switch (context->currentMenu)
    {
    case MENU_NONE:
        // Do nothing
        break;

    case MENU_ANIMATION:
    {
        int newIndex = context->currentAnimation + increment;
        if (newIndex < 0)
        {
            newIndex = context->animationsCount - 1;
        }
        else if (newIndex >= context->animationsCount)
        {
            newIndex = 0;
        }
        context->currentAnimation = newIndex;
        clearLeds(context);

        break;
    }
    case MENU_BRIGHTNESS:
    {
        int newValue = context->brightness + increment * BRIGHTNESS_STEP;
        if (newValue < 0)
        {
            newValue = 0;
        }
        else if (newValue >= MAX_BRIGHTNESS)
        {
            newValue = MAX_BRIGHTNESS;
        }
        context->brightness = newValue;
        break;
    }
    case MENU_FPS:
    {
        int newValue = context->fps + increment * FPS_STEP;
        if (newValue < 1)
        {
            newValue = 1;
        }
        else if (newValue >= MAX_FPS)
        {
            newValue = MAX_FPS;
        }
        context->fps = newValue;
        break;
    }
    }
}

} // namespace Catharsis
#include <Arduino.h>
#include <cmath>
#include "Input/InputResolver.h"
#include "Utils/Log.h"

#define BRIGHTNESS_STEP 10

namespace Catharsis {

    void InputResolver::updateContext(Input input, Context *context) {
        Serial.print("Updating context with: ");
        Serial.println(input);

        switch (input)
        {
        case Input::BRIGHTNESS_UP:
            context->brightness = min(context->brightness + BRIGHTNESS_STEP, MAX_BRIGHTNESS);
            break;

        case Input::BRIGHTNESS_DOWN:
            context->brightness = max(context->brightness - BRIGHTNESS_STEP, 0);
            break;

        case Input::ANIMATION_NEXT:
            context->currentAnimation++;
            context->currentAnimation %= context->animationsCount;
            break;

        case Input::ANIMATION_PREVIOUS:
        {
            int newIndex = context->currentAnimation - 1;
            if (newIndex < 0) {
                newIndex = context->animationsCount - 1;
            }
            context->currentAnimation = newIndex;
            break;
        }
        
        default:
            log("Not implemented: " );
            break;
        }
    }

}
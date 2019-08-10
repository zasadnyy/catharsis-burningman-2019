#include "Input/AnalogueButtonsInput.h"

namespace Catharsis
{

InputResolver::Input previousInput = InputResolver::NONE;
uint32_t previousInputTime = 0;

InputResolver::Input AnalogueButtonsInput::readInput()
{
    InputResolver::Input currentInput = readCurrentInput();

    if (currentInput == InputResolver::NONE)
    {
        return currentInput;
    }

    if (currentInput != previousInput)
    {
        previousInput = currentInput;
        previousInputTime = millis();
    }
    else
    {
        if ((millis() - previousInputTime) > COOLDOWN)
        {
            previousInputTime = millis();
        }
        else
        { // Not enough time lapsed => reset input to NONE
            currentInput = InputResolver::NONE;
        }
    }

    return currentInput;
}

InputResolver::Input AnalogueButtonsInput::readCurrentInput()
{
    int adcKeyIn = analogRead(ANALOGUE_BUTTONS_PIN);

    // Real readings from the shield
    // right 0
    // up 202
    // down 467
    // left 729
    // none  1023
    // select ??? - looks like not working

    if (adcKeyIn > 1000)
    {
        return InputResolver::NONE;
    }

    if (adcKeyIn < 50)
    {
        return InputResolver::ANIMATION_NEXT;
    }
    if (adcKeyIn < 250)
    {
        return InputResolver::BRIGHTNESS_UP;
    }
    if (adcKeyIn < 500)
    {
        return InputResolver::BRIGHTNESS_DOWN;
    }
    if (adcKeyIn < 800)
    {
        return InputResolver::ANIMATION_PREVIOUS;
    }

    return InputResolver::NONE;
}

} // namespace Catharsis
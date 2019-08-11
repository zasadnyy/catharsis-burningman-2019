#include "Input/AnalogueButtonsInput.h"
#include "Input/DFR_Key.h"

namespace Catharsis
{

// Real readings from the shield
// right 0
// up 202
// down 467
// left 729
// none  1023
// select ??? - looks like not working

DFR_Key *keypad; 

void AnalogueButtonsInput::setup()
{
    keypad = new DFR_Key(ANALOGUE_BUTTONS_PIN);
    keypad->setRate(COOLDOWN);
}

InputResolver::Input AnalogueButtonsInput::readInput()
{
    int pressedKey = keypad->getKey();

    switch (pressedKey)
    {
    case UP_KEY:
        return InputResolver::BUTTON_UP;
    case DOWN_KEY:
        return InputResolver::BUTTON_DOWN;
    case LEFT_KEY:
        return InputResolver::BUTTON_LEFT;
    case RIGHT_KEY:
        return InputResolver::BUTTON_RIGHT;
    }

    return InputResolver::NONE;
}

} // namespace Catharsis
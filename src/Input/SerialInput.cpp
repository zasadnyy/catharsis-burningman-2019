#include <Arduino.h>
#include "Input/SerialInput.h"
#include "Input/InputResolver.h"

namespace Catharsis
{

void SerialInput::setup()
{
    Serial.begin(9600);
}

InputResolver::Input SerialInput::readInput()
{
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read();
        return parseChar(receivedChar);
    }

    return InputResolver::Input::NONE;
}

InputResolver::Input SerialInput::parseChar(char c)
{
    switch (c)
    {
    case 'n':
        return InputResolver::Input::ANIMATION_NEXT;
    case 'p':
        return InputResolver::Input::ANIMATION_PREVIOUS;
    case 'f':
        return InputResolver::Input::FRAMERATE_UP;
    case 's':
        return InputResolver::Input::FRAMERATE_DOWN;
    case 'b':
        return InputResolver::Input::BRIGHTNESS_UP;
    case 'd':
        return InputResolver::Input::BRIGHTNESS_DOWN;

    default:
        Serial.print("Unrecognized input: ");
        Serial.println(c);
        return InputResolver::Input::NONE;
    }
}

} // namespace Catharsis
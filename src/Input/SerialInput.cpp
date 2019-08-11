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
    case 'w':
        return InputResolver::BUTTON_UP;
    case 's':
        return InputResolver::BUTTON_DOWN;
    case 'a':
        return InputResolver::BUTTON_LEFT;
    case 'd':
        return InputResolver::BUTTON_RIGHT;

    default:
        Serial.print("Unrecognized input: ");
        Serial.println(c);
        return InputResolver::Input::NONE;
    }
}

} // namespace Catharsis
#define USE_OCTOWS2811

#include <Arduino.h>
#include <OctoWS2811.h>
#include <FastLED.h>
#include "Config.h"
#include "Context.h"

#include "Animations/RainbowAnimation.h"
#include "Animations/LineNumbersAnimation.h"

#include "Input/InputResolver.h"
#include "Input/SerialInput.h"

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

using namespace Catharsis;

Context context;

Animation *animations[] = {
    new Animation(),
    new LineNumbersAnimation(),
    new RainbowAnimation()};


void setup()
{
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    digitalWrite(ONBOARD_LED_PIN, HIGH);

    delay(3000); // 3s power-up safety delay

    LEDS.addLeds<OCTOWS2811>(context.leds, NUM_LEDS_PER_STRIP);
    context.brightness = MAX_BRIGHTNESS / 2;
    context.animationsCount = sizeof(animations) / sizeof(animations[0]);
    context.currentAnimation = 0;

    SerialInput::setup();
}

void loop()
{
    InputResolver::Input input = SerialInput::readInput();
    if (input != InputResolver::Input::NONE)
    {
        InputResolver::updateContext(input, &context);
    }

    // Update from context
    LEDS.setBrightness(context.brightness);

    animations[context.currentAnimation]->loop(&context);

    LEDS.show();
    LEDS.delay(10);
}
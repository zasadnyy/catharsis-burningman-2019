#define USE_OCTOWS2811

#include <Arduino.h>
#include <OctoWS2811.h>
#include <FastLED.h>
#include <LiquidCrystal.h>
#include "Config.h"
#include "Context.h"

#include "Animations/RainbowAnimation.h"
#include "Animations/LineNumbersAnimation.h"
#include "Animations/FireAnimation.h"
#include "Animations/PlasmaAnimation.h"
#include "Animations/TmpAnimation.h"

#include "Input/InputResolver.h"
#include "Input/SerialInput.h"
#include "Input/AnalogueButtonsInput.h"

#include "Utils/Screen.h"

#include "Animations/MAL.h"

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

using namespace Catharsis;

Context context;
Animation *animations[] = {
    new Animation(),
    new TmpAnimation(),
    new PlasmaAnimation(),
    new RainbowAnimation(),
    new LineNumbersAnimation(),
    new FireAnimation()};


void setup()
{
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    digitalWrite(ONBOARD_LED_PIN, HIGH);

    delay(3000); // 3s power-up safety delay

    LEDS.addLeds<OCTOWS2811>(context.leds, NUM_LEDS_PER_STRIP);
    context.fps = 30;
    context.brightness = MAX_BRIGHTNESS / 2;
    context.animationsCount = sizeof(animations) / sizeof(animations[0]);
    context.currentAnimation = 0;
    context.currentMenu = MENU_NONE;
    context.menusCount = 4;

    SerialInput::setup();
    AnalogueButtonsInput::setup();

    Screen::setup();
    Screen::updateScreen(&context);

    // MAL::setup(&context);
}

void loop()
{
    // ---------------------------------------------------
    // INPUT
    // ---------------------------------------------------

    InputResolver::Input input = SerialInput::readInput();
    InputResolver::Input buttonsInput = AnalogueButtonsInput::readInput();
    if (buttonsInput != InputResolver::NONE)
    {
        input = buttonsInput;
    }

    if (input != InputResolver::NONE)
    {
        InputResolver::updateContext(input, &context);
        Screen::updateScreen(&context);
    }

    // ---------------------------------------------------
    // RENDER ANIMATION
    // ---------------------------------------------------

    uint16_t updateIntervalMs = 1000 / context.fps;
    uint32_t now = millis();
    static uint32_t lastUpdate = now;

    if (now - lastUpdate > updateIntervalMs) 
    {
        lastUpdate = now;

        LEDS.setBrightness(context.brightness);
        animations[context.currentAnimation]->loop(&context);
        LEDS.show();
    }
}
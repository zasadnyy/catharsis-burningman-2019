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

#include "Input/InputResolver.h"
#include "Input/SerialInput.h"
#include "Input/AnalogueButtonsInput.h"

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

using namespace Catharsis;

Context context;
LiquidCrystal lcd(0, 1, 17, 18, 19, 22);

Animation *animations[] = {
    new RainbowAnimation(),
    new Animation(),
    new LineNumbersAnimation(),
    new FireAnimation()};

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

    // set up the LCD's number of rows and columns:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hello, world!");
}

void loop()
{
    // if (lcd_key != btnNONE)
    // {
    //     Serial.print("Pressed button: ");
    //     Serial.println(lcd_key);
    // }

    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis() / 1000);

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
    }

    // ---------------------------------------------------
    // UPDATE FROM CONTEXT
    // ---------------------------------------------------
    LEDS.setBrightness(context.brightness);

    animations[context.currentAnimation]->loop(&context);

    LEDS.show();
    LEDS.delay(10);
}
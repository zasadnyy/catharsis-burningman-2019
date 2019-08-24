#define USE_OCTOWS2811

#include <Arduino.h>
#include <OctoWS2811.h>
#include <FastLED.h>
#include <LiquidCrystal.h>

#include "Config.h"
#include "Context.h"
#include "Animations.h"
#include "Palettes.h"

#include "Input/InputResolver.h"
#include "Input/SerialInput.h"
#include "Input/AnalogueButtonsInput.h"

#include "Utils/Screen.h"

#include "Animations/MAL.h"

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

using namespace Catharsis;

Context context;
CRGBPalette16 currentPalette;
bool inTransition = false;
int direction = -1;
int brightness = 0; 

void startTransition() {
    if (!inTransition) {
        inTransition = true;
        brightness = context.brightness;
    }
}

void switchAnimation() {
    Serial.println("switch animation");
    u_int8_t nextAnimation = context.currentAnimationIndex + 1;
    if(nextAnimation == context.animationsCount) {
        nextAnimation = 0;
    }
    context.currentAnimationIndex = nextAnimation;
}

void switchPalette() {
    u_int8_t nextPalette = context.currentPaletteIndex + 1;
    if(nextPalette == context.palettesCount) {
        nextPalette = 0;
    }
    context.currentPaletteIndex = nextPalette;
}


void setup()
{
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    digitalWrite(ONBOARD_LED_PIN, HIGH);

    delay(3000); // 3s power-up safety delay

    LEDS.addLeds<OCTOWS2811>(context.leds, NUM_LEDS_PER_STRIP);
    context.fps = FPS;
    context.brightness = BRIGHTNESS;
    context.animationsCount = sizeof(animations) / sizeof(animations[0]);
    context.currentAnimationIndex = 0;
    context.currentPaletteIndex = 0;
    context.palettesCount = sizeof(palettes) / sizeof(palettes[0]);
    context.animationTimeout = ANIMATION_TIMEOUT;
    context.paletteTimeout = PALETTES_TIMEOUT;
    context.currentMenu = MENU_NONE;
    context.menusCount = 6;

    context.animationTimer.setPeriod(context.animationTimeout);
    context.paletteTimer.setPeriod(context.paletteTimeout);

    currentPalette = palettes[0];

    SerialInput::setup();
    AnalogueButtonsInput::setup();

    Screen::setup();
    Screen::updateScreen(&context);

    // MAL::setup(&context);

    LEDS.setBrightness(context.brightness); 
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

    if (context.animationTimer) {
        startTransition();
        context.animationTimer.setPeriod(context.animationTimeout);
    }

    if (context.paletteTimer) {
        switchPalette();
        context.paletteTimer.setPeriod(context.paletteTimeout);
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


        if(inTransition) {
            LEDS.setBrightness(brightness); 
            brightness = brightness + ANIMATION_FADE_AMOUNT * direction;
            // reverse the direction of the fading at the ends of the fade: 
            if(brightness <= 0 || brightness >= context.brightness)
            {
                direction = -direction;
            }
            if(brightness <= 0) {
                switchAnimation();
            }
            if (brightness >= context.brightness) {
                inTransition = false; 
            }
        } 
        
        nblendPaletteTowardPalette(currentPalette, palettes[context.currentPaletteIndex], PALETTES_MAX_CHANGES);
        animations[context.currentAnimationIndex]->loop(&context, currentPalette);
    
        LEDS.show();
    }
}
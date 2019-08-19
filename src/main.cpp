#define USE_OCTOWS2811

#include <Arduino.h>
#include <OctoWS2811.h>
#include <FastLED.h>
#include <LiquidCrystal.h>
#include "Config.h"
#include "Context.h"
#include "Palettes.h"
#include "Animations.h"

#include "Animations/RainbowAnimation.h"
#include "Animations/LineNumbersAnimation.h"
#include "Animations/FireAnimation.h"
#include "Animations/PlasmaAnimation.h"
#include "Animations/TmpAnimation.h"
#include "Animations/PalletCrossfadeAnimation.h"
#include "Animations/Fire2012WithPalettesAnimation.h"
#include "Animations/BeatWaveAnimation.h"

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
    // new Animation(),
    // new TmpAnimation(),
    // new PlasmaAnimation(),
    new BeatWaveAnimation(),
    new Fire2012WithPalettesAnimation(),
    new PalletCrossfadeAnimation(),
    // new RainbowAnimation(),
    // new LineNumbersAnimation(),
    // new FireAnimation()
};

CRGBPalette16 curPalette;
CRGBPalette16 targetPalette;


void ChangePalettePeriodically() {
  
  uint8_t secondHand = (millis() / 1000) % 20;
  static uint8_t lastSecond = 99;
  
  if(lastSecond != secondHand) {
    lastSecond = secondHand;
    // targetPalette = palettes[secondHand/10];

    CRGB p = CHSV(HUE_PURPLE, 255, 255);
    CRGB g = CHSV(HUE_GREEN, 255, 255);
    CRGB b = CRGB::Black;
    CRGB w = CRGB::White;

    Serial.println(secondHand);

    if(secondHand ==  0)  { targetPalette = palettes[0]; }
    if(secondHand == 10)  { targetPalette = palettes[1]; }
    if(secondHand == 20)  { targetPalette = palettes[2]; }
    // if(secondHand == 10)  { targetPalette = CRGBPalette16(g,g,b,b, p,p,b,b, g,g,b,b, p,p,b,b); }
    // if(secondHand == 20)  { targetPalette = CRGBPalette16(b,b,b,w, b,b,b,w, b,b,b,w, b,b,b,w); }
    // if(secondHand == 30)  { targetPalette = LavaColors_p; }
    // if(secondHand == 40)  { targetPalette = CloudColors_p; }
    // if(secondHand == 50)  { targetPalette = PartyColors_p; }
  }

}

void switchAnimation() {
    Serial.println("Switch");
    Serial.println(context.currentAnimation);
    u_int8_t nextAnimation = context.currentAnimation + 1;
    if(nextAnimation == context.animationsCount) {
        nextAnimation = 0;
    }
    context.currentAnimation = nextAnimation;
}


void setup()
{
    pinMode(ONBOARD_LED_PIN, OUTPUT);
    digitalWrite(ONBOARD_LED_PIN, HIGH);

    delay(3000); // 3s power-up safety delay

    LEDS.addLeds<OCTOWS2811>(context.leds, NUM_LEDS_PER_STRIP);
    context.fps = 60;
    context.brightness = MAX_BRIGHTNESS / 2;
    context.animationsCount = sizeof(animations) / sizeof(animations[0]);
    context.currentAnimation = 0;
    context.currentPalette = palettes[0];
    context.currentMenu = MENU_NONE;
    context.menusCount = 4;

    curPalette = palettes[0];
    targetPalette = palettes[1];

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

    ChangePalettePeriodically();

    // EVERY_N_MILLISECONDS(2000) {
    //     uint8_t maxChanges = 24; 

    //     Serial.println('---');
    //     nblendPaletteTowardPalette(context.currentPalette, targetPalette, maxChanges);
    //     // context.currentPalette = targetPalette;
    // }

    EVERY_N_MILLISECONDS(100) {
        uint8_t maxChanges = 24; 
        nblendPaletteTowardPalette(curPalette, targetPalette, maxChanges);
    }

    EVERY_N_BSECONDS(ANIMATION_TIMEOUT) {
        switchAnimation();
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
        animations[context.currentAnimation]->loop(&context, curPalette);
        
        // CRGB* anim1 = beatwave(curPalette);
        // CRGB* anim2 = palletCrossfade(curPalette);

        // for (int i=0; i<NUM_LEDS; i++) {
        //   context.leds[i] = anim2[i]; 
        // }

        // uint8_t ratio = beatsin8(2);

        // for (int i = 0; i < NUM_LEDS; i++) {                        // mix the 2 arrays together
        //     context.leds[i] = blend( anim1[i], anim2[i], ratio);
        // }

        LEDS.show();
    }
}
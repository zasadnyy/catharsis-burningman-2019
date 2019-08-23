#define USE_OCTOWS2811

#include <Arduino.h>
#include <OctoWS2811.h>
#include <FastLED.h>
#include <LiquidCrystal.h>

#include "Config.h"
#include "Context.h"
#include "Palettes.h"
#include "Animations.h"

// #include "support.h"

#include "Animations/RainbowAnimation.h"
#include "Animations/LineNumbersAnimation.h"
#include "Animations/FireAnimation.h"
#include "Animations/PlasmaAnimation.h"
#include "Animations/TmpAnimation.h"
#include "Animations/PalletCrossfadeAnimation.h"
#include "Animations/Fire2012WithPalettesAnimation.h"
#include "Animations/BeatWaveAnimation.h"
#include "Animations/FadePulseGlowAnimation.h"
#include "Animations/NewKittAnimation.h"
#include "Animations/JungleAnimation.h"
#include "Animations/MatrixAnimation.h"
#include "Animations/NoiseAnimation.h"

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
    // new BeatWaveAnimation(),
    // new NewKittAnimation(),
    new FadePulseGlowAnimation(),
    // new NoiseAnimation(),
    new JungleAnimation(),
    new MatrixAnimation(),
    new PlasmaAnimation(),
    // new Fire2012WithPalettesAnimation(),
    // new PalletCrossfadeAnimation(),
    new RainbowAnimation(),
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

bool inTransition = false;
bool direction = 0;
int fadeAmount = -5;  // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
int brightness = 0; 

void startTransition() {
    if (!inTransition) {
        direction = -1;
        inTransition = true;
        brightness = context.brightness;
        fadeAmount = -2;
    }
}

void switchAnimation() {
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
    context.brightness = 100;
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

    ChangePalettePeriodically();

    EVERY_N_MILLISECONDS(PALETTES_TIMEOUT) {
        nblendPaletteTowardPalette(curPalette, targetPalette, PALETTES_MAX_CHANGES);
    }

    EVERY_N_BSECONDS(ANIMATION_TIMEOUT) {
        startTransition();
    }

    // ---------------------------------------------------
    // RENDER ANIMATION
    // ---------------------------------------------------

    uint16_t updateIntervalMs = 1000 / context.fps;
    uint32_t now = millis();
    static uint32_t lastUpdate = now;

    // if (now - lastUpdate > updateIntervalMs) 
    // {
    //     lastUpdate = now;


        if(inTransition) {
            LEDS.setBrightness(brightness); 
            brightness = brightness + fadeAmount;
            // reverse the direction of the fading at the ends of the fade: 
            if(brightness == 0 || brightness == context.brightness)
            {
                fadeAmount = -fadeAmount;
            }
            if(brightness == 0) {
                switchAnimation();
            }
            if (brightness == context.brightness) {
                inTransition = false; 
            }
        } 
        
        animations[context.currentAnimation]->loop(&context, curPalette);
    
        LEDS.show();
    // }
}
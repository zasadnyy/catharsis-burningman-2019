// // RGB LED Matrix Animation Library
// // Copyright (C) 2016 Robbie Nichols
// //
// // This program is free software: you can redistribute it and/or modify it
// // under the terms of the GNU General Public License as published by the Free
// // Software Foundation, either version 3 of the License, or (at your option)
// // any later version.
// //
// // This program is distributed in the hope that it will be useful, but WITHOUT
// // ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
// // FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
// // more details.
// //
// // You should have received a copy of the GNU General Public License along with
// // this program.  If not, see <http://www.gnu.org/licenses/>.
// //
// // Some parts were initially copied out of the FastLED examples directory.
// // those are licensed under the MIT license. If you want to use some of this
// // code under a less restrictive license, there is a chance it is from FastLED.
// //
// // https://github.com/FastLED/FastLED
// //
// // This program is meant to be a collection of easy to reuse and easy to read
// // animations for RGB LED matricies of arbitrary sizes. All the #define
// // statements can be changed as settings for the program, or the animations can
// // be lifted out for use in another program.

// // The hardware config for this program is very simple. Two push buttons, each
// // connected to one of the BUTTON_PIN pins and ground.
// // The LED strips should be wired as one continuous strip with alternating
// // directions.

// #include <FastLED.h>
// #include "MAL.h"
// #include "Config.h"
// #include "Context.h"

// namespace Catharsis
// {

// #define FALSE 0

// #define enable_cylon 1
// #define enable_pallet_fade 0
// #define enable_random_walk 1
// #define enable_fullrandom 1
// #define enable_conway_life 1
// #define enable_flow_through_pallet 1
// #define enable_center_box 1
// #define enable_lightning_bugs 1
// #define enable_full_fade 1

// #define cylon_case 0
// #define pallet_fade_case 1
// #define random_walk_case 2
// #define fullrandom_case 3
// #define conway_life_case 4
// #define flow_through_pallet_case 5
// #define center_box_case 6
// #define lightning_bugs_case 7
// #define full_fade_case 8
// #define last_case 9 //this is used to loop. not an animation

// // Hardware settings start //////////

// // These are settings for FastLED that vary depending on LED Strip
// // #define FastLED_LED_Strip_type WS2811
// // #define FastLED_LED_Color_Order BRG

// // default 7 strips of 6 LEDs each
// // #define NUM_STRIPS

// //Define the data pin
// // #define DATA_PIN1 5

// //define pins for the buttons. Mush have hardware interupts
// // #define ANIMATION_BUTTON_PIN 3
// // #define PALETTE_BUTTON_PIN 2

// // This adjusts how bright the LEDs are
// // #define BRIGHTNESS 80

// // Hardware settings end ////////////

// // Animation settins start //////////

// // This audjusts how quickly some things happen
// #define FRAMES_PER_SECOND 60

// // define percent likely a random cell will be alive for Conway' Game of Life
// #define LIFECHANCE 20

// // This controls how often the lightning bugs flash
// // one "bug" should average a blink every 20 seconds
// #define NUMBER_OF_LIGHTNING_BUGS 10

// // Animation settings end ///////////

// //Define LED array
// // CRGB leds[NUM_LEDS_PER_STRIP * NUM_STRIPS];

// using namespace Catharsis;

// volatile int animation;

// CRGBPalette16 currentPalette(HeatColors_p);

// CRGBPalette16 targetPalette(PartyColors_p);

// //This is a flag that is checked inside loops to make sure the animation change
// // button hasn't been pressed between loop iterations
// volatile bool break_flag = 0;

// Context *_context;

// //This mostly comes from the fastLED cylon example.12E
// void fadeall()
// {
//     for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
//     {
//         _context->leds[i].nscale8(256);
//     }
// }

// void MAL::change_animation()
// {

//     // static unsigned long last_interrupt_time = 0;
//     // unsigned long interrupt_time = millis();

//     // If interrupts come faster than 200ms, assume it's a bounce and ignore
//     // if (interrupt_time - last_interrupt_time > 200)
//     // {
//     if (animation < last_case)
//         animation++;
//     else
//         animation = 0;

//     // use a little recursion to skip animations that are disabled
//     // if (animation == cylon_case && enable_cylon == FALSE)
//     //     change_animation();
//     // else if (animation == pallet_fade_case && enable_pallet_fade == FALSE)
//     //     change_animation();
//     // else if (animation == random_walk_case && enable_random_walk == FALSE)
//     //     change_animation();
//     // else if (animation == fullrandom_case && enable_fullrandom == FALSE)
//     //     change_animation();
//     // else if (animation == conway_life_case && enable_conway_life == FALSE)
//     //     change_animation();
//     // else if (animation == flow_through_pallet_case && enable_flow_through_pallet == FALSE)
//     //     change_animation();
//     // else if (animation == center_box_case && enable_center_box == FALSE)
//     //     change_animation();
//     // else if (animation == lightning_bugs_case && enable_lightning_bugs == FALSE)
//     //     change_animation();
//     // else if (animation == full_fade_case && enable_full_fade == FALSE)
//     //     change_animation();
//     // }
//     // last_interrupt_time = interrupt_time;

//     //blank out the LEDs for the next animation
//     fadeall();
//     // FastLED.setBrightness(BRIGHTNESS);
// }

// void MAL::change_palette()
// {
//     // static unsigned long last_interrupt_time = 0;
//     // unsigned long interrupt_time = millis();
//     static uint8_t palette = -1; //random8(8);
//     palette++;
//     palette %= 8;

//     // If interrupts come faster than 500ms, assume it's a bounce and ignore
//     // if (interrupt_time - last_interrupt_time > 500)
//     // {
//     switch (palette)
//     {
//     case 1:
//         currentPalette = RainbowColors_p;
//         break;
//     case 2:
//         currentPalette = CloudColors_p;
//         break;
//     case 3:
//         currentPalette = LavaColors_p;
//         break;
//     case 4:
//         currentPalette = OceanColors_p;
//         break;
//     case 5:
//         currentPalette = ForestColors_p;
//         break;
//     case 6:
//         currentPalette = RainbowStripeColors_p;
//         break;
//     case 7:
//         currentPalette = PartyColors_p;
//         break;
//     case 8:
//         currentPalette = CRGBPalette16(
//             0x480000, 0xF0A860, 0x000000, 0xF09048,
//             0xD84830, 0x000000, 0xF0C060, 0x000000,
//             0x66330, 0xFFFFFF, 0xFF0000, 0xFF6600,
//             0xFFCC00, 0x480000, 0xF0A860, 0xF0C060);
//     default:
//         currentPalette = HeatColors_p;
//         palette = 0;
//     }
//     // palette++;
//     Serial.print("palette: ");
//     Serial.println(palette);
//     // }
//     // last_interrupt_time = interrupt_time;
// }

// void MAL::setup(Context *context)
// {
//     _context = context;
//     random16_add_entropy(random());

//     //add LEDs to FastLED
//     // FastLED.addLeds<FastLED_LED_Strip_type, DATA_PIN1, FastLED_LED_Color_Order>(leds, NUM_LEDS_PER_STRIP * NUM_STRIPS);

//     // pinMode(ANIMATION_BUTTON_PIN, INPUT_PULLUP);
//     // pinMode(PALETTE_BUTTON_PIN, INPUT_PULLUP);
//     // attachInterrupt(digitalPinToInterrupt(ANIMATION_BUTTON_PIN), change_animation, LOW);
//     // attachInterrupt(digitalPinToInterrupt(PALETTE_BUTTON_PIN), change_palette, LOW);

//     // FastLED.setBrightness(BRIGHTNESS);

//     //initialize with a random palette
//     change_palette();
//     change_animation();
// }

// void FillLEDsFromPaletteColors(uint8_t colorIndex)
// {

//     for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
//     {
//         _context->leds[i] = ColorFromPalette(currentPalette, colorIndex + sin8(i * 16), MAX_BRIGHTNESS);
//         colorIndex += 3;
//     }
// }

// void ChangePalettePeriodically()
// {
//     uint8_t secondHand = (millis() / 1000) % 60;
//     static uint8_t lastSecond = 99;

//     if (lastSecond != secondHand)
//     {
//         lastSecond = secondHand;
//         CRGB p = CHSV(HUE_PURPLE, 255, 255);
//         CRGB g = CHSV(HUE_GREEN, 255, 255);
//         CRGB b = CRGB::Black;
//         CRGB w = CRGB::White;
//         if (secondHand == 0)
//         {
//             targetPalette = RainbowColors_p;
//         }
//         if (secondHand == 10)
//         {
//             targetPalette = CRGBPalette16(g, g, b, b, p, p, b, b, g, g, b, b, p, p, b, b);
//         }
//         if (secondHand == 20)
//         {
//             targetPalette = CRGBPalette16(b, b, b, w, b, b, b, w, b, b, b, w, b, b, b, w);
//         }
//         if (secondHand == 30)
//         {
//             targetPalette = LavaColors_p;
//         }
//         if (secondHand == 40)
//         {
//             targetPalette = CloudColors_p;
//         }
//         if (secondHand == 50)
//         {
//             targetPalette = PartyColors_p;
//         }
//     }
// }

// //from https://gist.github.com/kriegsman/1f7ccbbfa492a73c015e
// void pallet_fade()
// {

//     // ChangePalettePeriodically();

//     // Crossfade current palette slowly toward the target palette
//     //
//     // Each time that nblendPaletteTowardPalette is called, small changes
//     // are made to currentPalette to bring it closer to matching targetPalette.
//     // You can control how many changes are made in each call:
//     //   - the default of 24 is a good balance
//     //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
//     //   - "0" means do not change the currentPalette at all; freeze

//     uint8_t maxChanges = 24;
//     nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);

//     static uint8_t startIndex = 0;
//     startIndex = startIndex + 1; /* motion speed */
//     FillLEDsFromPaletteColors(startIndex);

//     FastLED.show();
//     FastLED.delay(1000 / FRAMES_PER_SECOND);
// }

// //mostly from the fastLED examples
// void cylon()
// {

//     static uint8_t hue = 0;
//     // First slide the led in one direction
//     for (int i = 0; i < NUM_STRIPS; i++)
//     {
//         // Set the i'th led strip to red
//         for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
//         {
//             _context->leds[i * NUM_LEDS_PER_STRIP + j] = CHSV(hue++, 255, 255);
//         }
//         // Show the leds
//         FastLED.show();
//         // now that we've shown the leds, reset the i'th led to black
//         // _context->leds[i] = CRGB::Black;
//         fadeall();

//         // Break immediately if the change animation button was pressed
//         if (break_flag)
//         {
//             break_flag = 0;
//             fadeall();
//             break;
//         }

//         // Wait a little bit before we loop around and do it again
//         delay(100);
//     }

//     // Now go in the other direction.
//     for (int i = NUM_STRIPS - 1; i >= 0; i--)
//     {
//         // Set the i'th led strip to red
//         for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
//         {
//             _context->leds[i * NUM_LEDS_PER_STRIP + j] = CHSV(hue++, 255, 255);
//         }
//         // Show the leds
//         FastLED.show();
//         // now that we've shown the leds, reset the i'th led to black
//         // _context->leds[i] = CRGB::Black;
//         fadeall();

//         // Break immediately if the change animation button was pressed
//         if (break_flag)
//         {
//             break_flag = 0;
//             fadeall();
//             break;
//         }

//         // Wait a little bit before we loop around and do it again
//         delay(100);
//     }
// }

// void random_walk()
// {

//     for (int i = 0; i < NUM_LEDS_PER_STRIP * NUM_STRIPS; i++)
//     {
//         _context->leds[i] = ColorFromPalette(currentPalette, random8());
//         // Show the leds
//         FastLED.show();

//         // Break immediately if the change animation button was pressed
//         if (break_flag)
//         {
//             break_flag = 0;
//             fadeall();
//             break;
//         }

//         // Wait a little bit before we loop around and do it again
//         delay(100);
//     }
//     delay(300);
//     fadeall();
//     delay(100);
// }

// void fullrandom()
// {
//     _context->leds[random8(NUM_LEDS_PER_STRIP * NUM_STRIPS)] = ColorFromPalette(currentPalette, random8());

//     //    Serial.print("random: ");
//     //    Serial.println(random8(NUM_LEDS_PER_STRIP * NUM_STRIPS));
//     FastLED.show();
//     delay(50);
// }

// // This currently can only do one bug at a time. This would be a great OOP re-write
// // but I don't feel like doing it right now.
// void lightning_bugs()
// {
//     unsigned long current_time = millis();
//     static unsigned long next_flash = millis();

//     if (current_time < next_flash)
//     {
//         next_flash = random16(100, 39900) / NUMBER_OF_LIGHTNING_BUGS;
//         unsigned int flashes = random8(1, 6);
//         unsigned int interval_len = random16(50, 600);
//         unsigned int flash_duration = random16(50, 600);
//         unsigned int led = random16(NUM_LEDS_PER_STRIP * NUM_STRIPS);
//         CRGB color = ColorFromPalette(currentPalette, random8());

//         for (int i = 0; i < flashes; i++)
//         {

//             // Break immediately if the change animation button was pressed
//             if (break_flag)
//             {
//                 break_flag = 0;
//                 fadeall();
//                 break;
//             }

//             _context->leds[led] = color;
//             FastLED.show();
//             delay(flash_duration);
//             _context->leds[led].nscale8(256);

//             // Break immediately if the change animation button was pressed
//             if (break_flag)
//             {
//                 break_flag = 0;
//                 fadeall();
//                 break;
//             }

//             delay(interval_len);
//         }
//     }
// }

// void flow_through_pallet()
// {
// }

// void center_box()
// {
//     int led_mult;
//     int strip_mult;
//     static uint8_t inc = 0;

//     for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
//     {
//         if (i > NUM_LEDS_PER_STRIP / 2)
//         {
//             led_mult = i - (NUM_LEDS_PER_STRIP - 2 * i);
//         }
//         else
//         {
//             led_mult = i;
//         }
//         for (int j = 0; j < NUM_STRIPS; j++)
//         {

//             // Break immediately if the change animation button was pressed
//             if (break_flag)
//             {
//                 break_flag = 0;
//                 fadeall();
//                 break;
//             }

//             if (j > NUM_STRIPS / 2)
//             {
//                 strip_mult = j - (NUM_STRIPS - 2 * j);
//             }
//             else
//             {
//                 strip_mult = j;
//             }
//             if (led_mult < strip_mult)
//             {
//                 _context->leds[j * i] = ColorFromPalette(currentPalette, ((led_mult + inc) % 16) * 16);
//             }
//             else
//             {
//                 _context->leds[j * i] = ColorFromPalette(currentPalette, ((strip_mult + inc) % 16) * 16);
//             }
//         }
//     }
//     inc++;
//     FastLED.show();
// }

// void full_fade()
// {
//     static uint8_t inc = 0;
//     uint8_t bright;

//     for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
//     {
//         for (int j = 0; j < NUM_STRIPS; j++)
//         {
//             _context->leds[j * i] = ColorFromPalette(currentPalette, ((inc) % 16) * 16);

//             // Break immediately if the change animation button was pressed
//             if (break_flag)
//             {
//                 break_flag = 0;
//                 fadeall();
//                 break;
//             }
//         }
//     }

//     for (int k = -MAX_BRIGHTNESS; k <= MAX_BRIGHTNESS; k++)
//     {
//         // Break immediately if the change animation button was pressed
//         if (break_flag)
//         {
//             break_flag = 0;
//             fadeall();
//             break;
//         }
//         bright = MAX_BRIGHTNESS - abs(k);
//         FastLED.setBrightness(bright);
//         FastLED.show();
//     }
//     inc++;
// }

// int conway_life_seed()
// {
//     uint8_t rndNum = random8(99);
//     if (rndNum > LIFECHANCE)
//     {
//         return (1);
//     }
//     else
//     {
//         return (0);
//     }
// }

// void conway_life()
// {
//     static bool lifeChanges[NUM_LEDS_PER_STRIP][NUM_STRIPS]{}; //initialize all 0
//     static CRGBPalette16 startingPalette{};                    //initialize null (I hope)

//     // changing the palette also resets the game
//     if (startingPalette != currentPalette)
//     {
//         startingPalette = currentPalette;
//         fadeall();
//         for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
//         {
//             for (int j = 0; j < NUM_STRIPS; j++)
//             {
//                 lifeChanges[i][j] = conway_life_seed();
//             }
//         }
//     }
//     else
//     {
//         // This is where the game counts neighbors to see what changes need to happen
//     }

//     for (int i = 0; i < NUM_LEDS_PER_STRIP; i++)
//     {
//         for (int j = 0; j < NUM_STRIPS; j++)
//         {
//             //set all the cells here
//         }
//     }

//     FastLED.show();
//     delay(500);
// }

// void MAL::loop()
// {

//     switch (animation)
//     {
//     case cylon_case:
//         Serial.print("Cyclon");
//         cylon();
//         break;
//     case pallet_fade_case:
//         Serial.print("Palete fade");
//         pallet_fade();
//         break;
//     case random_walk_case:
//         Serial.print("Random walk");
//         random_walk();
//         break;
//     case fullrandom_case:
//         Serial.print("Full rndom");
//         fullrandom();
//         break;
//     case conway_life_case:
//         Serial.print("Conway life");
//         conway_life();
//         break;
//     case flow_through_pallet_case:
//         Serial.print("Flow through pallete");
//         flow_through_pallet();
//         break;
//     case center_box_case:
//         Serial.print("Center box");
//         center_box();
//         break;
//     case lightning_bugs_case:
//         Serial.print("Lightning bugs");
//         lightning_bugs();
//         break;
//     case full_fade_case:
//         Serial.print("Full fade");
//         full_fade();
//         break;
//     }
// }

// } // namespace Catharsis

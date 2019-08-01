// #include "Arduino.h"
// #include "FastLED.h"

// #define NUM_LEDS 164
// #define DATA_PIN 12
// #define ONBOARD_LED_PIN 13

// CRGB leds[NUM_LEDS];

// void setup() {
//   delay( 3000 ); // power-up safety delay
//   FastLED.addLeds<WS2813, DATA_PIN, GRB>(leds, NUM_LEDS);
//   FastLED.setBrightness(  255 );

//   pinMode(ONBOARD_LED_PIN, OUTPUT);
// }

// void loop() {

//   for (int i = 0; i < NUM_LEDS; i++) {
//     leds[i] = CRGB::White;
//   }

//   FastLED.show();
//   delay(30);

//   //  for (int i = 0; i <= 23; i++) {
//   //    digitalWrite(i, HIGH);
//   //  }
//   digitalWrite(ONBOARD_LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(1000);               // wait for a secon
//   digitalWrite(ONBOARD_LED_PIN, LOW);    // turn the LED off by making the voltage LOW
//   delay(1000);               // wait for a second
// }

#define USE_OCTOWS2811
#include <OctoWS2811.h>
#include <FastLED.h>

#define NUM_LEDS_PER_STRIP 20
#define NUM_STRIPS 4

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup()
{
  delay(3000); // power-up safety delay
  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(32);
}

static int lIndex = 0;
void loop()
{
  // static uint8_t hue = 0;
  // for (int i = 0; i < NUM_STRIPS; i++)
  // {
  //   for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
  //   {
  //     leds[i * NUM_LEDS_PER_STRIP + j] = CHSV((32 * i) + hue + i, 192, 255);
  //   }
  // }
  // hue++;

  FastLED.clear();
  for (int strip = 0; strip < NUM_STRIPS; strip++)
  {
    leds[strip * NUM_LEDS_PER_STRIP + lIndex] = CHSV(255 / NUM_LEDS_PER_STRIP * lIndex, 255, 255);
  }

  lIndex++;
  lIndex %= NUM_LEDS_PER_STRIP;

  // Set the first n leds on each strip to show which strip it is
  for (int i = 0; i < NUM_STRIPS; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      leds[(i * NUM_LEDS_PER_STRIP) + j] = CRGB::Red;
    }
  }

  LEDS.show();
  LEDS.delay(10);
}
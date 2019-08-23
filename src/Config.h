#ifndef CONFIG_H
#define CONFIG_H

#define ONBOARD_LED_PIN 13
#define ANALOGUE_BUTTONS_PIN 23
#define SCREEN_RS_PIN 0
#define SCREEN_ENABLE_PIN 1
#define SCREEN_D4_PIN 17
#define SCREEN_D5_PIN 18
#define SCREEN_D6_PIN 19
#define SCREEN_D7_PIN 22

#define NUM_LEDS_PER_STRIP 666
#define NUM_STRIPS 8
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

#define ANIMATION_TIMEOUT 10 // Seconds
#define PALETTES_TIMEOUT 100 // Milliseconds
#define PALETTES_MAX_CHANGES 24 // Milliseconds

#define MAX_BRIGHTNESS 255
#define MAX_FPS 510 // The max FPS I could get from Teensy

// #define qsubd(x, b) ((x>b)?b:0)                               
// #define qsuba(x, b) ((x>b)?x-b:0) 

// CRGB leds[NUM_LEDS];

#endif /* CONFIG_H */

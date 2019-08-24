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

#define ANIMATION_TIMEOUT 10 // Minutes
#define MAX_ANIMATION_TIMEOUT 15

#define PALETTES_TIMEOUT 20 // Seconds
#define MAX_PALETTE_TIMEOUT 180
#define PALETTES_MAX_CHANGES 24
#define PALETTE_TIMEOUT_STEP 10

#define BRIGHTNESS 50
#define MAX_BRIGHTNESS 255
#define ANIMATION_FADE_AMOUNT 2 // Set the amount to fade I usually do 5, 10, 15, 20, 25 etc even up to 255.
#define BRIGHTNESS_STEP 10

#define FPS 60
#define MAX_FPS 510 // The max FPS I could get from Teensy
#define FPS_STEP 5

// #define qsubd(x, b) ((x>b)?b:0)                               
// #define qsuba(x, b) ((x>b)?x-b:0) 

#endif /* CONFIG_H */

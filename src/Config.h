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

#define NUM_LEDS_PER_STRIP 15
#define NUM_STRIPS 8
#define NUM_LEDS NUM_STRIPS * NUM_LEDS_PER_STRIP

#define MAX_BRIGHTNESS 255
#define MAX_FPS 510 // The max FPS I could get from Teensy



#endif /* CONFIG_H */

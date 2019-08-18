#include <FastLED.h>
#include <Arduino.h>
#include "Animations/ConveyLifeAnimation.h"

namespace Catharsis
{
ConveyLifeAnimation::ConveyLifeAnimation() {}

// #include <SmartMatrix3.h>

// #define COLOR_DEPTH 24                  // This sketch and FastLED uses type `rgb24` directly, COLOR_DEPTH must be 24
// const uint8_t kMatrixWidth = 32;        // known working: 32, 64, 96, 128
// const uint8_t kMatrixHeight = 32;       // known working: 16, 32, 48, 64
// const uint8_t kRefreshDepth = 36;       // known working: 24, 36, 48
// const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
// const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
// const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
// const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

// SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
// SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

// #define NUM_LEDS (kMatrixWidth * kMatrixHeight)

// blur between each frame of the simulation
boolean blur = true;

// adjust the amount of blur
float blurAmount = 0.5;

boolean randomBlur = true;

// alternate between blurred and not blurred each time a new world is filled
boolean alternateBlur = true;

// switch to a random palette each time a new world is filled
boolean switchPalette = true;

CRGBPalette16 currentGamePalette = PartyColors_p;

class Cell
{
public:
    byte alive = 1;
    byte prev = 1;
    byte hue = 6;
    byte brightness;
};

Cell world[NUM_STRIPS][NUM_LEDS_PER_STRIP];
long density = 30;
int generation = 0;

void randomFillWorld()
{
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
        {
            if (random(100) < (unsigned long)density)
            {
                world[i][j].alive = 1;
                world[i][j].brightness = 255;
            }
            else
            {
                world[i][j].alive = 0;
                world[i][j].brightness = 0;
            }
            world[i][j].prev = world[i][j].alive;
            world[i][j].hue = 0;
        }
    }
}

int neighbours(int x, int y)
{
    return (world[(x + 1) % NUM_STRIPS][y].prev) +
           (world[x][(y + 1) % NUM_LEDS_PER_STRIP].prev) +
           (world[(x + NUM_STRIPS - 1) % NUM_STRIPS][y].prev) +
           (world[x][(y + NUM_LEDS_PER_STRIP - 1) % NUM_LEDS_PER_STRIP].prev) +
           (world[(x + 1) % NUM_STRIPS][(y + 1) % NUM_LEDS_PER_STRIP].prev) +
           (world[(x + NUM_STRIPS - 1) % NUM_STRIPS][(y + 1) % NUM_LEDS_PER_STRIP].prev) +
           (world[(x + NUM_STRIPS - 1) % NUM_STRIPS][(y + NUM_LEDS_PER_STRIP - 1) % NUM_LEDS_PER_STRIP].prev) +
           (world[(x + 1) % NUM_STRIPS][(y + NUM_LEDS_PER_STRIP - 1) % NUM_LEDS_PER_STRIP].prev);
}

uint16_t XY(uint8_t x, uint8_t y)
{
    return (y * NUM_STRIPS) + x;
}

void chooseNewPalette()
{
    switch (random(0, 8))
    {
    case 0:
        currentGamePalette = CloudColors_p;
        break;

    case 1:
        currentGamePalette = ForestColors_p;
        break;

    case 2:
        currentGamePalette = HeatColors_p;
        break;

    case 3:
        currentGamePalette = LavaColors_p;
        break;

    case 4:
        currentGamePalette = OceanColors_p;
        break;

    case 5:
        currentGamePalette = PartyColors_p;
        break;

    case 6:
        currentGamePalette = RainbowColors_p;
        break;

    case 7:
    default:
        currentGamePalette = RainbowStripeColors_p;
        break;
    }
}

// void setup() {
//   matrix.addLayer(&backgroundLayer);
//   matrix.begin();
//   matrix.setBrightness(32);
// }

void ConveyLifeAnimation::loop(Context *context)
{
    // rgb24 *buffer = backgroundLayer.backBuffer();

    if (generation == 0)
    {
        // fill_solid((CRGB *)buffer, NUM_LEDS, CRGB::Black);
        fill_solid(context->leds, NUM_LEDS, CRGB::Black);

        randomFillWorld();

        if (alternateBlur)
            blur = !blur;

        if (switchPalette)
            chooseNewPalette();

        if (randomBlur)
            blurAmount = ((float)random(50, 90)) / 100.0;
    }

    // Display current generation
    for (int i = 0; i < NUM_STRIPS; i++)
    {
        for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
        {
            if (blur)
            {
                context->leds[XY(i, j)] = ColorFromPalette(currentGamePalette, world[i][j].hue * 4, world[i][j].brightness);
            }
            else if (world[i][j].alive == 1)
            {
                context->leds[XY(i, j)] = ColorFromPalette(currentGamePalette, world[i][j].hue * 4, world[i][j].brightness);
            }
            else
            {
                context->leds[XY(i, j)] = (CRGB)CRGB::Black;
            }
        }
    }

    // Birth and death cycle
    for (int x = 0; x < NUM_STRIPS; x++)
    {
        for (int y = 0; y < NUM_LEDS_PER_STRIP; y++)
        {
            // Default is for cell to stay the same
            if (world[x][y].brightness > 0 && world[x][y].prev == 0)
                world[x][y].brightness *= blurAmount;
            int count = neighbours(x, y);
            if (count == 3 && world[x][y].prev == 0)
            {
                // A new cell is born
                world[x][y].alive = 1;
                world[x][y].hue += 2;
                world[x][y].brightness = 255;
            }
            else if ((count < 2 || count > 3) && world[x][y].prev == 1)
            {
                // Cell dies
                world[x][y].alive = 0;
            }
        }
    }

    // Copy next generation into place
    for (int x = 0; x < NUM_STRIPS; x++)
    {
        for (int y = 0; y < NUM_LEDS_PER_STRIP; y++)
        {
            world[x][y].prev = world[x][y].alive;
        }
    }

    generation++;
    // if (generation >= 256)
    //     generation = 0;

    // backgroundLayer.swapBuffers();
    // LEDS.delay(33);
}

} // namespace Catharsis
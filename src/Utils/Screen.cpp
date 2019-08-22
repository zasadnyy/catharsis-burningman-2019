#include <LiquidCrystal.h>
#include "Utils/Screen.h"

namespace Catharsis
{

LiquidCrystal lcd(SCREEN_RS_PIN, SCREEN_ENABLE_PIN, SCREEN_D4_PIN, SCREEN_D5_PIN, SCREEN_D6_PIN, SCREEN_D7_PIN);

void Screen::setup()
{
    lcd.begin(16, 2);
}

void Screen::updateScreen(Context *context)
{
    lcd.clear();

    String currentMenu = "";

    lcd.setCursor(0, 0);
    currentMenu = context->currentMenu == MENU_ANIMATION ? ">" : "";
    lcd.print(currentMenu + "Animation " + String(context->currentAnimation));

    // Serial.println(String(currentMenu + "Animation " + String(context->currentAnimation)));

    lcd.setCursor(0, 1);
    currentMenu = context->currentMenu == MENU_BRIGHTNESS ? ">" : "";
    lcd.print(currentMenu + "BR:" + String(context->brightness));

    // Serial.println(currentMenu + "BR: " + String(context->brightness));

    lcd.setCursor(8, 1);
    currentMenu = context->currentMenu == MENU_FPS ? ">" : "";
    lcd.print(currentMenu + "FPS:" + String(LEDS.getFPS()));

    // Serial.println(currentMenu + "FPS: " + String(context->fps) + "(" + LEDS.getFPS() + ")");
}

} // namespace Catharsis
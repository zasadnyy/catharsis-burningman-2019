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
    
    // 0123456789012345
    // A:10 AT:10 PT:10  
    // BR:100  FPS:555

    lcd.setCursor(0, 0);
    currentMenu = context->currentMenu == MENU_ANIMATION ? ">" : "";
    lcd.print(currentMenu + "A:" + String(context->currentAnimationIndex));


    lcd.setCursor(5, 0);
    currentMenu = context->currentMenu == MENU_ANIMATION_TIMEOUT ? ">" : "";
    lcd.print(currentMenu + "AT:" + String(context->animationTimeout));


    lcd.setCursor(11, 0);
    currentMenu = "";
    if (context->currentMenu == MENU_PALETTE_TIMEOUT) {
        lcd.setCursor(10, 0);
        currentMenu = ">";
    }
    lcd.print(currentMenu + "PT:" + String(context->paletteTimeout));


    lcd.setCursor(0, 1);
    currentMenu = context->currentMenu == MENU_BRIGHTNESS ? ">" : "";
    lcd.print(currentMenu + "BR:" + String(context->brightness));


    lcd.setCursor(8, 1);
    currentMenu = context->currentMenu == MENU_FPS ? ">" : "";
    lcd.print(currentMenu + "FPS:" + String(LEDS.getFPS()));
}

} // namespace Catharsis
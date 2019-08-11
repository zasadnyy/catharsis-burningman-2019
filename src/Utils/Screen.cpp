#include <LiquidCrystal.h>
#include "Utils/Screen.h"

namespace Catharsis
{

LiquidCrystal lcd(0, 1, 17, 18, 19, 22);

void Screen::setup()
{
    lcd.begin(16, 2);
}

void Screen::updateScreen(Context *context) {
    lcd.setCursor(0, 0);
    lcd.print("Catharsis");
    
    lcd.setCursor(0, 1);
    lcd.print("BR: " + String(context->brightness));

    lcd.setCursor(7, 1);
    // Serial.println("FPS: " + String(context.fps));
    lcd.print("FPS: " + String(context->fps));
}

} // namespace Catharsis
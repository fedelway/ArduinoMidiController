#include "screen.h"

Screen::Screen(LiquidCrystal& lcd) : lcd(lcd)
{

}

void Screen::writeStateChange(const char* stateName)
{
    lcd.home();
    lcd.print("Modo: ");
    lcd.print(stateName);
}

void Screen::writeVolumeChange(int vol)
{
    lcd.setCursor(0,1);
    lcd.print("Vol: ");
    lcd.print(vol);
}

void Screen::writeNoteChange(int note)
{
    lcd.setCursor(8,1);
    lcd.print("Nota: ");
    lcd.print(note);
}
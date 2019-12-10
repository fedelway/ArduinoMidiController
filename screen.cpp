#include "screen.h"

Screen::Screen(LiquidCrystal& lcd) : lcd(lcd)
{

}

void Screen::writeStateChange(const char* stateName)
{
    lcd.home();
    lcd.print("Modo:           ");
    lcd.setCursor(7,0);
    lcd.print(stateName);
}

void Screen::writeVolumeChange(int vol)
{
    lcd.setCursor(0,1);
    lcd.print("Vol:    ");
    lcd.setCursor(5,1);
    lcd.print(vol);
}

void Screen::writeNoteChange(int note)
{
    lcd.setCursor(8,1);
    lcd.print("Nota: ");
    lcd.print(note);
}

void Screen::writeScaleChange(const char* scaleName)
{
    lcd.home();
    lcd.print("Escala:         ");
    lcd.setCursor(8,0);
    lcd.print(scaleName);
}

void Screen::writeIpAddress(const IPAddress& ip)
{
    lcd.home();
    lcd.print("                ");
    lcd.home();
    lcd.print(ip);
}
#include "LedControl.h"

LedControl lc=LedControl(11,13,10,4);  // Pins: DIN,CLK,CS, # of Display connected

void fillDisplay()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,0xFF);
    lc.setRow(1,i,0xFF);
    lc.setRow(2,i,0xFF);
    lc.setRow(3,i,0xFF);
  }
}

void setup()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.shutdown(3,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.setIntensity(2,5);
  lc.setIntensity(3,5);
  fillDisplay();
  delay(500);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

void loop()
{
  lc.setDigit(0, 0, 0x0F, false);
}

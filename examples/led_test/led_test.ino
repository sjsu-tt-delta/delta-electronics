#include "fc16.h"

FC16 led = FC16();

void setup()
{
  Serial.begin(9600);
  led.init();
  led.display_scrolling_text("Hello!");
}

void loop()
{
  led.update();
}

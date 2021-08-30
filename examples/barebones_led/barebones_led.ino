#include <stdlib.h>
#include "fc16.h"

FC16 led = FC16();

unsigned int counter = 0;

unsigned char buff0[20] = "Rush Theta Tau!";

void setup()
{
  
  led.init();

  led.set_brightness(15);
  led.set_static_align(PA_CENTER);
  led.display_static_text("On!");
  _delay_ms(1000);
  led.display_static_text("");
  //led.reset();
  //led.display_scrolling_text("Test");
  led.display_scrolling_text(buff0);
}

void loop()
{
  if (counter > 80)
  {
    //led.reset();
    led.display_scrolling_text(buff0);
    counter = 0;
  }
  
  led.animate_display();
  delay(40);
  counter++;
}

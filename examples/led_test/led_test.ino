#include "fc16.h"

FC16 led = FC16();
/*
//Calibrated seconds for _delay_ms to use
const uint16_t SECONDS_C = 248;
const uint8_t NUM_ZERO_BLINK_CYCLES = 8;

uint8_t zero_blinks = NUM_ZERO_BLINK_CYCLES;

uint16_t count = 15; //Countdown in seconds
int8_t minutes;
int8_t seconds;
char count_str[6] = "";
char minutes_str[3] = "";
char seconds_str[3] = "";
*/
void setup()
{
  Serial.begin(9600);
  led.init();
  led.set_brightness(10);
  led.countdown(25); //In seconds
}

void loop()
{

}

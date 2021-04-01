/*
 * fc16.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: Vincent Saw
 */

#include "fc16.h"

char curr_message[BUFF_SIZE] = "";
char new_message[BUFF_SIZE] = "Testing...";
bool new_message_available = true;

FC16::FC16() {
  this->state = 255;
  this->scroll_speed = DEFAULT_SCROLL_SPEED;    // default frame delay value
  this->scroll_effect = DEFAULT_SCROLL_EFFECT;
  this->scroll_align = DEFAULT_SCROLL_ALIGN;
  this->scroll_pause = DEFAULT_SCROLL_PAUSE; // in milliseconds
}

FC16::FC16(uint8_t s_speed, textEffect_t s_effect,
textPosition_t s_align, uint16_t s_pause) {
  this->scroll_speed = s_speed;
  this->scroll_effect = s_effect;
  this->scroll_align = s_align;
  this->scroll_pause = s_pause;
}

uint8_t FC16::get_scroll_speed()        { return this->scroll_speed; }
textEffect_t FC16::get_scroll_effect()  { return this->scroll_effect; }
textPosition_t FC16::get_scroll_align() { return this->scroll_align; }
uint16_t FC16::get_scroll_pause()       { return this->scroll_pause; }
uint8_t FC16::get_state()               { return this->state; }

void FC16::set_brightness(uint8_t bn)               { P->setIntensity(bn); }
void FC16::set_static_align(textPosition_t s_align) { P->setTextAlignment(s_align); }
void FC16::set_scroll_speed(uint8_t s_speed)        { this->scroll_speed = s_speed; }
void FC16::set_scroll_effect(textEffect_t s_effect) { this->scroll_effect = s_effect; }
void FC16::set_scroll_align(textPosition_t s_align) { this->scroll_align = s_align; }
void FC16::set_scroll_pause(uint16_t s_pause)       { this->scroll_pause = s_pause; }
void FC16::set_state(uint8_t st)                    { this->state = st; }

void FC16::init() {
  P = new MD_Parola(MD_MAX72XX::FC16_HW, CS_PIN, FC16_DEVICES*4);
  P->begin();
}

void FC16::reset() {
  P->displayReset();
}

bool FC16::animate_display() {
  return P->displayAnimate();
}

void FC16::update() {
  //switch(this->state) {
    if (animate_display()) {
      if (new_message_available) {
        strcpy(curr_message, new_message);
        new_message_available = false;
        display_scrolling_text(curr_message);
      }
      reset();
    }
  //}
  //read_serial();
}

void FC16::display_static_text(const char *s) {
  P->print(s);
}

void FC16::display_static_text(const int num) {
  P->print(num);
}

void FC16::display_scrolling_text(const char *s) {
  P->displayText(s, this->scroll_align, this->scroll_speed, this->scroll_pause, this->scroll_effect, this->scroll_effect);
}

void FC16::countdown(uint16_t ct_time) {
  reset();
  set_static_align(PA_CENTER);

  display_static_text("Ready?");
  _delay_ms(400);

  char count_str[6] = "";
  char minutes_str[3] = "";
  char seconds_str[3] = "";
  
  int8_t minutes = ct_time / 60; //Ignore seconds, get # minutes
  int8_t seconds = ct_time % 60; //Take remainder of minutes
  uint8_t zero_blinks = NUM_ZERO_BLINK_CYCLES;

  for (minutes; minutes != -1; minutes--) {
    for (seconds; seconds != -1; seconds--) {
      count_str[0] = '\0';
      itoa(minutes, minutes_str, 10);
      itoa(seconds, seconds_str, 10);

      //If minutes is not two digits, append extra 0
      if (!(minutes/10)) strncat(count_str, "0", 1);

      strncat(count_str, minutes_str, 2);
      strncat(count_str, ":", 1);

      //If seconds is not two digits, append extra 0
      if (!(seconds/10)) strncat(count_str, "0", 1);

      strncat(count_str, seconds_str, 2);

      if (!minutes && seconds < 11) {
        for (int i = 0; i < 2; i++) {
          display_static_text("");
          _delay_ms(SECONDS_C >> 2); //Shift right by 1, divide by 2

          if (!seconds)   display_static_text(count_str);
          else            display_static_text(seconds);

          _delay_ms(SECONDS_C >> 2);
        }
      }
      else {
        display_static_text(count_str);
        _delay_ms(SECONDS_C);
      }
    }
    seconds = 59;
  }
  //Buzz speaker?
  for (zero_blinks; zero_blinks > 0; zero_blinks--) {
    display_static_text("");
    _delay_ms(SECONDS_C >> 2);
    display_static_text("00:00");
    _delay_ms(SECONDS_C >> 2);
  }
}

void read_serial(void)
{
  static char *cp = new_message;

  while (Serial.available())
  {
    *cp = (char)Serial.read();
    if ((*cp == '\n') || (cp - new_message >= BUFF_SIZE-2)) // end of message character or full buffer
    {
      *cp = '\0'; // end the string
      // restart the index for next filling spree and flag we have a message waiting
      cp = new_message;
      new_message_available = true;
    }
    else  // move char pointer to next position
      cp++;
  }
}

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

void FC16::set_scroll_speed(uint8_t s_speed)        { this->scroll_speed = s_speed; }
void FC16::set_scroll_effect(textEffect_t s_effect) { this->scroll_effect = s_effect; }
void FC16::set_scroll_align(textPosition_t s_align) { this->scroll_align = s_align; }
void FC16::set_scroll_pause(uint16_t s_pause)       { this->scroll_pause = s_pause; }

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
  if (animate_display()) {
    if (new_message_available) {
      strcpy(curr_message, new_message);
      new_message_available = false;
      display_scrolling_text(curr_message);
    }
    reset();
  }
  //read_serial();
}

void FC16::display_static_text(const char *s) {
  P->print(s);
}

void FC16::display_scrolling_text(const char *s) {
  P->displayText(s, this->scroll_align, this->scroll_speed, this->scroll_pause, this->scroll_effect, this->scroll_effect);
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

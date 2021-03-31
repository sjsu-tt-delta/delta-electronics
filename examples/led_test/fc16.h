/*
 * fc16.h
 *
 *  Created on: Mar 30, 2021
 *      Author: Vincent Saw
 *  For SJSU Theta Tau Delta Pledge Class's Technical Project
 */

#ifndef FC16_H_
#define FC16_H_

#include <Arduino.h>
#include <SPI.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>

using namespace std;
// Global message buffers shared by Serial and Scrolling functions
/*
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
char newMessage[BUF_SIZE] = { "Hello! Enter new message?" };
bool newMessageAvailable = true;
*/

//MD_MAX72XX::moduleType_t mod, uint8_t csPin, uint8_t numDevices = 1

const uint8_t           DEFAULT_SCROLL_SPEED    = 25;
const textEffect_t      DEFAULT_SCROLL_EFFECT   = PA_SCROLL_LEFT;
const textPosition_t    DEFAULT_SCROLL_ALIGN    = PA_LEFT;
const uint16_t          DEFAULT_SCROLL_PAUSE    = 0;                //In ms

const uint8_t           FC16_DEVICES            = 1;

//Using Arduino's Hardware SPI
const uint8_t           CS_PIN                  = 10;

const size_t            BUFF_SIZE               = 75;

extern char curr_message[BUFF_SIZE];
extern char new_message[BUFF_SIZE];
extern bool new_message_available;

void read_serial(void);

class FC16 {
    private:
        MD_Parola *P;
        uint16_t wait_time;
        uint8_t scroll_speed;
        textEffect_t scroll_effect;
        textPosition_t scroll_align;
        uint16_t scroll_pause;
    public: 
        FC16();
        FC16(uint8_t s_speed, textEffect_t s_effect,
            textPosition_t s_align, uint16_t s_pause);

        uint8_t get_scroll_speed();
        textEffect_t get_scroll_effect();
        textPosition_t get_scroll_align();
        uint16_t get_scroll_pause();

        void set_scroll_speed(uint8_t s_speed);
        void set_scroll_effect(textEffect_t s_effect);
        void set_scroll_align(textPosition_t s_align);
        void set_scroll_pause(uint16_t s_pause);

        void init();
        void reset();
        bool animate_display();
        void update();

        void display_static_text(const char *s);
        void display_scrolling_text(const char *s);

        //friend void read_serial(void);

};

#endif /* FC16_H_ */
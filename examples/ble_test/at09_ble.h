/*
 * at09_ble.h
 *
 *  Created on: Apr 3, 2021
 *      Author: Vincent Saw
 *  For SJSU Theta Tau Delta Pledge Class' Technical Project
 */

#ifndef AT09_BLE_H_
#define AT09_BLE_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

#define USE_SERIAL_MONITOR 0

class AT09_BLE {
    private:
        SoftwareSerial *sws;
    public: 
        AT09_BLE(uint8_t at9_txd, uint8_t at09_rxd);

        void begin(long baud_rate);
        int available();

        int read();
        char * read_string();

        //Sends cmd to 
        void send_cmd(const char * cmd);

        void println();

};


#endif /* AT09_BLE_H_ */

/*
 * at09_ble.cpp
 *
 *  Created on: Apr 3, 2021
 *      Author: Vincent Saw
 */

#include "at09_ble.h"

AT09_BLE::AT09_BLE(uint8_t at09_txd, uint8_t at09_rxd) {
    sws = new SoftwareSerial(at09_txd, at09_rxd);
}

void AT09_BLE::begin(long baud_rate) {
    sws->begin(baud_rate);
}

int AT09_BLE::available() {
    return sws->available();
}

int AT09_BLE::read() {
    return sws->read();
}

const char * AT09_BLE::read_string(){
  char reply[50];
  int i = 0;
  while (available()) {
    reply[i] = read();
    i++;
  }
  //end the string
  reply[i] = '\0';

    if(strlen(reply) > 0){

#if USE_SERIAL_MONITOR
        Serial.print("DATA IN: ");
        Serial.println(reply);
#endif
        char *replyPtr = reply;
        //free(replyPtr);
        //replyPtr = reply;
        return replyPtr;
    }

    return "";
}

void AT09_BLE::send_cmd(const char * cmd){
#if USE_SERIAL_MONITOR
    Serial.print("Command send :");
    Serial.println(cmd);
#endif

  sws->println(cmd);
  //wait some time
  _delay_ms(100);
  
  char reply[100];
  int i = 0;
  while (available()) {
    reply[i] = read();
    i++;
  }
  //end the string
  reply[i] = '\0';

#if USE_SERIAL_MONITOR
    Serial.print(reply);
    Serial.println("Reply end");
#endif
}
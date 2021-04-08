#include <stdlib.h>
#include "at09_ble.h"
#include "fc16.h"

FC16 led = FC16();
AT09_BLE ble_serial(2,3);

char incoming_str[21];
char *buff;

/*
const char * bluetooth_string_conversion(char * str) {
  //Copy rest of data AFTER idx 0 identifier
  char *temp = (char*)malloc(strlen(str));
  
  if (str[0] == 'a') {
    state = 0;
  }
  if (str[0] == 'b') {
    state = 1;
  }
  
  for (int i = 1; i < strlen(str); i++) {
      //Copy str into temp
      temp[i-1] = str[i];
  }
  return temp;
}*/

void setup()
{
#if USE_SERIAL_MONITOR
  Serial.begin(9600);
#endif
  ble_serial.begin(9600);
  led.init();
  ble_serial.send_cmd("AT");
  ble_serial.send_cmd("AT+ROLE0");
  ble_serial.send_cmd("AT+UUID0xFFE0");
  ble_serial.send_cmd("AT+CHAR0xFFE1");
  ble_serial.send_cmd("AT+NAMETTSign");
  led.set_brightness(10);
  led.set_static_align(PA_CENTER);
  led.display_static_text("On!");
  _delay_ms(300);
  led.display_static_text("");
  //led.reset();
  //led.display_scrolling_text("Test");
}

void loop()
{
  /*
  while (ble_serial.available()) {
    Serial.write(ble_serial.read());
  }
  */
  //readSerial();
  /*
  buff[0] = '\0';
  strcpy(buff, ble_serial.read_string());
  //Serial.println(buff);
  if (strlen(buff) > 0) {
    //led.display_static_text(buff);
    //Serial.print("Displayed: ");
    //Serial.println(buff);
    led.display_static_text(buff);
    //_delay_ms(250);
    //strcpy(new_message,buff);
  }
  //led.update();
  _delay_ms(250);
  */
  incoming_str[0] = '\0';
  buff[0] = '\0';
  //strcpy(buff, led.bluetooth_string_conversion(ble_serial.read_string()));
  strcpy(incoming_str, ble_serial.read_string());
  
  if (strlen(incoming_str) > 1) {
    buff = led.bluetooth_string_conversion(incoming_str);
    //Serial.print(buff);
    
    switch (led.get_state()) {
      case TEXT_DISPLAY: {
        led.display_static_text(buff);
        break;
      }
      case COUNTDOWN: {
        led.countdown(atoi(buff));
        break;
      }
    }
    
    //led.display_static_text(buff);
  }
  _delay_ms(250);
}

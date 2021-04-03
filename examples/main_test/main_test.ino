#include <stdlib.h>
#include "at09_ble.h"
#include "fc16.h"

FC16 led = FC16();
AT09_BLE ble_serial(2,3);

char buff[50];

void setup()
{
  Serial.begin(9600);
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
  _delay_ms(100);
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
}

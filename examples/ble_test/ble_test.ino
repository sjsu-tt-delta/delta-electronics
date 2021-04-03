#include "at09_ble.h"
//#include <SoftwareSerial.h>

//SoftwareSerial ble_serial(2,3);
AT09_BLE ble_serial(2,3);

void setup()
{
  Serial.begin(9600);
  ble_serial.begin(9600);
  ble_serial.send_cmd("AT");
  ble_serial.send_cmd("AT+ROLE0");
  ble_serial.send_cmd("AT+UUID0xFFE0");
  ble_serial.send_cmd("AT+CHAR0xFFE1");
  ble_serial.send_cmd("AT+NAMETTSign");
}

void loop()
{
  /*
  while (ble_serial.available()) {
    Serial.write(ble_serial.read());
  }
  */
  //readSerial();
  ble_serial.read_string();
  _delay_ms(500);
}

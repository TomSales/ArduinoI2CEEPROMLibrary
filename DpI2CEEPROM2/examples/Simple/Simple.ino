/*
Author: Dubravko Penezic

Version: 1.0, 2012

This code is example how to use DpI2CEEPROM2 library.

Source code is provided as is, without any warranty.

Distributetd under CC BY v 3.0

http://pcb.daince.net/doku.php?id=arduino_code
*/

#include <Wire.h>

#include <DpI2CEEPROM2.h>

//EEPROM address of ATMEL AT24Cxxx I2C EEPROM
#define EEPROM_ADDR 0x50

// initialize address of EEPROM
DpI2CEEPROM2 EP(EEPROM_ADDR);

void setup(void) {
  Serial.begin(115200);
  Serial.println("DpI2CEEPROM2 V 1.0");

  Wire.begin();
  
  int varFlo = 5671;
  Serial.print("Init value of variable ");
  Serial.println(varFlo,DEC);

  Serial.println("Write value to EEPROM");
  EP.writeInt(6000,varFlo);

  varFlo=0;
  Serial.print("Value of variable is clear ");
  Serial.println(varFlo, DEC);

  delay(10000);
  
  Serial.println("Read variable value from  EEPROM");
  varFlo = EP.readInt(6000);

  Serial.print("Velue of variable readed from EEPROM ");
  Serial.println(varFlo, DEC);
}

void loop(void) {

}

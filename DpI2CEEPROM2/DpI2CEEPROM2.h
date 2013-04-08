/*
Author: Dubravko Penezic

Version: 1.0, 2012

Modified Library (3/29/2013 by Tom Sales) to incorporate the following:
1. Adjust for the 64 byte page boundary of the 32K chip in the DpI2CEEPROM library.
2. Enable reading and writing large byte blocks to any location up to the top memory address.

This was accomplished by merging this library and the M24LC256 library by James Coliz, Jr. 2011.

The modified library functions as both authors intended, but in a single program.

DpI2CEEPROM2.h - Library definition of DpI2CEEPROM class

DpI2CEEPROM2 Arduino library provides function for writing and
reading different type of data to I2C EEPROM. (AT24C*).

Description from maniacbug:
"Create one instance of this class for each chip in your circuit.  This allows you to have up to 8 of these active at any time. This class is optimized to take advantage of the page size of the chip.  The chip has a 5msec write cycle now matter how many bytes you push it, up to its page size (64 bytes for 24LC256.  To get higher throughput, increase the size of the Wire buffer by increasing BUFFER_LENGTH in Wire.h and TWI_BUFFER_LENGTH in utility/twi.h.  Increase them to 34 for 32-byte writes, and to 66 for 64-byte writes." 

Some code was copied from http://arduino.cc/playground/Main/LibraryForI2CEEPROM by Rob Tillaart
Source code is provided as is, without any warranty.

Some code was copied from https://github.com/maniacbug/M24LC256/blob/master/M24LC256.cpp

Distributed under CC BY v 3.0

original code http://pcb.daince.net/doku.php?id=arduino_code
*/
#ifndef DpI2CEEPROM2_h
#define DpI2CEEPROM2_h

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <Wire.h>

class DpI2CEEPROM2 {
  public:

    // on initialization define address of EEPROM on I2C
    // caddr - address
    DpI2CEEPROM2(byte caddr);

    // write boolean value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeBoolean(unsigned int maddr, boolean val);

    // write byte value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeByte(unsigned int maddr, byte val);

    // write char value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeChar(unsigned int maddr, char val);
    
    // write char array value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeCharArry(unsigned int maddr, char val[]);
    
    // write int value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeInt(unsigned int maddr, int val);
    
    // write unsignet int value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeUnsignedInt(unsigned int maddr, unsigned int val);
    
    // write long value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeLong(unsigned int maddr, long val);
    
    // write unsigned long value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeUnsignedLong(unsigned int maddr, unsigned long val);
    
    // write float value to I2C EEPROM
    // maddr - memory address
    // val - value
    void writeFloat(unsigned int maddr, float val);

    // read and return boolean value to I2C EEPROM
    // maddr - memory address
    boolean readBoolean(unsigned int maddr);

    // read and return byte value to I2C EEPROM
    // maddr - memory address
    byte readByte(unsigned int maddr);
    
    // read and return char value to I2C EEPROM
    // maddr - memory address
    char readChar(unsigned int maddr);
    
    // read and return char array value to I2C EEPROM
    // maddr - memory address
    // val - return char array
    // len - length of char array
    void readCharArry(unsigned int maddr, char val[], unsigned int len);
    
    // read and return int value to I2C EEPROM
    // maddr - memory address
    int readInt(unsigned int maddr);
    
    // read and return unsigned int value to I2C EEPROM
    // maddr - memory address
    unsigned int readUnsignedInt(unsigned int maddr);
    
    // read and return long value to I2C EEPROM
    // maddr - memory address
    long readLong(unsigned int maddr);
    
    // read and return unsigned long value to I2C EEPROM
    // maddr - memory address
    unsigned long readUnsignedLong(unsigned int maddr);
    
    // read and return float value to I2C EEPROM
    // maddr - memory address
    float readFloat(unsigned int maddr);
    
    void write(unsigned int location, void* buf, unsigned int len);
    
    unsigned int WriteBlock(unsigned int maddr, unsigned int length, byte * data);

    unsigned int read(unsigned int maddr, void* buf, unsigned int len);

    unsigned int ReadBlock(unsigned int maddr, unsigned int length, byte * data);


    // write block of bytes to defined address
    // maddr - memory address
    // buffer - pointer to memory location of variable with data
    // length - number of bytes in block
    //void WriteBlock(unsigned int maddr, byte * buffer, unsigned int length);
    
    // read block of bytes from defined address
    // maddr - memory address
    // buffer - pointer to memory location of variable with data
    // length - number of bytes in block
    // variable buffer must be large enough to hold length int 
    //void ReadBlock(unsigned int maddr, byte * buffer, unsigned int length);
    
  private:
    byte _caddr;
    
    byte _valBa;
    char _valCh;
    int _valIn;
    unsigned int _valUnIn;
    long _valLo;
    unsigned long _valUnLo;
    float _valFl;
    
    byte _c;
};

#endif


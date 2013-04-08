/*
Author: Dubravko Penezic

Version: 1.0, 2012
Modified Library (3/29/2013 by Tom Sales) to incorporate the following:
1. Adjust write function for the 64 byte page boundary of the 32K chip in the DpI2CEEPROM library.
2. Enable reading and writing large byte blocks to any location up to the top memory address.

This was accomplished by merging this library and the M24LC256 library by James Coliz, Jr. 2011.

The modified library functions as both authors intended, but in a single program.

DpI2CEEPROM2.cpp - Library source code

DpI2CEEPROM2 Arduino library provide function writing and
reading different type of data to I2C EEPROM. (AT24C*).

Description from maniacbug:
"Create one instance of this class for each chip in your circuit.  This allows you to have up to 8 of these active at any time. This class is optimized to take advantage of the page size of the chip.  The chip has a 5msec write cycle now matter how many bytes you push it, up to its page size (64 bytes for 24LC256.  To get higher throughput, increase the size of the Wire buffer by increasing BUFFER_LENGTH in Wire.h and TWI_BUFFER_LENGTH in utility/twi.h.  Increase them to 34 for 32-byte writes, and to 66 for 64-byte writes." 

Some code was copied from http://arduino.cc/playground/Main/LibraryForI2CEEPROM Rob Tillaart

Source code is provided as is, without any warranty.

Distributed under CC BY v 3.0

Original code http://pcb.daince.net/doku.php?id=arduino_code
*/
#if ARDUINO >= 100
    #include "Arduino.h"   
#else
extern "C" {
    #include "WConstants.h"
}
#endif

#include "DpI2CEEPROM2.h"

#if ( BUFFER_LENGTH < 34 ) || ( TWI_BUFFER_LENGTH < 34 )
const int page_size = 0x10;
#elif ( BUFFER_LENGTH < 66 ) || ( TWI_BUFFER_LENGTH < 66 )
const int page_size = 0x20;
#else
const int page_size = 0x40;
#endif

// on initialization define address of EEPROM on I2C
// caddr - address
DpI2CEEPROM2::DpI2CEEPROM2(byte caddr) {
  _caddr = caddr;
}

// write boolean value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeBoolean(unsigned int maddr, boolean val){
  if(val) writeByte(maddr,1);
  else writeByte(maddr,0);
}

// write byte value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeByte(unsigned int maddr, byte val) {
  write(maddr, (byte *) &val, 1);
}

// write char value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeChar(unsigned int maddr, char val){
  write(maddr, (byte *) &val, 1);
}

// write char array value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeCharArry(unsigned int maddr, char val[]){
  write(maddr, (byte *) &val, strlen(val));
}

// write int value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeInt(unsigned int maddr, int val){
  write(maddr, (byte *) &val, 2);
}

// write unsignet int value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeUnsignedInt(unsigned int maddr, unsigned int val){
  write(maddr, (byte *) &val, 2);
}

// write long value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeLong(unsigned int maddr, long val){
  write(maddr, (byte *) &val, 4);
}

// write unsigned long value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeUnsignedLong(unsigned int maddr, unsigned long val){
  write(maddr, (byte *) &val, 4);
}

// write float value to I2C EEPROM
// maddr - memory address
// val - value
void DpI2CEEPROM2::writeFloat(unsigned int maddr, float val){
  write(maddr, (byte *) &val, 4);
}

// read and return boolean value to I2C EEPROM
// maddr - memory address
boolean DpI2CEEPROM2::readBoolean(unsigned int maddr) {
  if(readByte(maddr) == 1) return true;
  return false;
}

// read and return byte value to I2C EEPROM
// maddr - memory address
byte DpI2CEEPROM2::readByte(unsigned int maddr) {
  _valBa=0;
  read(maddr, (byte *) &_valBa, 1);
  return _valBa;
}

// read and return char value to I2C EEPROM
// maddr - memory address
char DpI2CEEPROM2::readChar(unsigned int maddr){
  _valCh=0;
  read(maddr, (byte *) &_valCh, 1);
  return _valCh;
}

// read and return char array value to I2C EEPROM
// maddr - memory address
// val - return char array
// len - length of char array
void DpI2CEEPROM2::readCharArry(unsigned int maddr, char val[], unsigned int len) {
  read(maddr, (byte *) &val, len);
}

// read and return int value to I2C EEPROM
// maddr - memory address
int DpI2CEEPROM2::readInt(unsigned int maddr) {
  _valIn=0;
  read(maddr, (byte *) &_valIn, 2);
  return _valIn;
}

// read and return unsigned int value to I2C EEPROM
// maddr - memory address
unsigned int DpI2CEEPROM2::readUnsignedInt(unsigned int maddr) {
  _valUnIn=0;
  read(maddr, (byte *) &_valUnIn, 2);
  return _valUnIn;
}

// read and return long value to I2C EEPROM
// maddr - memory address
long DpI2CEEPROM2::readLong(unsigned int maddr) {
  _valLo=0;
  read(maddr, (byte *) &_valLo, 4);
  return _valLo;
}

// read and return unsigned long value to I2C EEPROM
// maddr - memory address
unsigned long DpI2CEEPROM2::readUnsignedLong(unsigned int maddr) {
  _valUnLo=0;
  read(maddr, (byte *) &_valUnLo, 4);
  return _valUnLo;
}

// read and return float value to I2C EEPROM
// maddr - memory address
float DpI2CEEPROM2::readFloat(unsigned int maddr) {
  _valFl=0;
  read(maddr, (byte *) &_valFl, 4);
  return _valFl;
}
// write bytes to defined address
// maddr - memory address
// buf - pointer to memory location of variable with data
// len - number of bytes in block
void DpI2CEEPROM2::write(unsigned int location, void* buf, unsigned int len)
{
    unsigned int remaining = len;
    byte * next_in = reinterpret_cast< byte *>(buf);
    unsigned int next_out = location;

    if ( location & (page_size-1) )
    {
        unsigned int chunk_length = min(remaining, page_size - ( location & (page_size-1) ));

        unsigned int written = WriteBlock( next_out, chunk_length, next_in );
        remaining -= written;
        next_in += written;
        next_out += written;
    }

    while ( remaining )
    {
        unsigned int written = WriteBlock( next_out, remaining, next_in );
        remaining -= written;
        next_in += written;
        next_out += written;
    }
}


unsigned int DpI2CEEPROM2:: WriteBlock(unsigned int maddr, unsigned int length, byte * data)
{
    unsigned int bytes_written = min(length,page_size);

    Wire.beginTransmission(_caddr);  // START condition
    Wire.write((byte)(maddr >> 8));
    Wire.write((byte)(maddr & 0xff));
    Wire.write(data,bytes_written);
    Wire.endTransmission();
    delay(5);  // 5msec write cycle time
    return bytes_written;
}

unsigned int DpI2CEEPROM2::read(unsigned int maddr, void* buf, unsigned int len)
{
    unsigned int bytes_received = 0;
    unsigned int remaining = len;
    byte * next_memory = reinterpret_cast< byte *>(buf);
    unsigned int next_chip = maddr;

    // First, deal with page boundaries.  If location is NOT on an even 16 bytes,
    // we'll want to write out only enough to get to the end of this page.

    if (maddr & 0xf )
    {
        unsigned int chunk_length = min( remaining, 0x10 - (maddr & 0xf ) );

        unsigned int chunk_received = ReadBlock(next_chip,chunk_length,next_memory);
        remaining -= chunk_received;
        next_memory += chunk_received;
        next_chip += chunk_received;
        bytes_received += chunk_received;
    }

    while ( remaining )
    {
        unsigned int chunk_received = ReadBlock(next_chip,remaining,next_memory);
        remaining -= chunk_received;
        next_memory += chunk_received;
        next_chip += chunk_received;
        bytes_received += chunk_received;
        if ( ! chunk_received ) // if we don't get any data, fall out so we don't hang here forever.
            break;
    }

    return bytes_received;
}

unsigned int  DpI2CEEPROM2::ReadBlock(unsigned int maddr, unsigned int length, byte * data)
{
    unsigned int bytes_received = 0;
    unsigned int bytes_requested = min(length,16);

    Wire.beginTransmission(_caddr);  // START condition
    Wire.write((byte)(maddr >> 8));
    Wire.write((byte)(maddr & 0xff));
    Wire.endTransmission();
    Wire.requestFrom(_caddr, bytes_requested);
    unsigned int remaining = bytes_requested;
    byte * next = data;
    while (Wire.available() && remaining--)
    {
        *next++ = Wire.read();
        ++bytes_received;
    }
    delay(1);
    return bytes_received;
}

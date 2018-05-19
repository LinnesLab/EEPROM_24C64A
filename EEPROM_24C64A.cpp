/*
 
 FILENAME:		EEPROM_24C64A.cpp
 AUTHOR:		Orlando S. Hoilett
 EMAIL:			ohoilett@purdue.edu
 VERSION:		0.1
 
 
 DESCRIPTION
 This file provides the class definitions for controlling the 24C64A I2C
 Serial EEPROM. The library allows for single byte write and single byte read.
 The 24C64A is an EEPROM controlled via I2C. It has 64k memory stored in 8,
 8192 byte registers.
 
 
 A FEW INSTRUCTIONS
 All methods are defined and coded according to the instructions give in
 the 24C64A datashee from Fremont Micro Devices Inc (C) 2009. All references
 to the datasheet refer to the 2009 copyrighted version.The datasheet is
 referenced in the code so that the user can have further consult if more
 information is needed.
 
 A copy of the datasheet is included in the software download.
 
 All references to "the device" refer to the 24C64A Two-Wire Serial EEPROM
 from Fremont Micro Devices Inc.

 
 UPDATES
 Version 0.0
 2016/01/25:1902>
 			Started writing the code and making a few basic definitions. This
 			is a non-functional/non-tested version.
 2016/02/11:2208>
 			Finished functioning version.
 Version 0.1
 2016/02/16:2343>
 			Starting making changes to curReg variable to make it easier to
 			sequentially write registers.

 
 DISCLAIMER
 The MIT License (MIT)
 
 (C) Copyright 01/25/2016 by authors
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 */


#include "EEPROM_24C64A.h"


//Default Constructor
//EEPROM_24C64A::EEPROM_24C64A()
//
//Initializes class object. Provides default I2C address for device as given in
//the datasheet while other variables are set to 0. Please consult pages 1, 3,
//and 4 of the datasheet for more information.
EEPROM_24C64A::EEPROM_24C64A() : addr(EEPROM_24C64A_DEFAULT_ADDRESS), wp(0), curReg(0)
{
}


//Default Constructor
//EEPROM_24C64A::EEPROM_24C64A(uint8_t addr)
//
//@param addr               Device address
//
//Initializes class object with a given address. All other class variables are
//set to 0. Please consult pages 1, 3, and 4 of the datasheet for more information.
EEPROM_24C64A::EEPROM_24C64A(uint8_t addr) : addr(addr), wp(0), curReg(0)
{
}


//Default Constructor
//EEPROM_24C64A::EEPROM_24C64A(uint8_t addr, uint8_t wp)
//
//@param addr               Device address
//
//@param wp                 IO pin to protect device from being written to
//
//Initializes class object with given I2C address and IO pin for digitally
//controlling write protection. curReg is set to 0. Please consult pages 1, 3,
//and 4 of the datasheet for more information.
EEPROM_24C64A::EEPROM_24C64A(uint8_t addr, uint8_t wp) : addr(addr), wp(wp), curReg(0)
{
}


//void EEPROM_24C64A::write(uint16_t reg, uint8_t data)
//
//@param reg                Device register that data will be written to
//
//@param data               Data that will be stored in register
//
//Utilizes Arduino Wire library for I2C communication. First, a two byte word is
//written to the device. This two byte word determines the register that the data
//will be written to.
//
//8192 registers can be programmed directly by the user by defining the 13 LSBs
//of the "reg" variable. The 3 MSBs of the register cannot be user-programmed.
//These are auto-incremented by the device.
//
//Also updates the "curReg" variable to help the user know which register was last
//written to.
//
//Please consult pages 5 and 6 for more information.
void EEPROM_24C64A::write(uint16_t reg, uint8_t data)
{
    Wire.beginTransmission(addr); //first writes device address
    Wire.write(reg >> 8);
    Wire.write(reg & 0xFF);
    Wire.write(data);
    Wire.endTransmission();
    delay(5);
    curReg = reg + 1;
}


//void EEPROM_24C64A::write(uint8_t reg_low, uint8_t reg_high, uint8_t data)
//
//@param reg_low            Low register byte word that data will be written to
//
//@param reg_high           High register byte word that data will be written to
//
//@param data               Data that will be stored in register
//
//Utilizes Arduino Wire library for I2C communication. First, a two byte word is
//written to the device. This two byte word determines the register that the data
//will be written to.
//
//8192 registers can be programmed directly by the user by defining the 13 LSBs
//of the "reg" variable. The 3 MSBs of the register cannot be user-programmed.
//These are auto-incremented by the device.
//
//Also updates the "curReg" variable to help the user know which register was last
//written to.
//
//Please consult pages 5 and 6 for more information.
void EEPROM_24C64A::write(uint8_t reg_low, uint8_t reg_high, uint8_t data)
{
    Wire.beginTransmission(addr); //first writes device address
    Wire.write(reg_high);
    Wire.write(reg_low);
    Wire.write(data);
    Wire.endTransmission();
    delay(5);
    curReg = ((reg_high << 8) | reg_low) + 1;
}


//uint8_t EEPROM_24C64A::read()
//
//@return                   returns 1 byte of data that was read from the device
//
//const modifier            prevents updaing of private variables
//
//Utilizes Arduino Wire library for I2C communication. 1 byte of data is requested
//from teh device and returned to the user.
//
//After a read, the internal counter of the device increments by 1. Therefore,
//the curReg variable also increments by one. To indicate to the user which
//register would be read from next.
//
//Please consult pages 5-7 of the datasheet for more information.
uint8_t EEPROM_24C64A::read()
{
    Wire.requestFrom(addr, 1);
    
    uint8_t inData = 0;
    
    while (Wire.available()) //what if more than one byte is available?
    {
        inData = Wire.read();
    }
    
    curReg += 1;
    return inData;
}


//uint8_t EEPROM_24C64A::read(uint8_t reg_low, uint8_t reg_high)
//
//@param reg_low            Low register byte word that data will be read from
//
//@param reg_high           High register byte word that data will be read from
//
//@return                   returns 1 byte of data that was read from the device
//
//const modifier            prevents updaing of private variables
//
//Utilizes Arduino Wire library for I2C communication. First, a write protocol
//is initiated without the writing of data to the resiter. The write protocol
//sets the register that will be read. Then, a read protocol is executed and 1
//byte of data is requested from the device and returned to the user.
//
//After a read, the internal counter of the device increments by 1. Therefore,
//the curReg variable also increments by one. To indicate to the user which
//register would be read from next.
//
//Please consult pages 5-7 of the datasheet for more information.
uint8_t EEPROM_24C64A::read(uint8_t reg_low, uint8_t reg_high)
{
    Wire.beginTransmission(addr);
    Wire.write(reg_high);
    Wire.write(reg_low);
    Wire.endTransmission();
    delay(5);
    
    Wire.requestFrom(addr, 1);
    
    uint8_t inData = 0;
    
    while (Wire.available())
    {
        inData = Wire.read();
    }
    
    curReg = ((reg_high << 8) | reg_low) + 1;
    return inData;
}


//uint8_t EEPROM_24C64A::read(uint16_t reg)
//
//@param reg                Device register that data will be written from
//
//@return                   returns 1 byte of data that was read from the device
//
//const modifier            prevents updaing of private variables
//
//Utilizes Arduino Wire library for I2C communication. First, a write protocol
//is initiated without the writing of data to the resiter. The write protocol
//sets the register that will be read. Then, a read protocol is executed and 1
//byte of data is requested from the device and returned to the user.
//
//After a read, the internal counter of the device increments by 1. Therefore,
//the curReg variable also increments by one. To indicate to the user which
//register would be read from next.
//
//Please consult pages 5-7 of the datasheet for more information.
uint8_t EEPROM_24C64A::read(uint16_t reg)
{
    Wire.beginTransmission(addr);
    Wire.write(reg >> 8);
    Wire.write(reg & 0xFF);
    Wire.endTransmission();
    delay(5);
    
    Wire.requestFrom(addr, 1);
    
    uint8_t inData = 0;
    
    while (Wire.available())
    {
        inData = Wire.read();
    }
    
    curReg = reg + 1;
    return inData;
}


//uint16_t EEPROM_24C64A::getCurReg() const
//
//@return                   returns the 2 byte data word representing the current
//                          internal counter location of the device
//
//const modifier            prevents updaing of private variables
//
//Returns the current register that the device's internal counter is set to. This
//is determined by monitoring the read and write instructions.
uint16_t EEPROM_24C64A::getCurReg() const
{
    return curReg;
}




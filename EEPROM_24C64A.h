/*
 
 FILENAME:		EEPROM_24C64A.h
 AUTHOR:		Orlando S. Hoilett
 EMAIL:			orlandohoilett@gmail.com
 
 
 Please see .cpp file for extended descriptions, instructions, and version updates
 
  
 
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


#ifndef EEPROM_24C64A_H
#define EEPROM_24C64A_H

#include "Arduino.h"
#include "Wire.h"


//Default address for the SOT23-5 package of the device because the address pins
//A0, A1, and A2 are not avaiable.
const uint8_t EEPROM_24C64A_DEFAULT_ADDRESS = B1010000;


class EEPROM_24C64A
{
private:
    
    uint8_t addr; //device address
    uint8_t wp; //the write protect pin is not used in the SOT23-5 package
    uint16_t curReg; //to help the user keep track of the last reigster written to

    
public:
    
    //Constructors
    EEPROM_24C64A();
    EEPROM_24C64A(uint8_t addr);
    EEPROM_24C64A(uint8_t addr, uint8_t wp);
    
    //storing data on the EEPROM
    void write(uint16_t reg, uint8_t data);
    void write(uint8_t reg_low, uint8_t reg_high, uint8_t data);
    
    //reading data from the EEPROM
    uint8_t read();
    uint8_t read(uint16_t reg);
    uint8_t read(uint8_t reg_low, uint8_t reg_high);
    
    uint16_t getCurReg() const;

};

#endif

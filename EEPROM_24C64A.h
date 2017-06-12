/*
 * FILENAME:	24C64A.h
 * AUTHOR:      Orlando S. Hoilett
 * EMAIL:       ohoilett@purdue.edu
 * VERSION:     0.1
 
 
 * DESCRIPTION
 * This file provides the class declaration for controlling the 24C64A I2C
 * Serial EEPROM. The library allows for single byte write and single byte read.
 * The 24C64A is an EEPROM controlled via I2C. It has 64k memory stored in 8,
 * 8192 byte registers.
 
 
 * A FEW INSTRUCTIONS
 * All methods are defined and coded according to the instructions give in
 * the 24C64A datashee from Fremont Micro Devices Inc (C) 2009. All references
 * to the datasheet refer to the 2009 copyrighted version.The datasheet is
 * referenced in the code so that the user can have further consult if more
 * information is needed.
 * 
 * A copy of the datasheet is included in the software download.
 *
 * All references to "the device" refer to the 24C64A Two-Wire Serial EEPROM
 * from Fremont Micro Devices Inc.
 
 
 * UPDATES
 * Version 0.0
 * 2016/01/25:1902>
 *			Started writing the code and making a few basic definitions. This
 *			is a non-functional/non-tested version.
 * 2016/02/11:2208>
 *          Finished functioning version.
 * Version 0.1
 * 2016/02/16:2343>
 *          Starting making changes to curReg variable to make it easier to
 *          sequentially write registers.
 
 
 * DISCLAIMER
 * Copyright (C) Linnes Lab 2016, Purdue University, All rights reserved
 *
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
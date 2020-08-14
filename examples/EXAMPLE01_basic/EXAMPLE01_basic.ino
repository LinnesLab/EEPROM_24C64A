#include <EEPROM_24C64A.h>


EEPROM_24C64A myEEPROM = EEPROM_24C64A();


void setup()
{
  Wire.begin();
  Serial.begin(9600);


  myEEPROM.write(1,0);
  myEEPROM.write(0,0);

  Wire.requestFrom(addr, 100);
  
  uint8_t inData = 0;
  
  while (Wire.available())
  {
    inData = Wire.read();
    Serial.println(inData);
  }

  Serial.println(myEEPROM.read());
}


void loop()
{
  
}

#pragma once


#include "Wire.h"


#include <Arduino.h>

//  0.087890625;
const float   AS5600_RAW_TO_DEGREES     = 360.0 / 4096;
//  0.00153398078788564122971808758949;
const float   AS5600_RAW_TO_RADIANS     = PI * 2.0 / 4096;
class AMS_5600
{
public:
  AMS_5600(void);
  int getAddress();
  int setAddress(int address);
  void setAddTemp(int address);
  word setMaxAngle(word newMaxAngle = -1);
  word getMaxAngle();

  word setStartPosition(word startAngle = -1);
  word getStartPosition();

  word setEndPosition(word endAngle = -1);
  word getEndPosition();

  word getRawAngle();
  float getAngle();
  word getScaledAngle();

  int detectMagnet();
  int getMagnetStrength();
  int getAgc();
  word getMagnitude();

  int getBurnCount();
  int burnAngle();
  int burnMaxAngleAndConfig();
  void setOutPut(uint8_t mode);

private:
  int _ams5600_Address;

  word _rawStartAngle;
  word _zPosition;
  word _rawEndAngle;
  word _mPosition;
  word _maxAngle;

  /* Registers */
  int _zmco;
  int _zpos_hi; /*zpos[11:8] high nibble  START POSITION */
  int _zpos_lo; /*zpos[7:0] */
  int _mpos_hi; /*mpos[11:8] high nibble  STOP POSITION */
  int _mpos_lo; /*mpos[7:0] */
  int _mang_hi; /*mang[11:8] high nibble  MAXIMUM ANGLE */
  int _mang_lo; /*mang[7:0] */
  int _conf_hi;
  int _conf_lo;
  int _raw_ang_hi;
  int _raw_ang_lo;
  int _ang_hi;
  int _ang_lo;
  int _stat;
  int _agc;
  int _mag_hi;
  int _mag_lo;
  int _i2c_addr;
  int _i2c_updt;
  int _burn;
  int _burn_data;

  int readOneByte(int in_adr);
  word readTwoBytes(int in_adr_hi, int in_adr_lo);
  void writeOneByte(int adr_in, int dat_in);
};


AMS_5600::AMS_5600()
{
  /* set i2c address */
  _ams5600_Address = 0x40;

  /* load register values */
  /* c++ class forbids pre loading of variables */
  _zmco = 0x00;
  _zpos_hi = 0x01;
  _zpos_lo = 0x02;
  _mpos_hi = 0x03;
  _mpos_lo = 0x04;
  _mang_hi = 0x05;
  _mang_lo = 0x06;
  _conf_hi = 0x07;
  _conf_lo = 0x08;
  _raw_ang_hi = 0x0c;
  _raw_ang_lo = 0x0d;
  _ang_hi = 0x0e;
  _ang_lo = 0x0f;
  _stat = 0x0b;
  _agc = 0x1a;
  _mag_hi = 0x1b;
  _mag_lo = 0x1c;
  _i2c_addr = 0x20;
  _i2c_updt = 0x21;
  _burn = 0xff;
  _burn_data = 0x40;
}
/* mode = 0, output PWM, mode = 1 output analog (full range from 0% to 100% between GND and VDD */
void AMS_5600::setOutPut(uint8_t mode)
{
  uint8_t config_status;
  config_status = readOneByte(_conf_lo);
  if (mode == 1)
  {
    config_status = config_status & 0xcf;
  }
  else
  {
    uint8_t config_status;
    config_status = readOneByte(_conf_lo);
    if (mode == 1)
    {
      config_status = config_status & 0xcf;
    }
    else
    {
      config_status = config_status & 0xef;
    }
    writeOneByte(_conf_lo, lowByte(config_status));
  }
}
/****************************************************
  Method: AMS_5600
  In: none
  Out: i2c address of AMS 5600
  Description: returns i2c address of AMS 5600
****************************************************/
int AMS_5600::getAddress()
{
  return _ams5600_Address;
}
/****************************************************
  Method: AMS_5600
  In: address
  Out: i2c set address of AMS 5600
  Description: set i2c address of actual AMS 5600
****************************************************/
int AMS_5600::setAddress(int address)
{
 int oldadd=_ams5600_Address;

  writeOneByte(_i2c_addr, address<<1);
 writeOneByte(_i2c_updt, address<<1);
 _ams5600_Address=address;
  //writeOneByte(_burn, _burn_data);
  int res=burnMaxAngleAndConfig();
  switch(res){
    case -1:
     Serial.println("Limit exceeded");_ams5600_Address=oldadd;return(-1);         
    break;
   
    case 1:
       Serial.print("Success AS reprogrammed to :0x");    Serial.print(address,HEX);
    break;
    case -2:
     Serial.println("Angle too small");_ams5600_Address=oldadd;return(-1); 
    break;
    default:
     Serial.println("Pb to programm AS");_ams5600_Address=oldadd;return(-1); 
     break;
  }
  
  _ams5600_Address=address;

  return address;
}

void AMS_5600::setAddTemp(int address)
{
   _ams5600_Address = address;

}
/*******************************************************
  Method: setMaxAngle
  In: new maximum angle to set OR none
  Out: value of max angle register
  Description: sets a value in maximum angle register.
  If no value is provided, method will read position of
  magnet.  Setting this register zeros out max position
  register.
*******************************************************/
word AMS_5600::setMaxAngle(word newMaxAngle)
{
  word retVal;
  if (newMaxAngle == -1)
  {
    _maxAngle = getRawAngle();
  }
  else
    _maxAngle = newMaxAngle;

  writeOneByte(_mang_hi, highByte(_maxAngle));
  delay(2);
  writeOneByte(_mang_lo, lowByte(_maxAngle));
  delay(2);

  retVal = readTwoBytes(_mang_hi, _mang_lo);
  return retVal;
}

/*******************************************************
  Method: getMaxAngle
  In: none
  Out: value of max angle register
  Description: gets value of maximum angle register.
*******************************************************/
word AMS_5600::getMaxAngle()
{
  return readTwoBytes(_mang_hi, _mang_lo);
}

/*******************************************************
  Method: setStartPosition
  In: new start angle position
  Out: value of start position register
  Description: sets a value in start position register.
  If no value is provided, method will read position of
  magnet.  
*******************************************************/
word AMS_5600::setStartPosition(word startAngle)
{
  if (startAngle == -1)
  {
    _rawStartAngle = getRawAngle();
  }
  else
    _rawStartAngle = startAngle;

  writeOneByte(_zpos_hi, highByte(_rawStartAngle));
  delay(2);
  writeOneByte(_zpos_lo, lowByte(_rawStartAngle));
  delay(2);
  _zPosition = readTwoBytes(_zpos_hi, _zpos_lo);

  return (_zPosition);
}

/*******************************************************
  Method: getStartPosition
  In: none
  Out: value of start position register
  Description: gets value of start position register.
*******************************************************/
word AMS_5600::getStartPosition()
{
  return readTwoBytes(_zpos_hi, _zpos_lo);
}

/*******************************************************
  Method: setEndtPosition
  In: new end angle position
  Out: value of end position register
  Description: sets a value in end position register.
  If no value is provided, method will read position of
  magnet.  
*******************************************************/
word AMS_5600::setEndPosition(word endAngle)
{
  if (endAngle == -1)
    _rawEndAngle = getRawAngle();
  else
    _rawEndAngle = endAngle;

  writeOneByte(_mpos_hi, highByte(_rawEndAngle));
  delay(2);
  writeOneByte(_mpos_lo, lowByte(_rawEndAngle));
  delay(2);
  _mPosition = readTwoBytes(_mpos_hi, _mpos_lo);

  return (_mPosition);
}

/*******************************************************
  Method: getEndPosition
  In: none
  Out: value of end position register
  Description: gets value of end position register.
*******************************************************/
word AMS_5600::getEndPosition()
{
  word retVal = readTwoBytes(_mpos_hi, _mpos_lo);
  return retVal;
}

/*******************************************************
  Method: getRawAngle
  In: none
  Out: value of raw angle register
  Description: gets raw value of magnet position.
  start, end, and max angle settings do not apply
*******************************************************/
word AMS_5600::getRawAngle()
{
  return readTwoBytes(_raw_ang_hi, _raw_ang_lo);
}

float AMS_5600::getAngle()
{
  return((float)(getRawAngle())*AS5600_RAW_TO_DEGREES);
  
}
/*******************************************************
  Method: getScaledAngle
  In: none
  Out: value of scaled angle register
  Description: gets scaled value of magnet position.
  start, end, or max angle settings are used to 
  determine value
*******************************************************/
word AMS_5600::getScaledAngle()
{
  return readTwoBytes(_ang_hi, _ang_lo);
}

/*******************************************************
  Method: detectMagnet
  In: none
  Out: 1 if magnet is detected, 0 if not
  Description: reads status register and examines the 
  MH bit
*******************************************************/
int AMS_5600::detectMagnet()
{
  int magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = magnet detected*/
  /* ML high = AGC Maximum overflow, magnet to weak*/
  /* MH high = AGC minimum overflow, Magnet to strong*/
  magStatus = readOneByte(_stat);

  if (magStatus & 0x20)
    retVal = 1;

  return retVal;
}

/*******************************************************
  Method: getMagnetStrength
  In: none
  Out: 0 if no magnet is detected
       1 if magnet is to weak
       2 if magnet is just right
       3 if magnet is to strong
  Description: reads status register andexamins the MH,ML,MD bits
*******************************************************/
int AMS_5600::getMagnetStrength()
{
  int magStatus;
  int retVal = 0;
  /*0 0 MD ML MH 0 0 0*/
  /* MD high = magnet detected */
  /* ML high = AGC Maximum overflow, magnet to weak*/
  /* MH high = AGC minimum overflow, Magnet to strong*/
  magStatus = readOneByte(_stat);
  if (detectMagnet() == 1)
  {
    retVal = 2; /*just right */
    if (magStatus & 0x10)
      retVal = 1; /*to weak */
    else if (magStatus & 0x08)
      retVal = 3; /*to strong */
  }

  return retVal;
}

/*******************************************************
  Method: get Agc
  In: none
  Out: value of AGC register
  Description: gets value of AGC register.
*******************************************************/
int AMS_5600::getAgc()
{
  return readOneByte(_agc);
}

/*******************************************************
  Method: getMagnitude
  In: none
  Out: value of magnitude register
  Description: gets value of magnitude register.
*******************************************************/
word AMS_5600::getMagnitude()
{
  return readTwoBytes(_mag_hi, _mag_lo);
}

/*******************************************************
  Method: getBurnCount
  In: none
  Out: value of zmco register
  Description: determines how many times chip has been
  permanently written to. 
*******************************************************/
int AMS_5600::getBurnCount()
{
  return readOneByte(_zmco);
}

/*******************************************************
  Method: burnAngle
  In: none
  Out: 1 success
      -1 no magnet
      -2 burn limit exceeded
      -3 start and end positions not set (useless burn)
  Description: burns start and end positions to chip.
  THIS CAN ONLY BE DONE 3 TIMES
*******************************************************/
int AMS_5600::burnAngle()
{
  int retVal = 1;
  _zPosition = getStartPosition();
  _mPosition = getEndPosition();
  _maxAngle = getMaxAngle();

  if (detectMagnet() == 1)
  {
    if (getBurnCount() < 3)
    {
      if ((_zPosition == 0) && (_mPosition == 0))
        retVal = -3;
      else
        writeOneByte(_burn, 0x80);
    }
    else
      retVal = -2;
  }
  else
    retVal = -1;

  return retVal;
}

/*******************************************************
  Method: burnMaxAngleAndConfig
  In: none
  Out: 1 success
      -1 burn limit exceeded
      -2 max angle is to small, must be at or above 18 degrees
  Description: burns max angle and config data to chip.
  THIS CAN ONLY BE DONE 1 TIME
*******************************************************/
int AMS_5600::burnMaxAngleAndConfig()
{
  int retVal = 1;
  _maxAngle = getMaxAngle();

  if (getBurnCount() == 0)
  {
    if (_maxAngle * 0.087 < 18)
      retVal = -2;
    else
      writeOneByte(_burn, 0x40);
  }
  else
    retVal = -1;

  return retVal;
}

/*******************************************************
  Method: readOneByte
  In: register to read
  Out: data read from i2c
  Description: reads one byte register from i2c
*******************************************************/
int AMS_5600::readOneByte(int in_adr)
{
  int retVal = -1;
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(in_adr);
  Wire.endTransmission();
  Wire.requestFrom(_ams5600_Address, 1);
  //while (Wire.available() == 0)    ;
  long n=0; bool s=false;
  do{delayMicroseconds(1); n++;if(Wire.available() != 0){s=true;}}while (s==false && n<1000); if (n>=1000) return(-1);
  retVal = Wire.read();

  return retVal;
}

/*******************************************************
  Method: readTwoBytes
  In: two registers to read
  Out: data read from i2c as a word
  Description: reads two bytes register from i2c
*******************************************************/
word AMS_5600::readTwoBytes(int in_adr_hi, int in_adr_lo)
{
  word retVal = -1;

  /* Read Low Byte */
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(in_adr_lo);
  Wire.endTransmission();
  Wire.requestFrom(_ams5600_Address, 1);
  //while (Wire.available() == 0)    ;
  long n=0; bool s=false;
  do{delayMicroseconds(1); n++;if(Wire.available() != 0){s=true;}}while (s==false && n<1000); if (n>=1000) return(-1);
  int low = Wire.read();

  /* Read High Byte */
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(in_adr_hi);
  Wire.endTransmission();
  Wire.requestFrom(_ams5600_Address, 1);

  //while (Wire.available() == 0)    ;
  n=0;  s=false;
  do{delayMicroseconds(1); n++;if(Wire.available() != 0){s=true;}}while (s==false && n<1000); if (n>=1000) return(-1);
  

  word high = Wire.read();

  high = high << 8;
  retVal = high | low;

  return retVal;
}

/*******************************************************
  Method: writeOneByte
  In: address and data to write
  Out: none
  Description: writes one byte to a i2c register
*******************************************************/
void AMS_5600::writeOneByte(int adr_in, int dat_in)
{
  Wire.beginTransmission(_ams5600_Address);
  Wire.write(adr_in);
  Wire.write(dat_in);
  Wire.endTransmission();
}

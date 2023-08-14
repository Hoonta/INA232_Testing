#include "Arduino.h"
#include "Wire.h"

#ifndef INA232_H
#define INA232_H

//REGISTERS
#define INA232_CONFIG             0x00
#define INA232_SHUNT_VOLTAGE      0x01
#define INA232_BUS_VOLTAGE        0x02
#define INA232_POWER              0x03
#define INA232_CURRENT            0x04
#define INA232_CALIBRATION        0x05
#define INA232_MASK_ENABLE        0x06
#define INA232_ALERT_LIMIT        0x07
#define INA232_MANUFACTURER_ID    0x3E

//MASKS
#define INA232_RESET_MASK         0x8000
#define INA232_RESERVED_MASK      0x6000
#define INA232_ADCRANGE_MASK      0x1000
#define INA232_AVG_MASK           0x0E00
#define INA232_VBUSCT_MASK        0x01C0
#define INA232_VSHCT_MASK         0x0038
#define INA232_MODE_MASK          0X0007

typedef struct INA232
{
  uint8_t address;
  float current_LSB;
  float maxCurrent;
  float shunt;
  TwoWire *wire;
} INA232;

TwoWire wire_callers[2] = {
  Wire,
  Wire1
};

uint16_t writeRegister(const INA232 *csa, uint8_t reg, uint16_t value)
{
  csa->wire->beginTransmission(csa->address);
  csa->wire->write(reg);
  csa->wire->write(value >> 8);
  csa->wire->write(value & 0xFF);
  return csa->wire->endTransmission(); //Returns 0:success; 1:data too long to fit in transmit buffer; 2:received NACK on transmit of address; 3:received NACK on transmit of data; 4:other error; 5:timeout
}

uint16_t readRegister(const INA232 *csa, uint8_t reg)
{
  csa->wire->beginTransmission(csa->address);
  csa->wire->write(reg);
  csa->wire->endTransmission();

  csa->wire->requestFrom(csa->address, (uint8_t)2);
  uint16_t value = csa->wire->read();
  value <<= 8;
  value |= csa->wire->read();
  return value;
}

bool reset(const INA232 csa)
{
  uint16_t value = 0xFFFF & INA232_RESET_MASK;
  return(writeRegister(&csa, INA232_CONFIG, value) == 0);
}

uint8_t getAVG(const INA232 csa)
{
  //uint16_t value = readRegister(INA232_CONFIG);
}

uint8_t setAVG(const INA232 csa, uint8_t value)
{
  //IDK WHAT TO DO HERE UGHHHHH
}

uint16_t getADCRange(const INA232 csa)
{
  uint16_t config = readRegister(&csa, INA232_CONFIG);
  config &= INA232_ADCRANGE_MASK;
  config >>= 12;
  return(config); //should return a 1 if ADCRange is +/-20.48mV. Returns a 0 if ADCRange is +/-81.92mV
}

uint8_t setADCRange(const INA232 csa, uint8_t value)
{
  uint16_t mask = value;
  mask <<= 12; //bitshifts a 1 to the correct location
  mask &= INA232_ADCRANGE_MASK;
  return(writeRegister(&csa, INA232_CONFIG, mask));
}

float getShuntVoltage(const INA232 csa)
{
  int16_t raw_value = readRegister(&csa, INA232_SHUNT_VOLTAGE);
  return(raw_value * csa.current_LSB);
}

float getBusVoltage(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_BUS_VOLTAGE);
  return(raw_value*1.6e-3); //the INA232 only has one resolution for bus voltage
}

float getPower(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_POWER);
  return(raw_value);
}

int16_t getCurrent(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_CURRENT);
  return(raw_value);
}

uint16_t getCalibration(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_CALIBRATION);
  return(raw_value);
}

uint16_t setCalibration(const INA232 csa, float rshunt)
{
  uint16_t shunt_cal = (0.00512/(csa.current_LSB*rshunt));
  return(writeRegister(&csa, INA232_CALIBRATION, shunt_cal));
}

uint16_t getMaskEnable(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_MASK_ENABLE);
  return(raw_value);
}

uint16_t getAlertLimit(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_ALERT_LIMIT);
  return(raw_value);
}

uint16_t getID(const INA232 csa)
{
  uint16_t raw_value = readRegister(&csa, INA232_MANUFACTURER_ID);
  return(raw_value);
}
#endif
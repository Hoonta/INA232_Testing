#include <Wire.h>
#include "INA232.h"

uint16_t VBUS = 0;
int16_t VSHUNT = 0;

struct INA232 CS1;
struct INA232 CS2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire1.begin();
  CS1.address=0x40;
  CS1.current_LSB=2.5e-6;
  CS1.wire = &Wire1;
  CS2.address=0x43;
  CS2.current_LSB=2.5e-6;
  CS2.wire = &Wire1;
}

void loop() {
  
  
  delay(500);
  
  //getBusVoltage
  //Serial.print(getBusVoltage(CS1)); 
  //Serial/print(" VBUS CS1\n");
  //Serial.print(getBusVoltage(CS2));
  //Serial.print(" VBUS CS2\n");
  
  //Messing with ADCRange
  //Serial.print(getADCRange(CS1));
  //Serial.print(" ADC Range CS1\n");
  //delay(10);
  //Serial.print("Setting ADC Range: ");
  //Serial.print(setADCRange(CS1, 1));
  //Serial.print("\n");
  //Serial.print(getADCRange(CS1));
  //Serial.print(" ADC Range \n");
  //delay(10);
  //setADCRange(CS1, 0);
  
  //Manufacture_ID
  //Serial.print("Manufacture_ID: ");
  //Serial.print((char)(getID(CS1)>>8));
  //Serial.print((char)getID(CS1));
  //Serial.print("\n");
  
  //Get Shunt Voltage
  Serial.print(getShuntVoltage(CS1)*1000);
  Serial.print(" mVSHUNT CS1\n");
  
  //Testing Calibration
  Serial.print("Getting Calibration: ");
  Serial.print(getCalibration(CS1));
  setCalibration(CS1,0.002);
  Serial.print("\nAfter setting Calibration: ");
  Serial.print(getCalibration(CS1));
  Serial.print("\n Getting Current: ");
  Serial.print(getCurrent(CS1));
  Serial.print("A\n");
  
  delay(500);
}

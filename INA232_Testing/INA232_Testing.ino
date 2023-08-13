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
  CS2.address=0x43;
  CS2.current_LSB=2.5e-6;
}

void loop() {
  
  //Serial.print(getBusVoltage(CS1)); 
  delay(500);
 // Serial.print(getBusVoltage(CS2));
  //Serial.print(" VBUS CS2\n");
  Serial.print(getADCRange(CS1));
  Serial.print(" ADC Range CS1\n");
  delay(10);
  Serial.print("Setting ADC Range: ");
  Serial.print(setADCRange(CS1, 1));
  Serial.print("\n");
  Serial.print(getADCRange(CS1));
  Serial.print(" ADC Range \n");
  delay(10);
  setADCRange(CS1, 0);
  //Serial.print(getShuntVoltage(CS2)*1000);
  //Serial.print(" mVSHUNT CS2\n");
  delay(500);
}

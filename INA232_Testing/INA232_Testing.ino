#include <Wire.h>

int16_t val = 0;
#define _address 0x40

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  
  val = readRegister(0x02);
  Serial.print(1.25e-3 * val);
  Serial.print("\n");
  delay(1000);
  val = 0;
}

uint16_t readRegister(uint8_t reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(_address, (uint8_t)2);
  uint16_t value = Wire.read();
  value <<= 8;
  value |= Wire.read();
  return value;
}
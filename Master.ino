/* ------------------------------- I2C Master ------------------------------- */

#define I2C_SDA 19
#define I2C_SCL 18

#include "Wire.h"

#define I2C_DEV_ADDR 0x55

uint32_t i = 0;

void setup() 
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin(I2C_SDA, I2C_SCL);   
}

void loop() {
  delay(2000);

  //Write message to the slave
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.printf("Hardik from STEMpedia %u", i++);
  uint8_t error = Wire.endTransmission(true);
  Serial.printf("endTransmission: %u\n", error);
  
  //Read 16 bytes from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 16);
  Serial.printf("requestFrom: %u\n", bytesReceived);
  if((bool)bytesReceived){ //If received more than zero bytes
    uint8_t temp[bytesReceived];
    Wire.readBytes(temp, bytesReceived);
    log_print_buf(temp, bytesReceived);
  }
}

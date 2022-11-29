// MPU-6050 Short Example Sketch
//www.elegoo.com
//2016.12.9

#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t accelX, accelY, accelZ, prevX, prevY, prevZ, LRDiff, FBDiff, UDDiff;
bool doubleClick;
void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
  prevX = 0;
  prevY = 0;
  prevZ = 0;
}
void loop(){

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);  // request a total of 14 registers
  accelX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  accelY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  accelZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  LRDiff = accelX - prevX;
  FBDiff = accelY - prevY;
  UDDiff = accelZ - prevZ;

  if (LRDiff > 1500) {
    Serial.print("RIGHT"); Serial.print(LRDiff);
  } else if (LRDiff < -1500) {
    Serial.print("LEFT"); Serial.print(LRDiff);
  }

    if (FBDiff > 1500) {
    Serial.print("BACK"); Serial.print(FBDiff);
  } else if (FBDiff < -1500) {
    Serial.print("FORWARD"); Serial.print(FBDiff);
  }

    if (UDDiff > 3000) {
      Serial.print("CLICK");
    }

  prevX = accelX;
  prevY = accelY;
  prevZ = accelZ;

  Serial.println();
  delay(200);
}

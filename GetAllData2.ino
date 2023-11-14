/* Get all possible data from MPU6050
 * Accelerometer values are given as multiple of the gravity [1g = 9.81 m/s²]
 * Gyro values are given in deg/s
 * Angles are given in degrees
 * Note that X and Y are tilt angles and not pitch/roll.
 *
 * License: MIT
 */

#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

long timer = 0;

float prevAccX = 0;
float prevAccY = 0;
float prevAccZ = 0;

float currAccX;
float currAccY;
const float THRESHOLD_DIFF = 0.3;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
}

void loop() {
  mpu.update();

  currAccX = mpu.getAccX();
  currAccY = mpu.getAccY();
  
  if(millis() - timer > 50){
    if (abs(currAccX - prevAccX) > 0.75) {
      if (currAccX - prevAccX > 0) { // gyro moved right
        Serial.println(1);
      } else {
        Serial.println(0);
      }
    }
//    if (currAccY - prevAccY > 0) {
//      Serial.println(2);
//    } else {
//      Serial.println(3);
//    }
    timer = millis();
    prevAccX = currAccX;
    prevAccY = currAccY;
  }
}


//
//  if (prevAccX == 0){
//    prevAccX = 0.001;
//  }
//  if (prevAccY == 0) {
//    prevAccY = 0.001;
//  }
//    
//  if (abs(currAccX - prevAccX)/ prevAccX > THRESHOLD_DIFF || abs(currAccY - prevAccY)/ prevAccY > THRESHOLD_DIFF) { // 30% difference between values
//  Serial.println(currAccX);
//  prevAccX = currAccX;
//
//  Serial.println(currAccY);
//  prevAccY = currAccY;
//  }
//  if ((mpu.getAccY()- prevAccY)/ prevAccY > 0.2) {
////    Serial.print("Y: ");
//    Serial.println(mpu.getAccY());
//    prevAccY = mpu.getAccY();
//  }
//  if ((mpu.getAccZ()- prevAccZ)/ prevAccZ > 0.2) {
//    Serial.print("Y: ");Serial.println(mpu.getAccY());
//    prevAccZ = mpu.getAccZ();
//  }
//  
//  if(millis() - timer > 500){ // print data every second
////    Serial.print(F("TEMPERATURE: "));Serial.println(mpu.getTemp());
//    Serial.print(("\tX: ");Serial.print(mpu.getAccX());
//    Serial.print("\tY: ");Serial.print(mpu.getAccY());
//    Serial.print("\tZ: ");Serial.println(mpu.getAccZ());
// 
//    Serial.print(F("GYRO      X: "));
//    Serial.println(mpu.getGyroX());
//    Serial.print("\tY: ");Serial.print(mpu.getGyroY());
//    Serial.print("\tZ: ");Serial.println(mpu.getGyroZ());
//  
//    Serial.print(F("ACC ANGLE X: "));Serial.print(mpu.getAccAngleX());
//    Serial.print("\tY: ");Serial.println(mpu.getAccAngleY());
//    
//    Serial.print(F("ANGLE     X: "));Serial.print(mpu.getAngleX());
//    Serial.print("\tY: ");Serial.print(mpu.getAngleY());
//    Serial.print("\tZ: ");Serial.println(mpu.getAngleZ());
//    timer = millis();
//  }

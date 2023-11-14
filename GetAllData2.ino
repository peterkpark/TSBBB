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
  //while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
}

void loop() {
  mpu.update();

  //PORTB 


  currAccX = mpu.getAccX();
  currAccY = mpu.getAccY();
  int button = (PINB & (1<<PB4));
  
  if(millis() - timer > 50){
    if ((abs(currAccX - prevAccX) > 1.5)||(abs(currAccY-prevAccY) >1.5)) {
        Serial.println("shoot!");
        delay(700);
    }

    if (button == 0){
      PORTB |= (1<<PB3);
      Serial.println("button pressed");      
    }
    else{
       PORTB |= (1<<PB3);     
    }
    timer = millis();
    //delay(700);
    prevAccX = currAccX;
    prevAccY = currAccY;
  }
}

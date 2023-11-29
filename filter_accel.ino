#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

long timer = 0;

float prevAccX = 0;
float prevAccY = 0;
float prevAccZ = 0;

float currAccX;
float currAccY;
float currAccZ;
const float THRESHOLD_DIFF = 1.25;
unsigned long prevMillis = 0;
unsigned long currMillis;

// const int PIN_BUTTON = D7;
// const int PIN_LED = D6;

int currButtonVal = HIGH;
int counter = 0;
bool ledOn = false;

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

//  currAccX = mpu.getAccX();
  currAccY = mpu.getAccY();
  currAccZ = mpu.getAccZ();

  currMillis = millis();

  /*
  currButtonVal = digitalRead(PIN_BUTTON);
  if (currButtonVal == LOW) {
    counter = counter + 1;
    if (abs(currAccZ - prevAccZ) > THRESHOLD_DIFF) {
      Serial.println(counter);
      ledOn = true;
      counter = 0;
    }
  } else {
  */
    if(currMillis - prevMillis > 300){
      if (abs(currAccZ - prevAccZ) > THRESHOLD_DIFF || abs(currAccY - prevAccY) > THRESHOLD_DIFF) {
          Serial.println("shoot!");
          prevMillis = currMillis;
      }
//      prevAccX = currAccX;
        prevAccY = currAccY;
        prevAccZ = currAccZ;
    }
}

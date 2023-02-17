
int Sensor3 = 32 ;
int Sensor4 = 33;

int val3 = 0;
int val4 = 0;

int leftMotor_speed = 0;
int rightMotor_speed = 0;
int servoAngle = 90;

#define I2C_SLAVE_ADDR 0x04  
#include <Wire.h>
 
void setup() {

  Serial.begin(9600); 
  Wire.begin();  

  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);

  leftMotor_speed = 0;
  rightMotor_speed = 0;
  servoAngle = 88;
}

 

void loop() {

 
  val3 = analogRead(Sensor3);
  val4 = analogRead(Sensor4);

//When both 3 and 4 are over black, go forward
  if (val3 < 4095 && val4 < 4095) {
   leftMotor_speed = 150;
   rightMotor_speed = 150;
   servoAngle = 88;
  Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);

  }

//When both 3 and 4 are over white, stops
  else if (val3 == 4095 && val4 == 4095) {

    leftMotor_speed = 0;
    rightMotor_speed = 0;
    servoAngle = 88;
    Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);
  }
}

void Transmit_to_arduino(int leftMotor_speed, int rightMotor_speed, int servoAngle){

  Wire.beginTransmission(I2C_SLAVE_ADDR); 
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));   
  Wire.write((byte)(leftMotor_speed & 0x000000FF));          
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));   
  Wire.write((byte)(rightMotor_speed & 0x000000FF));          
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));        
  Wire.write((byte)(servoAngle & 0x000000FF)); 
  Wire.endTransmission();   

}
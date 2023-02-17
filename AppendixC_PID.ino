#include <Wire.h>


#define NANO_ADDRESS 0x04


#define SENSOR1 25 // First sensor green   (from the left)
#define SENSOR2 26 // Second sensor purple
#define SENSOR3 27 // Third sensor pink
#define SENSOR4 14 // Fourth sensor blue
#define SENSOR5 32 // Five sensor orange
#define SENSOR6 33 // Sixth sensor white


float weight1 = -32;
float weight2 = -20;
float weight3 = -8;
float weight4 = 8;
float weight5 = 20;
float weight6 = 32;


int min1, min2, min3, min4, min5, min6;
int Max1, Max2, Max3, Max4, Max5, Max6;

int stableSpeed = 150; 
int leftSpeed = 0;
int rightSpeed = 0;
float K = 0.166;  

int servoAngle = 88; 
int midServo = 54; 
int setpoint = 0; 

double Setpoint;
double Kp= 150, Ki=0, Kd=0;


void setup() {
  
  Wire.begin();
  Serial.begin(9600);

  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
  pinMode(SENSOR3, INPUT);
  pinMode(SENSOR4, INPUT);
  pinMode(SENSOR5, INPUT);
  pinMode(SENSOR6, INPUT);

  min_1 = 615;
  min_2 = 764;
  min_3 = 775;
  min_4 = 796;
  min_5 = 684;
  min_6 = 578;

  max_1 = 4095;
  max_2 = 4095;
  max_3 = 4095;
  max_4 = 4095;
  max_5 = 4095;
  max_6 = 4095;


  Setpoint = 0;
}

void loop() {
  // Read the analogue values 
  int sensor1Value = analogRead(SENSOR1);
  int sensor2Value = analogRead(SENSOR2);
  int sensor3Value = analogRead(SENSOR3);
  int sensor4Value = analogRead(SENSOR4);
  int sensor5Value = analogRead(SENSOR5);
  int sensor6Value = analogRead(SENSOR6);


  sensor1Value = constrain(sensor1Value, min_1, max_1);
  sensor2Value = constrain(sensor2Value, min_2, max_2);
  sensor3Value = constrain(sensor3Value, min_3, max_3);
  sensor4Value = constrain(sensor4Value, min_4, max_4);
  sensor5Value = constrain(sensor5Value, min_5, max_5);
  sensor6Value = constrain(sensor6Value, min_6, max_6);



  sensor1Value = map(sensor1Value, min_1, max_1, 0, 255);
  sensor2Value = map(sensor2Value, min_2, max_2, 0, 255);
  sensor3Value = map(sensor3Value, min_3, max_3, 0, 255);
  sensor4Value = map(sensor4Value, min_4, max_4, 0, 255);
  sensor5Value = map(sensor5Value, min_5, max_5, 0, 255);
  sensor6Value = map(sensor6Value, min_6, max_6, 0, 255);


  float numerator = (sensor1Value * weight1 + sensor2Value * weight2 + sensor3Value * weight3 + sensor4Value * weight4 + sensor5Value * weight5 + sensor6Value * weight6);
  float denomenator = (sensor1Value + sensor2Value + sensor3Value + sensor4Value + sensor5Value + sensor6Value);

  float weightedAvg = numumerator/denomenator;

  float error = Setpoint - weightedAvg;
  float sum = 0;
  sum = sum + error;
  float PrevError = 0;
  float dErr = error - PrevError
  float output = Kp*error + Ki*sum + Kd*dErr;
  PrevError = error;
 
  leftSpeed = baseSpeed + (K * Output);
  rightSpeed = baseSpeed - (K * Output);
  servoPos = midServo + Output;

  
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);
  servoPos = constrain(servoPos, 25, 85);

  transmitArduino(leftSpeed, rightSpeed, servoPos);
}


void transmitArduino(int leftSpeed, int rightSpeed, int servoPos)

{

  Wire.beginTransmission(NANO_ADDRESS);  

  Wire.write((byte)((leftSpeed & 0x0000FF00) >> 8)); 
  Wire.write((byte)(leftSpeed & 0x000000FF));  
  Wire.write((byte)((rightSpeed & 0x0000FF00) >> 8));  
  Wire.write((byte)(rightSpeed & 0x000000FF));  
  Wire.write((byte)((servoPos & 0x0000FF00) >> 8));  
  Wire.write((byte)(servoPos & 0x000000FF)); 
  Wire.endTransmission();  
}
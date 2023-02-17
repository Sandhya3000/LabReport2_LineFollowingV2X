
int Sensor1 = 32;
int Sensor2 = 33;
int Sensor3 = 14 ;
int Sensor4 = 27;
int Sensor5 = 25;
int Sensor6 = 26;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;
int val5 = 0;
int val6 = 0;

#include <Wire.h>


void setup() {
  Serial.begin(9600);  

}

void loop() {

  val1 = analogRead(Sensor1);
  val2 = analogRead(Sensor2);
  val3 = analogRead(Sensor3);
  val4 = analogRead(Sensor4);
  val5 = analogRead(Sensor5);
  val6 = analogRead(Sensor6);

 
  Serial.print(val1);
  Serial.print(val2);
  Serial.print(val3);
  Serial.print(val4);
  Serial.print(val5);
  Serial.print(val6);

 

}
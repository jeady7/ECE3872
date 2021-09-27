#include <Servo.h>
int led=12;
int sensor=2;
bool value=0;
int motor1=10;
int motor2=9;
int enable=11;
int speaker=3;
int angle=0;
Servo servo;
void setup() {
  pinMode(led,OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(speaker,OUTPUT);
  servo.attach(7);
  servo.write(angle);
  Serial.begin(9600);
}

void loop() {
  value=digitalRead(sensor);
  Serial.println(value);

  if (value==HIGH){
    digitalWrite(led,HIGH);
    digitalWrite(enable,200);
    digitalWrite(10,HIGH);
    digitalWrite(9,LOW);
    angle++;
    servo.write(angle);
    tone(speaker,500);
    delay(100);
    noTone(speaker);
    digitalWrite(enable,0);
  }
  else{
    digitalWrite(led,LOW);
  }
}

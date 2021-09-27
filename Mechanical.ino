int enable=11;
int motor1=10;
int motor2=9;
int enable2=7;
int motor3=5;
int motor4=6;
int power=8;
int sensor=2;
int led=12;

void setup() {
  // put your setup code here, to run once:
  pinMode (led,OUTPUT);
  pinMode (enable,OUTPUT);
  pinMode (motor1,OUTPUT);
  pinMode (motor2,OUTPUT);
  pinMode (motor3,OUTPUT);
  pinMode (motor4,OUTPUT);
  pinMode (enable2,OUTPUT);
  pinMode (power,INPUT);
} 

void loop() {
  // put your main code here, to run repeatedly:
  Power=digitalRead(power);
  if (Power==LOW){
     digitalWrite(12,HIGH);
     analogWrite(enable,200);
     digitalWrite(10,HIGH);
     digitalWrite(9,LOW);
  }
  
}

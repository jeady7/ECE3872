int motor1=10;
int motor2=9;
int enable=11;

void setup() {
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(enable,OUTPUT);

}

void loop() {
  digitalWrite(enable,200);
  digitalWrite(10,HIGH);
  digitalWrite(9,LOW);

}

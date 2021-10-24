#include <Servo.h>
int led=10;
int sensor=8;
int motor1=10;
int motor2=9;
int enable=11;
int speaker=3;

int octive=4;

int durations[]={2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int C=16.3516*(2^octive);
int D=18.35405*(2^octive);
int E=20.60172*(2^octive);
int F=21.82676*(2^octive);
int G=24.49971*(2^octive);
int A=27.5*(2^octive);
int B=30.86771*(2^octive);
int high_C=32.70320*(2^octive);
int rest=0;
int notes[]={C,rest,C,rest,C,rest,D,rest,E,rest,E,rest,D,rest,E,rest,F,rest,G,rest,high_C,rest,high_C,rest,high_C,rest,G,rest,G,rest,G,rest,E,rest,E,rest,E,rest,C,rest,C,rest,C,rest,G,rest,F,rest,E,rest,D,rest,C,rest};
int s=100;

int conductorMode = 1;  //Switch 
int playerMode = 2;

const int AA=7; //LSB
const int BB=6;
const int CC=5;
const int DD=4; //MSB
//octave buttons
int oct_up = 11;
int oct_down = 12;
int select = 13;
int reset = A0;

int angle=0;
bool value=0;

Servo servo;
void setup() {
  pinMode(led,OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(speaker,OUTPUT);
  pinMode(conductorMode, INPUT);
  pinMode(playerMode, INPUT);
  pinMode(AA, OUTPUT); //LSB
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT); //MSB
  servo.attach(A1);
  servo.write(angle);
  Serial.begin(9600);
}

  void conductorsetup() {
  if (select==1) {
  play();
  }
}
  void playersetup() {
  /////Do audio analysis and set tempo and octave...
  play();
}

void loop() {
  int  a = octive%2;
  int b = octive/2%2;
  int c = octive/4%2;
  int d = octive/8%2;
  (a==0) ? digitalWrite(AA, LOW): digitalWrite(AA, HIGH);
  (b==0) ? digitalWrite(BB, LOW): digitalWrite(BB, HIGH);
  (c==0) ? digitalWrite(CC, LOW): digitalWrite(CC, HIGH);
  (d==0) ? digitalWrite(DD, LOW): digitalWrite(DD, HIGH);
  if (oct_up) {
    octive++;
  }
  if (oct_down) {
    octive--;
  }
  
  if(playerMode == 1) {
    playersetup();
  } else if (conductorMode == 1) {
    conductorsetup();
  }
  
  }

  void play() {
  tone(speaker,A,durations[2]*100);
  digitalWrite(led,HIGH);
  digitalWrite(enable,200);
  digitalWrite(10,HIGH);
  digitalWrite(9,LOW);
  for (int i=0; notes[i]!=-1;i++){
    //move the motor in here somewhere as well
    //for testing 
    
    if (reset ==1) {
      return;
    }
    int duration=s*durations[i];
    tone(speaker,notes[i],duration*0.95);
    delay(duration);
    if (i==52){
        break;
      }
    noTone(speaker);
    digitalWrite(enable,0);
    digitalWrite(led,LOW);
  }
  }

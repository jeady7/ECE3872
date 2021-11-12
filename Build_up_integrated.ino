#include <Servo.h>
Servo servo1;
Servo servo2;
int sensor=8;
int led=2;
int speaker=3;
int durations[]={2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int octive=4;
bool value=0;
int C=16.3516;
int D=18.35405;
int E=20.60172;
int F=21.82676;
int G=24.49971;
int A=27.5;
int B=30.86771;
int high_C=32.70320;
int rest=0;
int notes[]={C,rest,D,rest,E,rest,E,rest,D,rest,E,rest,F,rest,G,rest,high_C,rest,high_C,rest,high_C,rest,G,rest,G,rest,G,rest,E,rest,E,rest,E,rest,C,rest,C,rest,C,rest,G,rest,F,rest,E,rest,D,rest,C,rest};
int Start1=0;int Start2=0;int Start3=0; int Start4 = 0;int cursor1=0;int cursor2=0;int cursor3=0; int cursor4 = 0;
int state=0;
float tempo=0;

int conductorMode = 12;  //Switch 
int playerMode = 13;
int playerState;
int conductorState;

const int AA=4; //LSB
const int BB=5;
const int CC=6;
const int DD=7; //MSB
//octave buttons
int oct_up = A3;
int upstate;
int oct_down = A4;
int downstate;
int select = A5;
int selectState;

int angle=5;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(sensor,INPUT);
  pinMode(speaker,OUTPUT);
  pinMode(select,INPUT);
  pinMode(oct_up,INPUT);
  pinMode(oct_down,INPUT);
  pinMode(conductorMode, INPUT);
  pinMode(playerMode, INPUT);
  pinMode(AA, OUTPUT); //LSB
  pinMode(BB, OUTPUT);
  pinMode(CC, OUTPUT);
  pinMode(DD, OUTPUT); //MSB
  servo1.attach(9);
  servo1.write(angle);
  servo2.attach(10);
  servo2.write(50-angle);
  Serial.begin(9600);
}

void conductorsetup() {
  digitalWrite(led,HIGH);
  selectState=digitalRead(select);
  if (selectState==LOW) {
    play();
  }
}

void loop() {
  if (octive==-1){
    octive=9;
  }
  octive=octive%10;
  int  a = octive%2;
  int b = (octive/2)%2;
  int c = (octive/4)%2;
  int d = (octive/8)%2;
  (a==0) ? digitalWrite(AA, LOW): digitalWrite(AA, HIGH);
  (b==0) ? digitalWrite(BB, LOW): digitalWrite(BB, HIGH);
  (c==0) ? digitalWrite(CC, LOW): digitalWrite(CC, HIGH);
  (d==0) ? digitalWrite(DD, LOW): digitalWrite(DD, HIGH);
  upstate=digitalRead(oct_up);
  downstate=digitalRead(oct_down);
  if (upstate==LOW) {
    octive++;
    delay(800);
  }
  if (downstate==LOW) {
    octive--;
    delay(800);
  }
  
  playerState=digitalRead(playerMode);
  conductorState=digitalRead(conductorMode);
  
if(playerState == 1) {
  servo1.detach();
  servo2.detach();
  digitalWrite(led, LOW);
  value=digitalRead(sensor);
  if (value==HIGH && state==0){
    Start1=millis();
    Serial.println(Start1);
    state=1;
    cursor1=millis();
  }
  if (value==HIGH && state==1){
    cursor2=millis();
    if (abs(cursor2-cursor1)>50){
      Start2=millis();
      Serial.println(Start2);
      state=2;
    }
    cursor1=cursor2;
    
  }
  if (value==HIGH && state==2){
    Serial.println(2);
    cursor3=millis();
    if (abs(cursor3-cursor2)>50){
      Start3=millis();
      tempo = Start3-Start2;
      state=3;
    }
    cursor2=cursor3;
  }

  if (value==HIGH && state==3){
    cursor4=millis();
    if (abs(cursor4-cursor3)>50){
      Start4=millis();
      state=4;
    }
    cursor3=cursor4;
  } 


  if (state==4){
    servo1.attach(9);
    servo1.write(angle);
    servo2.attach(10);
    servo2.write(50-angle);
    for (int i=2; notes[i]!=-1;i++){
        if (digitalRead(conductorMode)) {
          angle=5;
          servo1.write(angle);
          servo2.write(50-angle);
          state=0;
          break;
        }
        if ((i-2)/10%2) {
         angle=angle-4;
        }
        if((i-2)/10%2==0){
         angle=angle+4;
        }
        servo1.write(angle);
        servo2.write(50-angle);
        int duration=durations[i];
        tone(speaker,notes[i]*(2^octive),duration*tempo/2.8);
        delay(duration*0.95*tempo/2.8);
        if (i==49){
          angle=5;
          servo1.write(angle);
          servo2.write(50-angle);
          state=0;
          break;
        }
  }
  state=0;
}
} 
else{
  conductorsetup();
}
}

void play() {
  servo1.attach(9);
  servo2.attach(10);
  servo1.write(5);
  servo2.write(45);
//  tone(speaker,A,durations[2]*100);
  for (int i=0; notes[i]!=-1;i++){
    if (i/10%2) {
      angle=angle-4;
    }
    if(i/10%2==0){
      angle=angle+4;
    }
    servo1.write(0+angle);
    servo2.write(50-angle);
    int duration=100*durations[i];
    tone(speaker,notes[i]*(2^octive),duration*0.95);
    delay(duration);
    if (i==49){
        angle=5;
        servo1.write(5);
        servo2.write(50-angle);
        break;
     }
  }
  }

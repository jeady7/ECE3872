#include <Servo.h>
int led=2;
int sensor=8;
int speaker=3;

int octive=4;

int durations[]={2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
float C=16.3516;
float D=18.35405;
float E=20.60172;
float F=21.82676;
float G=24.49971;
float A=27.5;
float B=30.86771;
float high_C=32.70320;
float rest=0;
float notes[]={C,rest,C,rest,C,rest,D,rest,E,rest,E,rest,D,rest,E,rest,F,rest,G,rest,high_C,rest,high_C,rest,high_C,rest,G,rest,G,rest,G,rest,E,rest,E,rest,E,rest,C,rest,C,rest,C,rest,G,rest,F,rest,E,rest,D,rest,C,rest};
int s=100;

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
float tempo;
int Start1=0;int Start2=0;int Start3=0; int Start4 = 0;int cursor1=0;int cursor2=0;int cursor3=0; int cursor4 = 0;
int state = 0;
int countPlays = 0;

int angle=0;
bool value=0;

Servo servo;
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
  servo.attach(A1);
  servo.write(angle);
  Serial.begin(9600);
  int start0 = millis();
  Serial.print("Start0: ");
  Serial.print(start0);
}

void conductorsetup() {
  digitalWrite(led,HIGH);
  selectState=digitalRead(select);
  if (selectState==LOW) {
    play();
  }
}

void playersetup() {
  int dummy = millis();
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
      Serial.println(tempo);
    }
    cursor1=cursor2;
    
  }
  if (value==HIGH && state==2){
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
    //countPlays++;
    for (int i=6; notes[i]!=-1;i++){
        if (digitalRead(conductorMode)) {
          break;
        }
        int duration=durations[i];
        tone(speaker,notes[i]*(2^octive),duration*tempo/2.8);
        delay(duration*0.95*tempo/2.8);
        if (i==52){
          break;
        }
  }
  state=0;
}

}

void loop() {
  int  a = octive%2;
  int b = (octive/2)%2;
  int c = (octive/4)%2;
  int d = (octive/8)%2;
  (a==0) ? digitalWrite(AA, LOW): digitalWrite(AA, HIGH);
  (b==0) ? digitalWrite(BB, LOW): digitalWrite(BB, HIGH);
  (c==0) ? digitalWrite(CC, LOW): digitalWrite(CC, HIGH);
  (d==0) ? digitalWrite(DD, LOW): digitalWrite(DD, HIGH);
  upstate=digitalRead(oct_up);
  Serial.print("Up button: ");
  Serial.println(upstate);
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
    playersetup();
  } 
  else{
    conductorsetup();
  }
  
  }

void play() {
//  tone(speaker,A,durations[2]*100);
  Serial.println(high_C);
  for (int i=0; notes[i]!=-1;i++){
    //move the motor in here somewhere as well
    //for testing 
    int duration=s*durations[i];
    tone(speaker,notes[i]*(2^octive),duration*0.95);
    delay(duration);
    if (i==52){
        break;
     }
  }
  }

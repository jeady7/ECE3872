#include <Servo.h>
// Set pin numbers for the hardware we currently have 1 too many pins
// 

int sensor=2;
int motor1=3;
int motor2=4;
int speaker=5;
int conductorMode = 6;
int playerMode = 7;
int enable=8; //motor driver enable
//7 Seg pins
const int A=9; //LSB
const int B=10;
const int C=11;
const int D=12; //MSB
//octave buttons
int oct_up = 13;
int oct_down = 14;
int select = 15;
int reset = 1;



//global variables
bool value=0; //microphone in
int angle=0; //servo position
int octave = 4;
Servo servo;

void setup() {
  //assigning pins
  pinMode(sensor,INPUT);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(enable,OUTPUT);
  pinMode(speaker,OUTPUT);
  pinMode(conductorMode, INPUT);
  pinMode(playerMode, INPUT);
  pinMode(A, OUTPUT); //LSB
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT); //MSB
  //servo setup
  servo.attach(7);
  servo.write(angle);
  Serial.begin(9600);

}

void loop() {

  int  a = octave%2;
  int b = octave/2%2;
  int c = octave/4%2;
  int d = octave/8%2;
  (a==0) ? digitalWrite(A, LOW): digitalWrite(A, HIGH);
  (b==0) ? digitalWrite(B, LOW): digitalWrite(B, HIGH);
  (c==0) ? digitalWrite(C, LOW): digitalWrite(C, HIGH);
  (d==0) ? digitalWrite(D, LOW): digitalWrite(D, HIGH);
  if (oct_up) {
    octave++;
  }
  if (oct_down) {
    octave--;
  }
  if(playerMode == 1) {
    conductorsetup();
  } else if (conductorMode == 1) {
    playersetup();
  }
  delay(100);
}

void conductorsetup() {
  while (select = 0) {
    if (oct_up) {
    octave++;
    }
    if (oct_down) {
    octave--;
    }
    if (reset == 1) {
      return;
    }
    delay(300);
  }
  play();
}

void playersetup() {
  /////Do audio analysis and set tempo and octave...
  play();
}


//Song variables
int durations[]={2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int low_C=16.3516*(2^octave);
int low_D=18.35405*(2^octave);
int E=20.60172*(2^octave);
int F=21.82676*(2^octave);
int G=24.49971*(2^octave);
int high_A=27.5*(2^octave);
int high_B=30.86771*(2^octave);
int high_C=32.70320*(2^octave);
int rest=0;
int notes[]={low_C,rest,low_C,rest,low_C,rest,low_D,rest,E,rest,E,rest,low_D,rest,E,rest,F,rest,G,rest,high_C,rest,high_C,rest,high_C,rest,G,rest,G,rest,G,rest,E,rest,E,rest,E,rest,low_C,rest,low_C,rest,low_C,rest,G,rest,F,rest,E,rest,low_D,rest,low_C,rest};
int s=90;
void play() {
  tone(speaker,high_A,durations[2]*100);
  for (int i=0; notes[i]!=-1;i++){
    //move the motor in here somewhere as well
    //for testing 
    
    if (reset = 1) {
      return;
    }
    int duration=s*durations[i];
    tone(speaker,notes[i],duration*0.95);
    delay(duration);
    noTone(3);
  }
}

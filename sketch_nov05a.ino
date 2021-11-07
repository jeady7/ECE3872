int sensor=8;
int speaker=3;
int durations[]={2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int octive=4;
bool value=0;
int C=16.3516*(2^octive);
int D=18.35405*(2^octive);
int E=20.60172*(2^octive);
int F=21.82676*(2^octive);
int G=24.49971*(2^octive);
int A=27.5*(2^octive);
int B=30.86771*(2^octive);
int high_C=32.70320*(2^octive);
int rest=0;
int notes[]={C,rest,D,rest,E,rest,E,rest,D,rest,E,rest,F,rest,G,rest,high_C,rest,high_C,rest,high_C,rest,G,rest,G,rest,G,rest,E,rest,E,rest,E,rest,C,rest,C,rest,C,rest,G,rest,F,rest,E,rest,D,rest,C,rest};
int Start1=0;int Start2=0;int Start3=0;int cursor1=0;int cursor2=0;int cursor3=0;
int state=0;
float tempo=0;

void setup() {
  pinMode(sensor,INPUT);
  pinMode(speaker,OUTPUT);
  Serial.begin(9600);
}

void loop() {
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
      tempo=(Start2-Start1);
      Serial.println(tempo);
    }
    cursor1=cursor2;
    
  }
  if (value==HIGH && state==2){
    cursor3=millis();
    if (abs(cursor3-cursor2)>50){
      Start3=millis();
      state=3;
    }
    cursor2=cursor3;
  }

  if (state==3){
    for (int i=0; notes[i]!=-1;i++){
        int duration=durations[i];
        tone(speaker,notes[i],duration*tempo/2.8);
        delay(duration*0.95*tempo/2.8);
        if (i==49){
          break;
        }
  }
  state=0;
}
}

int led=12;
int speaker=3;
int durations[]={2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};
int octive=4;
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
int s=90;

void setup() {
  pinMode(led,OUTPUT);
  pinMode(speaker,OUTPUT);
  Serial.begin(9600);
  tone(speaker,A,durations[2]*100);
  for (int i=0; notes[i]!=-1;i++){
    int duration=s*durations[i];
    tone(speaker,notes[i],duration*0.95);
    delay(duration);
    noTone(3);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

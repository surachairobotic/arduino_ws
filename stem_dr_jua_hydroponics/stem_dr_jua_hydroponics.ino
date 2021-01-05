#define NUM_LED 4
#define PUSH LOW

const int led[NUM_LED] = {8, 9, 10, 11}, btnPin=2, pwmPin=3;
const int pattern[5][NUM_LED] = { {1,0,0,0}, 
                                  {0,1,0,0}, 
                                  {0,0,1,0}, 
                                  {0,0,0,1}, 
                                  {1,1,1,1}};
int cntPat=0, prevBtn=!PUSH;
unsigned long prevTime=0;
bool bPause=false;

void setup() {
  for(int i=0; i<NUM_LED; i++)
    pinMode(led[i], OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(pwmPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  //ex1_1();
  ex1_2();
  //ex2();
  //ex3();
  //ex4();
  //ex5();
}

void ex1_1() {
  for(int i=0; i<NUM_LED; i++)
    digitalWrite(led[i], pattern[cntPat][i]);
  delay(500);
  cntPat=(cntPat+1)%5;  
}

void ex1_2() {
  for(int i=0; i<NUM_LED; i++)
    digitalWrite(led[i], pattern[cntPat][i]);
  if(millis()-prevTime > 500) {
    prevTime=millis();
    cntPat=(cntPat+1)%5;
  }
}

void ex2() {
  for(int i=0; i<NUM_LED; i++)
    digitalWrite(led[i], pattern[cntPat][i]);
  if(!bPause && millis()-prevTime > 500) {
    prevTime=millis();
    cntPat=(cntPat+1)%5;
  }
  if(digitalRead(btnPin)==PUSH) {
    if(prevBtn!=PUSH) {
      prevBtn=PUSH;
      bPause=!bPause;
    }
  }
  else
    prevBtn=!PUSH;
}

void ex3() {
  for(int i=0; i<NUM_LED; i++)
    digitalWrite(led[i], pattern[cntPat][i]);
  if(!bPause && millis()-prevTime > 500) {
    prevTime=millis();
    cntPat=(cntPat+1)%5;
  }
  if(Serial.available()) {
    char c=Serial.read();
    if(c == 'F') {
      bPause=true;
      Serial.println("Pause...");
    }
    else if(c == 'N') {
      bPause=false;
      Serial.println("Running...");
    }
  }
}

void ex4() {
  for(int i=0; i<NUM_LED; i++)
    digitalWrite(led[i], pattern[cntPat][i]);
  if(!bPause && millis()-prevTime > 500) {
    prevTime=millis();
    cntPat=(cntPat+1)%5;
  }
  if(analogRead(A0) < 512)
    bPause=true;
  else
    bPause=false;
}

void ex5() {
  int rawAnalog = analogRead(A0);  
  analogWrite(pwmPin, int(rawAnalog/1024.0*255.0));
  Serial.println(rawAnalog/1024.0*5.0);
}

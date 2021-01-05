const int led[6] = {6,8,10,11,12,13};
bool state=true;

void setup() {
  for(int i=0; i<6; i++)
    pinMode(led[i], OUTPUT);
}

void loop() {
  for(int i=0; i<6; i++)
    digitalWrite(led[i], state);
  delay(500);
  state=!state;
}

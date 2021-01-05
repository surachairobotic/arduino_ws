const int led[6] = {6,8,10,11,12,13};

void setup() {
  Serial.begin(9600);
  for(int i=0; i<6; i++)
    pinMode(led[i], OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    String txt = Serial.readStringUntil('\n');
    int state = -1;
    if(txt[0] == 'N')
      state = 1;
    else if(txt[0] == 'F')
      state = 0;
    else {
      Serial.println("Invalid command !");
      state = -1;
    }
    if(state != -1)
      if(txt[1] >= '1' && txt[1] <= '6') {
        digitalWrite(led[5], state);
        Serial.print(txt[1]-'1');
        Serial.print(" : ");
        Serial.println((state) ? "ON" : "OFF");
      }
      else
        Serial.println("Invalid index !");
  }
}

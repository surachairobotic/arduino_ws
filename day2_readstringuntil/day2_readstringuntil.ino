String txt = "";

void setup() {
  Serial.begin(9600);
}

void loop() {
  if( Serial.available() > 0 ) {
    txt = Serial.readStringUntil('\n');
    Serial.print("txt.length() = ");
    Serial.println(txt.length());    
    if( txt.length() > 2 ) {
      Serial.print("txt[0] = ");
      Serial.println(txt[0]);
      Serial.print("txt[1] = ");
      Serial.println(txt[1]);
    }
  }
}

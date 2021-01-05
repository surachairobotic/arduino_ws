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
      txt.remove(0, 2);
      Serial.print("new text = ");
      Serial.println(txt);
    }
  }
}

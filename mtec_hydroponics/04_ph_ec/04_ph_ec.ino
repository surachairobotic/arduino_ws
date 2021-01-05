#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

uint32_t time_lcd = 0;

void setup() {
  
  smartfarm._wifi.enable(false);
  smartfarm._temp_humid.enable(false);
  smartfarm._light.enable(false);
  smartfarm._ec.enable(false);
  smartfarm._ph.enable(true);

  smartfarm.enable_upload( false );

  if( !smartfarm.init("xxxxxxxxxxxx") )
    while(1);

  smartfarm._lcd.print(0, 0, "Welcome");
  smartfarm._lcd.print(0, 1, "SmartFarming");
  smartfarm._lcd.print(0, 2, "-----");
  smartfarm._lcd.print(0, 3, "MTEC");
  delay(1000);
}

void loop() {
  // Read sensor data and upload them to server
  smartfarm.update();
  if( (uint32_t)(millis()-time_lcd) >= 2000 ){
    time_lcd = millis();
    float ph  = smartfarm._ph.read();
    //    , ec  = smartfarm._ec.read();
    //Serial.print("EC:");
    //Serial.print(ec);
    //Serial.print(", pH:");
    //Serial.print(ph);
    smartfarm._lcd.clear();
    smartfarm._lcd.print(0, 0, "pH Sensor");
    smartfarm._lcd.print(0, 1, analogRead(A2));
    smartfarm._lcd.print(0, 2, ph);
  }
}

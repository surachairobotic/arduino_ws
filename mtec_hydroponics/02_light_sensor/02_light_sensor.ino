#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

uint32_t time_lcd = 0;

void setup() {
  
  smartfarm._wifi.enable(false);
  smartfarm._temp_humid.enable(false);
  smartfarm._light.enable(true);
  smartfarm._ec.enable(false);
  smartfarm._ph.enable(false);

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
  if( (uint32_t)(millis()-time_lcd) >= 2000 ){
    time_lcd = millis();
    float light = smartfarm._light.read();
    smartfarm._lcd.clear();
    smartfarm._lcd.print(0, 3, "LIGHT:");
    smartfarm._lcd.print(6, 3, light);
  }
}

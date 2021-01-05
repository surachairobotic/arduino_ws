#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

float temp[4]={0.0}, humid[4]={0.0};

void setup() {
  
  smartfarm._wifi.enable(false);
  smartfarm._temp_humid.enable(false);
  smartfarm._light.enable(false);
  smartfarm._ec.enable(false);
  smartfarm._ph.enable(false);

  smartfarm.enable_upload( false );

  if( !smartfarm.init("xxxxxxxxxxxx") )
    while(1);

  smartfarm._lcd.print(0, 0, "Welcome");
  smartfarm._lcd.print(0, 1, "SmartFarming");
  smartfarm._lcd.print(0, 2, "-----");
  smartfarm._lcd.print(0, 3, "MTEC");

  randomSeed(analogRead(0));
  delay(500);
}

void loop() {
  // Read sensor data and upload them to server
  smartfarm.update();
  //float temp  = smartfarm._temp_humid.read_temperature()
  //    , humid = smartfarm._temp_humid.read_humidity();
  for(int i=3; i>=1; i--) {
    temp[i] = temp[i-1];
    humid[i] = humid[i-1];
  }
  temp[0]=smartfarm._temp_humid.read_temperature();
  humid[0]=smartfarm._temp_humid.read_humidity();
  smartfarm._lcd.clear();
  for(int i=0; i<4; i++) {
    smartfarm._lcd.print(0, i, "T:");
    smartfarm._lcd.print(2, i, temp[i]);
    smartfarm._lcd.print(7, i, ", H:");
    smartfarm._lcd.print(11, i, humid[i]);    
  }
  smartfarm.delay(1000);
}

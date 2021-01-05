#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

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
}

void loop() {
  // put your main code here, to run repeatedly:

}

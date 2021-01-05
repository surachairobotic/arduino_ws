#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;
bool state=false;

void setup() {
  // Use Serial for showing message from smartfarm library
  Serial.begin(9600);

  /*
    Set log level to LOG_WARN.
    You can change to LOG_INFO for more information.
  */
  smartfarm.set_log_level( LOG_WARN );

  // Disable Wi-Fi module and sensors since they are not used in this sample program
  smartfarm._wifi.enable(false);
  smartfarm._temp_humid.enable(false);
  smartfarm._light.enable(false);
  smartfarm._ec.enable(false);
  smartfarm._ph.enable(false);

  // Disable uploading data to server
  smartfarm.enable_upload( false );

  /*
    Initialize smartfarm library. Return false if failed.
    Replace "xxxxxxxxxxxx" with your station API key.
  */
  if( !smartfarm.init("xxxxxxxxxxxx") )
    while(1);

}

void loop() {
  if(state) {
    smartfarm._lcd.print(0, 0, "Welcome");
    smartfarm._lcd.print(0, 1, "SmartFarming");
    smartfarm._lcd.print(0, 2, "-----");
    smartfarm._lcd.print(0, 3, "MTEC");
  }
  else {
    smartfarm._lcd.clear();
  }
  state = !state;
  delay(500);
}

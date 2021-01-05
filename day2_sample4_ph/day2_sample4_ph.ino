#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

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
  smartfarm._ph.enable(true);

  // Disable uploading data to server
  smartfarm.enable_upload( false );

  /*
    Initialize smartfarm library. Return false if failed.
    Replace "xxxxxxxxxxxx" with your station API key.
  */
  if( !smartfarm.init("xxxxxxxxxxxx") )
    while(1);

void setup() {
  ...
  ...
  
  smartfarm._ph.set_param_volt2pH(1.94247, 3.39571);
}

void loop() {
  // Read sensor data and upload them to server
  smartfarm.update();

  float ph = smartfarm._ph.read();
  Serial.print("pH : ");
  Serial.println(ph);

  smartfarm.delay(500);
}

#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;
bool state=false;

void setup() {
  // Use Serial for showing message from smartfarm library
  Serial.begin(9600);

  smartfarm.set_log_level( LOG_WARN );

  // Disable Wi-Fi module and sensors since they are not used in this sample program
  smartfarm._wifi.enable(false);
  smartfarm._temp_humid.enable(false);
  smartfarm._light.enable(true);
  smartfarm._ec.enable(false);
  smartfarm._ph.enable(false);

  // Disable uploading data to server
  smartfarm.enable_upload( false );

  if( !smartfarm.init("xxxxxxxxxxxx") )
    while(1);

}

void loop() {
  // Read sensor data and upload them to server
  smartfarm.update();

  float light = smartfarm._light.read();
  if(light > 50){
    
  else
    Serial.println("Night");

  state = !state;
  smartfarm.delay(1000);
}

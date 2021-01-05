#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

const int led[6] = {6,8,10,11,12,13};
bool state=true;
float temp[4]={0.0}, humid[4]={0.0};
int pattern[4][3] = { {255, 0, 0}, 
                    {0, 255, 0}, 
                    {0, 0, 255},
                    {255, 255, 255} };
int i_pat=0;

void setup() {
  
  smartfarm._wifi.enable(false);
  smartfarm._temp_humid.enable(true);
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

  smartfarm._led.set_pixel_num( 865 );
  smartfarm._led.set_color( 150, 150, 150 );

  for(int i=0; i<6; i++)
    pinMode(led[i], OUTPUT);

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

  smartfarm._led.set_color( pattern[i_pat][0],
                            pattern[i_pat][1],
                            pattern[i_pat][2] );
  i_pat=(i_pat+1)%4;

  for(int i=0; i<6; i++)
    digitalWrite(led[i], true);
  state=!state;

  smartfarm.delay(25000);
}

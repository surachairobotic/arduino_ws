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

  smartfarm._led.set_pixel_num( 825 );
  smartfarm._led.set_color( 255, 0, 0 );
}

void loop() {

}

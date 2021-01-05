/*
  A sample program to control fans and evaporator
*/

#include <MTEC_smartfarm.h>

cSmartFarm smartfarm;

// LED RGB value
const uint8_t LED_COLOR[3] = { 200, 200, 200 };

// Read sensors' data and show on LCD every [INTERVAL_READ_DATA] milliseconds
const uint32_t INTERVAL_READ_DATA = 1000;

// get a Wi-Fi status from Wi-Fi module
void get_wifi_status();

// Wi-Fi status
char wifi_status[32] = "";

// The last time Wi-Fi status is updated
uint32_t time_wifi_status = -1000000;

// The last time sensors' data are read
uint32_t time_read_data = 0;

// fans & evaporator's status
static bool fan_status[3] = {false,false,false}
  , evap_status = false;

void setup(){
  // Use Serial for showing message from smartfarm library
  Serial.begin(9600);

  /*
    Set log level to LOG_WARN.
    You can change to LOG_INFO for more information.
  */
  smartfarm.set_log_level( LOG_WARN );
  
  /*
    Initialize smartfarm library. Return false if failed.
    Replace "xxxxxxxxxxxx" with your station API key.
    API key can be found in https://farm.mtec.or.th/stations.html
  */
  smartfarm._wifi.enable(false);
  if( !smartfarm.init("3qqn7jd6qsx6") )
    while(1);
    
  /*
    Set Wi-Fi module's log level to LOG_WARN.
    You can change to LOG_INFO for more information.
  */
  //smartfarm._wifi.set_log_level( LOG_WARN );

  // Turn on LED when start
  smartfarm._led.set_color( LED_COLOR[0], LED_COLOR[1], LED_COLOR[2] );

}

void loop(){
  smartfarm.update();
  //get_wifi_status();

  if( millis()-time_read_data >= INTERVAL_READ_DATA ){
    // LED
    {
      struct tm timeinfo;
      
      // get date & time from the internet
      if( smartfarm.get_datetime(&timeinfo) ){
        // turn on LED between 5:00 ~ 20:00
        if( timeinfo.tm_hour >= 5 && timeinfo.tm_hour<20 ){
          smartfarm._led.set_color( LED_COLOR[0], LED_COLOR[1], LED_COLOR[2] );
        }
        else{
          // turn off LED between 20:00 ~ 5:00
          //smartfarm._led.set_color( 0, 0, 0 );
          smartfarm._led.set_color( LED_COLOR[0], LED_COLOR[1], LED_COLOR[2] );
        }
      }
      else{
        // do nothing if cannot get date & time
        smartfarm._led.set_color( LED_COLOR[0], LED_COLOR[1], LED_COLOR[2] );
      }
    }

    {
      // Read sensors' data
      float temp = smartfarm._temp_humid.read_temperature()
        , humid = smartfarm._temp_humid.read_humidity()
        , light = smartfarm._light.read()
        , ec = smartfarm._ec.read()
        , ph = smartfarm._ph.read()
        , current = smartfarm._current.read();

      // show the data on LCD
      {
        // Clear all messages on LCD
        smartfarm._lcd.clear();
        
        char str[32]; // a string buffer to store message shown on LCD

        // Show temperature & pH in the 1st row of the LCD
        strcpy(str, "TEMP:");
        dtostrf( temp, 4, 1, str + strlen(str) );  // convert float to char* and store it into "str" variable
        strcpy( str + strlen(str), " PH:");
        dtostrf( ph, 4, 1, str + strlen(str) );
        smartfarm._lcd.print(0, 0, str);
        Serial.println(str);
    
        // Show humidity and EC in the 2nd row
        strcpy(str, "HUMID:");
        dtostrf( humid, 4, 1, str + strlen(str) );
        strcpy( str + strlen(str), " EC:");
        dtostrf( ec, 4, 1, str + strlen(str) );
        smartfarm._lcd.print(0, 1, str);
        Serial.println(str);

        // show pump statuses and Wi-Fi status in the 3rd row
        sprintf(str, "PU:%d,%d Wi:%s", !digitalRead( PIN_STATUS_PUMP_PLANT )
          , !digitalRead( PIN_STATUS_PUMP_EVAPORATOR ), wifi_status );
        str[LCD_COLUMNS] = 0;
        smartfarm._lcd.print(0, 2, str);
        Serial.println(str);

        // Show the real time got from the internet in the 4th row
        struct tm timeinfo;
        // check if we can get date & time from the internet
        if( smartfarm.get_datetime(&timeinfo) ){
          // show hours, minutes and seconds
          sprintf( str, "TIME: %02d:%02d:%02d"
            , timeinfo.tm_hour 
            , timeinfo.tm_min
            , timeinfo.tm_sec );
          smartfarm._lcd.print(0, 3, str);
          Serial.println(str);
        }
        else{
          // do nothing if cannot get date & time from the internet
        }
      }
        
      // control fans and evaporator
      {
        // turn on fans & evap when the humidity is low
        if( humid < 80.0 ){
          evap_status = true;
        }
        // turn off fans & evap when the humidity is high and the temperature is low
        else if( humid>90.0 ){
          evap_status = false;
        }
        
        // turn on fans & evap when the temperature is high
        if( temp<25.0 ){
          fan_status[0] = fan_status[1] = fan_status[2] = false;
        }
        if( temp>27.5 ){
          evap_status = true;
          fan_status[0] = fan_status[1] = fan_status[2] = true;
        }
        digitalWrite( PIN_OUTPUT_PUMP_EVAPORATOR, evap_status );
        digitalWrite( PIN_OUTPUT_FAN_TOP, fan_status[0] );
        digitalWrite( PIN_OUTPUT_FAN_MIDDLE, fan_status[1] );
        digitalWrite( PIN_OUTPUT_FAN_BOTTOM, fan_status[2] );
      }
    }
    time_read_data = millis();
  }
}



// A funtion to check Wi-Fi status
void get_wifi_status(){
  // update status every 5 seconds
  if( uint32_t(millis()-time_wifi_status) < 5000 )
    return;

  // get Wi-Fi status. It will return a status code.
  uint8_t wifi_status_id;
  if( !smartfarm._wifi.get_status(&wifi_status_id) ){
    wifi_status_id = 99;
  }
  // Convert status code to a string
  // for more details : https://www.arduino.cc/en/Reference/WiFiStatus
  switch(wifi_status_id){
    case WL_NO_SHIELD:
      strcpy( wifi_status, "NO_SHIELD" );
      break;
    case WL_IDLE_STATUS:
      strcpy( wifi_status, "IDLE" );
      break;
    case WL_NO_SSID_AVAIL:
      strcpy( wifi_status, "NO_SSID" );
      break;
    case WL_SCAN_COMPLETED:
      strcpy( wifi_status, "SCAN_COMPLETED" );
      break;
    case WL_CONNECTED:
      strcpy( wifi_status, "CONNECTED" );
      break;
    case WL_CONNECT_FAILED:
      strcpy( wifi_status, "CONNECT FAILED" );
      break;
    case WL_CONNECTION_LOST:
      strcpy( wifi_status, "CONNECTION LOST" );
      break;
    case WL_DISCONNECTED:
      strcpy( wifi_status, "DISCONNECTED" );
      break;
    case 99:
      strcpy( wifi_status, "NO RESPONSE" );
      break;
    default:
      sprintf( wifi_status, "UNKNOWN %d", wifi_status_id );
  }
  time_wifi_status = millis();
}

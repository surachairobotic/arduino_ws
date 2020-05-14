#include <SoftwareSerial.h>
#include <MHZ.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <SD.h>

#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// pin for pwm reading
#define CO2_IN 10

// pin for uart reading
#define MH_Z19_RX 8  // D7
#define MH_Z19_TX 9  // D6

// change this to match your SD shield or module;
//     Arduino Ethernet shield: pin 4
//     Adafruit SD shields and modules: pin 10
//     Sparkfun SD shield: pin 8
const int chipSelect = 4;
File myFile;

MHZ co2(MH_Z19_RX, MH_Z19_TX, MHZ14A);
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
DHT dht1(A0, DHTTYPE), dht2(A1, DHTTYPE);

unsigned long long t_previous=0;
int ppm_uart, temperature;
float temp[2], humid[2];
char txt[16];

void setup() {
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  Serial.begin(9600);
  //pinMode(CO2_IN, INPUT);
  delay(100);
  Serial.println("MHZ 19B");

  // enable debug to get addition information
  co2.setDebug(false);

  /*
  if (co2.isPreHeating()) {
    Serial.print("Preheating");
    while (co2.isPreHeating()) {
      co2.get_timing(&t_current, &t_preheat);
      Serial.print(t_current);
      Serial.print(" : ");
      Serial.println(t_preheat);
      delay(1000);
    }
    Serial.println();
  }
  */

  dht1.begin();
  dht2.begin();


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  if( millis() - t_previous > 30000 ) {
    ppm_uart = co2.readCO2UART();
    Serial.print(millis() / 1000);
    Serial.print(" s : ");
    
    Serial.print("PPMuart: ");
    if (ppm_uart > 0) {
      Serial.print(ppm_uart);
    } else {
      Serial.print("n/a");
    }

    temperature = co2.getLastTemperature();
    Serial.print(", Temperature: ");
  
    if (temperature > 0) {
      Serial.println(temperature);
    } else {
      Serial.println("n/a");
    }
    t_previous = millis();

    humid[0] = dht1.readHumidity();
    temp[0] = dht1.readTemperature();
    humid[1] = dht2.readHumidity();
    temp[1] = dht2.readTemperature();

    Serial.print(humid[0]);
    Serial.print(", ");
    Serial.print(temp[0]);
    Serial.print(", ");
    Serial.print(humid[1]);
    Serial.print(", ");
    Serial.println(temp[1]);

    for(int i=0; i<2; i++) {
      // Check if any reads failed and exit early (to try again).
      if (isnan(humid[i])) {
        humid[i] = -1;
        Serial.println("humid is NAN");
      }
      if (isnan(temp[i])) {
        temp[i] = -1;
        Serial.println("temp is NAN");
      }
    }

    update_lcd();
    write_file();
  }

  /*
  int ppm_pwm = co2.readCO2PWM();
  Serial.print(", PPMpwm: ");
  Serial.print(ppm_pwm);
  */
}

void update_lcd() {
  lcd.clear();
  lcd.setCursor(0,0);
  sprintf(txt, "%s,%s,%d", String(temp[0]).c_str(), String(humid[0]).c_str(), ppm_uart);
  lcd.print(txt);
  lcd.setCursor(0,1);
  sprintf(txt, "%s,%s,%d", String(temp[1]).c_str(), String(humid[1]).c_str(), temperature);
  lcd.print(txt);  
}

void write_file() {
  myFile = SD.open("test.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    sprintf(txt, "%d", ppm_uart);
    myFile.print(txt);
    sprintf(txt, ",%s,%s", String(temp[0]).c_str(), String(humid[0]).c_str());
    myFile.print(txt);
    sprintf(txt, ",%s,%s", String(temp[1]).c_str(), String(humid[1]).c_str());
    myFile.println(txt);
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

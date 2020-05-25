// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 144 // Popular NeoPixel ring size

int pattern[4][3] = {{255,0,0}, {0,255,0}, {0,0,255}, {255,255,255}};
int i_pat=0, bright=0;

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 25 // Time (in milliseconds) to pause between pixels

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    String txt = Serial.readStringUntil('\r');
    Serial.println(txt);
    Serial.println(txt.length());
    txt.remove(txt.length()-1);
    Serial.println(txt);
    bright = txt.toInt();
    if( bright < 0 ) bright = 0;
    else if( bright > 255 ) bright = 255;
    else bright = 128;
    Serial.print("current bright : ");
    Serial.println(bright);
  }
  
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    //pixels.setPixelColor(i, pixels.Color(pattern[i_pat][0], pattern[i_pat][1], pattern[i_pat][2]));
    //pixels.setPixelColor(i, pixels.Color(255, 0, 255));
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.setBrightness(255);
    //pixels.setBrightness(255);

  }
  if(bright == 255)
    i_pat = (i_pat+1)%4;
  i_pat = 3;
  
  //bright = (bright+1);
  //if(bright > 255-32)
  //  bright = 255-32;
  pixels.show();   // Send the updated pixel colors to the hardware.

  delay(DELAYVAL); // Pause before next pass through loop
}

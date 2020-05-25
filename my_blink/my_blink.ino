/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

int led_pin[] = {9, 10, 11};
int pattern[8][3] = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1}, {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
int i_pat=0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //for(int i=0; i<3; i++)
  //  pinMode(led_pin[i], OUTPUT);
  for(int i : led_pin)
    pinMode(i, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  for(int i=0; i<3; i++)
    digitalWrite(led_pin[i], pattern[i_pat][i]);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  i_pat = (i_pat+1)%8;
}

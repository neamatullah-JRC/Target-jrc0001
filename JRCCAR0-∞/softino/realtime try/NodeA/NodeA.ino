/* Code for NODE A */

#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include "ssd1306.h"
#include "ssd1306_console.h"
Ssd1306Console  lcd;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 9 & 10 */
RF24 radio(9, 10);
/**********************************************************/

byte node_A_address[6] = "NodeA";
byte node_B_address[6] = "NodeB";

#define JoyStick_X_PIN     A0
#define JoyStick_Y_PIN     A1

struct CarData {
  byte fd;
  byte ld;
  byte rd;
  byte ch;
  byte lr;
  byte rr;
};
CarData cardata;

struct RmData {

  byte fw;
  byte bw;
  byte l;
  byte r;
};
RmData rmdata;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));

  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(node_B_address);
  radio.openReadingPipe(1, node_A_address);

  // Start the radio listening for data
  radio.startListening();
}

void loop() {
  int jx = map(analogRead(JoyStick_X_PIN), 0, 1023, 0, 255);
  int jy = map(analogRead(JoyStick_Y_PIN), 0, 1023, 0, 255);


  rmdata.fw = 0;
  rmdata.bw = 0;
  rmdata.l = 0;
  rmdata.r = 0;
  cardata.lr = 0;
  cardata.rr = 0;
  

  if (jx < 40)
  {
    Serial.print("forward");
    rmdata.fw = 1;
    rmdata.bw = 0;
    rmdata.l = 0;
    rmdata.r = 0;
  }
  else if (jx > 240)
  {
    Serial.print("backward");
    rmdata.fw = 0;
    rmdata.bw = 1;
    rmdata.l = 0;
    rmdata.r = 0;
  }

  else if (jy < 40)
  {
    Serial.print("right");
    rmdata.fw = 0;
    rmdata.bw = 0;
    rmdata.l = 0;
    rmdata.r = 1;
  }

  else if (jy > 240)
  {
    Serial.print("left");
    rmdata.fw = 0;
    rmdata.bw = 0;
    rmdata.l = 1;
    rmdata.r = 0;
  } else {
    Serial.print("stop");
    rmdata.fw = 0;
    rmdata.bw = 0;
    rmdata.l = 0;
    rmdata.r = 0;
  }

  radio.stopListening();                                    // First, stop listening so we can talk.

  Serial.println(F("Now sending Hello to node B"));

  char msg_to_B[20] = "Hello from node_A";                             // Take the time, and send it.  This will block until complete

  unsigned long start_time = micros();
  if (!radio.write( &rmdata, sizeof(RmData) )) {
    Serial.println(F("failed"));
  }

  radio.startListening();                                    // Now, continue listening

  unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

  while ( ! radio.available() ) {                            // While nothing is received
    if (micros() - started_waiting_at > 200000 ) {           // If waited longer than 200ms, indicate timeout and exit while loop
      timeout = true;
      break;
    }
  }

  if ( timeout ) {                                            // Describe the results
    Serial.println(F("Failed, response timed out."));
  } else {
    radio.read( &cardata, sizeof(CarData) );
    unsigned long end_time = micros();

    // Spew it
    Serial.print(F("Sent '"));
    Serial.print(msg_to_B);
    Serial.print(F("', Got response '"));
    Serial.println(cardata.fd);
    Serial.println(cardata.ld);
    Serial.println(cardata.rd);
    Serial.println(cardata.ch);
    Serial.println(cardata.lr);
    Serial.println(cardata.rr);
    Serial.println(F("'"));
    Serial.print(F("', Round-trip delay "));
    Serial.print(end_time - start_time);
    Serial.println(F(" microseconds"));
    lcd.setCursor(0, 1);
    lcd.print("front dist:");
    lcd.print(cardata.fd);
    lcd.print("cm");
    lcd.setCursor(1, 10);
    lcd.print("left dist:");
    lcd.print(cardata.ld);
    lcd.print("cm");
    lcd.setCursor(1, 20);
    lcd.print("right dist:");
    lcd.print(cardata.rd);
    lcd.print("cm");
    lcd.setCursor(1, 30);
    lcd.print("compass :");
    lcd.print(cardata.ch);
    lcd.print("d");
    lcd.setCursor(1, 35);
    lcd.print("left rpm:");
    lcd.print(cardata.lr);
    lcd.print("/m");
    lcd.setCursor(1, 40);
    lcd.print("right rpm:");
    lcd.print(cardata.rr);
    lcd.print("/m");

  }

  // Try again 1s later
  delay(10);
}

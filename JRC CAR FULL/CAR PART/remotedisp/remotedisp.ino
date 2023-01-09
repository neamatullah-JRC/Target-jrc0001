#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "ssd1306.h"
#include "ssd1306_console.h"



Ssd1306Console  lcd;
const uint64_t pipeIn = 0xE8E8F0F0E1LL;
RF24 radio(90, 10);



struct MyData {
  byte fd;
  byte ld;
  byte rd;
  int ch;
  byte lr;
  byte rr;
};
MyData data;
void setup()
{
  Serial.begin(9600);


  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font6x8);


  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, pipeIn);
  radio.startListening();
  lcd.print("ready");

  delay(500);
}
void recvData()
{
  if ( radio.available() ) {
    radio.read(&data, sizeof(MyData));
  }
}
void loop()
{
  radio.startListening();
  recvData();
  lcd.setCursor(0, 1);
  lcd.print("front dist:");
  lcd.print(data.fd);
  lcd.print("cm");
  lcd.setCursor(1, 10);
  lcd.print("left dist:");
  lcd.print(data.ld);
  lcd.print("cm");
  lcd.setCursor(1, 20);
  lcd.print("right dist:");
  lcd.print(data.rd);
  lcd.print("cm");
  lcd.setCursor(1, 30);
  lcd.print("compass :");
  lcd.print(data.ch);
  lcd.print("d");
  lcd.setCursor(1, 35);
  lcd.print("left rpm:");
  lcd.print(data.lr);
  lcd.print("/m");
  lcd.setCursor(1, 40);
  lcd.print("right rpm:");
  lcd.print(data.rr);
  lcd.print("/m");
 Serial.print(data.fd);
  Serial.print("  ");
  Serial.print(data.ld);
  Serial.print("  ");
  Serial.print(data.rd);
  Serial.print("  ");
  Serial.print(data.ch);
  Serial.print("  ");
  Serial.print(data.lr);
  Serial.print("  ");
  Serial.print(data.rr);
  Serial.print("  ");
  Serial.println("  ");
  //Serial.println(data.ch);

}

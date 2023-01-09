#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



#include <Wire.h> 
#include <MechaQMC5883.h> 

MechaQMC5883 qmc; 


#define TRIGGER1 22
#define TRIGGER2 24
#define TRIGGER3 26

#define ECHO1 23
#define ECHO2 25
#define ECHO3 27


long distance1=0; 
long distance2=0;
long distance3=0;




const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
RF24 radio(14, 15); //  CN and CSN  pins of nrf
struct MyData {
  byte fd;
  byte ld;
  byte rd;
  byte ch;
  byte lr;
  byte rr;
};
MyData data;




long measure(int trigger, int echo){
  long duration = 0;
  digitalWrite(trigger, LOW);  
  delay(5); 
  digitalWrite(trigger, HIGH); 
  delay(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH,11662); 
  return (duration/2) * 0.03432; 
}


void setup()
{
  Serial.begin(9600); 
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);

  
  pinMode(TRIGGER1, OUTPUT); 
  pinMode(ECHO1, INPUT); 
  pinMode(TRIGGER2, OUTPUT); 
  pinMode(ECHO2, INPUT); 
  pinMode(TRIGGER3, OUTPUT); 
  pinMode(ECHO3, INPUT); 

  Wire.begin();
  qmc.init();

}

void loop()
{
  distance1 = measure(TRIGGER1, ECHO1);
  distance2 = measure(TRIGGER2, ECHO2);
  distance3 = measure(TRIGGER3, ECHO3);
  int x,y,z;
  qmc.read(&x,&y,&z);
  int heading=atan2(x, y)/0.0174532925; 
    if(heading < 0) 
    heading+=360;
    heading = 360-heading;
  heading = map(heading,0,360,0,160);

  data.fd = distance1;
  data.ld = distance2;
  data.rd = distance3;
  data.ch = heading;
  data.lr = 200;
  data.rr = 200;
  radio.write(&data, sizeof(MyData));
  delay(5);
  

}

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

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
  int ch;
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
  Serial.println("Initialize HMC5883L");
  while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    delay(500);
  }
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);
  compass.setOffset(0, 0);
}

void loop()
{
  distance1 = measure(TRIGGER1, ECHO1);
  distance2 = measure(TRIGGER2, ECHO2);
  distance3 = measure(TRIGGER3, ECHO3);
  Vector norm = compass.readNormalize();

  float heading = atan2(norm.YAxis, norm.XAxis);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }
  float headingDegrees = heading * 180/M_PI; 
  data.fd = distance1;
  data.ld = distance2;
  data.rd = distance3;
  data.ch = headingDegrees;
  data.lr = 200;
  data.rr = 200;
  radio.write(&data, sizeof(MyData));
  delay(5);
  Serial.print(data.fd);
  Serial.print("  ");
  Serial.print(data.ld);
  Serial.print("  ");
  Serial.print(data.rd);
  Serial.print("  ");
  Serial.print(data.ch);
  Serial.println("  ");
  
  

}

 

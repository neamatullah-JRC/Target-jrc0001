/* Code for NODE B */

#include <SPI.h>
#include "RF24.h"
RF24 radio(14, 15);

byte node_A_address[6] = "NodeA";
byte node_B_address[6] = "NodeB";


#define TRIGGER1 22
#define TRIGGER2 24
#define TRIGGER3 26

#define ECHO1 23
#define ECHO2 25
#define ECHO3 27


long distance1=0; 
long distance2=0;
long distance3=0;


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




const byte MOTOR_A = 3;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 2;  // Motor 1 Interrupt Pin - INT 0 - Left Motor
const float stepcount = 20.00;
const float wheeldiameter = 66.10;
volatile int counter_A = 0;
volatile int counter_B = 0;


int enA = 9;
int in1 = 8;
int in2 = 7;
int enB = 4;
int in3 = 5;
int in4 = 6;

void ISR_countA()
{
  counter_A++;
}
void ISR_countB()
{
  counter_B++;
}
int CMtoSteps(float cm) {

  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step

  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)

  return result;  // End and return result

}

// Function to Move Forward
void MoveForward(int steps, int mspeed)
{
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero

  // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Go forward until step value is reached
  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
  }

  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;
  counter_B = 0;

}

void MoveReverse(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
  }

  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;
  counter_B = 0;

}

void SpinRight(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);


  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
  }
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;
  counter_B = 0;

}


void SpinLeft(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      analogWrite(enA, mspeed);
    } else {
      analogWrite(enA, 0);
    }
    if (steps > counter_B) {
      analogWrite(enB, mspeed);
    } else {
      analogWrite(enB, 0);
    }
  }
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  counter_A = 0;
  counter_B = 0;

}



void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High

  pinMode(TRIGGER1, OUTPUT); 
  pinMode(ECHO1, INPUT); 
  pinMode(TRIGGER2, OUTPUT); 
  pinMode(ECHO2, INPUT); 
  pinMode(TRIGGER3, OUTPUT); 
  pinMode(ECHO3, INPUT); 

  
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(node_A_address);
  radio.openReadingPipe(1, node_B_address);
  radio.startListening();
}

void loop() {
  /****************** Pong Back Role ***************************/
  

  if ( radio.available()) {
    while (radio.available()) { 
      radio.read( &rmdata, sizeof(RmData) );             
    }

    radio.stopListening();                                       
    radio.write( &cardata, sizeof(CarData) );              
    radio.startListening();                                    
/*
    Serial.print(F("Got message '"));
    Serial.println(rmdata.fw);
    Serial.println(rmdata.bw);
    Serial.println(rmdata.l);
    Serial.println(rmdata.r);
    Serial.print(F("', Sent response '"));
    Serial.println(cardata.fd);
    Serial.println(cardata.ld);
    Serial.println(cardata.rd);
    Serial.println(cardata.ch);
    Serial.println(cardata.lr);
    Serial.println(cardata.rr);
    Serial.println(F("'"));
  
*/
  if (rmdata.fw == 1 && rmdata.bw == 0 && rmdata.l == 0 && rmdata.r == 0)
  {
    MoveForward(CMtoSteps(5), 255);
  }
  else if (rmdata.fw == 0 && rmdata.bw == 1 && rmdata.l == 0 && rmdata.r == 0)
  {
    MoveReverse(CMtoSteps(5), 255);
  }  else if (rmdata.fw == 0 && rmdata.bw == 0 && rmdata.l == 0 && rmdata.r == 1)
  {
    SpinRight(CMtoSteps(5), 255);
  }  else if (rmdata.fw == 0 && rmdata.bw == 0 && rmdata.l == 1 && rmdata.r == 0)
  {
    SpinLeft(CMtoSteps(5), 255);
  }
}
distance1 = measure(TRIGGER1, ECHO1);
  distance2 = measure(TRIGGER2, ECHO2);
  distance3 = measure(TRIGGER3, ECHO3);
float rotation1 = (counter_A / stepcount) * 60.00;  // calculate RPM for Motor 2
float rotation2 = (counter_B / stepcount) * 60.00;  // calculate RPM for Motor 2
  
  cardata.fd = distance1;
  cardata.ld = distance2;
  cardata.rd = distance3;
  cardata.ch = 50;
  cardata.lr = rotation2;
  cardata.rr = rotation1;
}

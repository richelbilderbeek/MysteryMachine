#include <CapacitiveSensor.h>

/*
  MysteryMachine (using capacitive sensors)
  (C) 2015 Richel Bilderbeek


  Connecting the three sensors:
  
  2              3 
  |  +--------+  |
  +--+ R      +--+
  |  +--------+
  |
  X
  
  4              5 
  |  +--------+  |
  +--+ R      +--+
  |  +--------+
  |
  X

  A4             A5 
  |  +--------+  |
  +--+ R      +--+
  |  +--------+
  |
  X
  
  2,4,A4: sensor pins
  3,5,A5: helper pins
  R: resistance of at least 1 Mega-Ohm (brown-black-green-gold)
  X: place to touch wire
  
  Connecting the LEDs:

  Side 1:
  
   6 - LED1 -+
             |
   7 - LED2 -+- R - GND
             | 
   8 - LED3 -+

  Side 2:  

   9 - LED1 -+
             |
  10 - LED2 -+- R - GND
             | 
  11 - LED3 -+

  Center 2:  

  A0 - LED1 -+
             |
  A1 - LED2 -+- R - GND
             | 
  A2 - LED3 -+
  

   6: pin_1_1 (side 1, LED 1), red
   7: pin_1_2 (side 1, LED 2), yellow
   8: pin_1_3 (side 1, LED 3), green

   9: pin_2_1 (side 2, LED 1), red
  10: pin_2_2 (side 2, LED 2), yellow
  11: pin_2_3 (side 2, LED 3), green

  A0: pin_mid_1 (center, LED 1), red
  A1: pin_mid_2 (center, LED 2), red
  A2: pin_mid_3 (center, LED 3), red

  GND: Arduino pin GND, Earth
  R: resistance of at least 220 Ohm (red-red-brown-gold)
  
*/

//Show debug information in Serial Monitor?
const bool debug = false;

//Side 1
const int pin_sensor1 =  2;
const int pin_helper1 =  3;
const int pin_1_1     =  6;
const int pin_1_2     =  7;
const int pin_1_3     =  8;
CapacitiveSensor sensor1 
  = CapacitiveSensor(pin_helper1,pin_sensor1);        

//Side 2
const int pin_sensor2 =  4;
const int pin_helper2 =  5;
const int pin_2_1     =  9;
const int pin_2_2     = 10;
const int pin_2_3     = 11;
CapacitiveSensor sensor2 
  = CapacitiveSensor(pin_helper2,pin_sensor2);        

//Mid
const int pin_sensor3 = A4;
const int pin_helper3 = A5;
const int pin_mid_1   = A0;
const int pin_mid_2   = A1;
const int pin_mid_3   = A2;
CapacitiveSensor sensor3 
  = CapacitiveSensor(pin_helper3,pin_sensor3);        

//Which of player 1's LEDs is active?
int p1 = 0;
//Which of player 2's LEDs is active?
int p2 = 0;

void setup()                    
{
  pinMode(pin_1_1,OUTPUT);
  pinMode(pin_1_2,OUTPUT);
  pinMode(pin_1_3,OUTPUT);
  pinMode(pin_2_1,OUTPUT);
  pinMode(pin_2_2,OUTPUT);
  pinMode(pin_2_3,OUTPUT);
  pinMode(pin_mid_1,OUTPUT);
  pinMode(pin_mid_2,OUTPUT);
  pinMode(pin_mid_3,OUTPUT);
  Serial.begin(9600);
}

void loop()                    
{
  //The higher 'samples' is set, the more accurate the sensors measure
  const int samples = 30;

  //Measure the capacitive sensors
  const int r1 = sensor1.capacitiveSensor(samples);
  const int r2 = sensor2.capacitiveSensor(samples);
  const int r3 = sensor3.capacitiveSensor(samples);

  if (debug)
  {
    //Show the values in the Serial Monitor
    Serial.print(r1);
    Serial.print(" ");
    Serial.print(r2);
    Serial.print(" ");
    Serial.println(r3);
  }
  
  //The threshold value, which determines the sensitivity of the sensors
  // - too low: the program will think more often there is a touch, possibly even when you do not touch
  // - too high: the program will think less often there is a touch, possibly even when you do touch 
  const int t = 100;
  
  //Respond to touches
  if (r1 >= t) { p1 = (p1 + 1) % 3; }
  if (r2 >= t) { p2 = (p2 + 1) % 3; }
  const bool mid_pressed = r3 >= t;
  const int p_mid = (1 + p1 - p2 + 3) % 3;

  //Show the results  
  digitalWrite(pin_1_1,p1 == 0 ? HIGH : LOW);
  digitalWrite(pin_1_2,p1 == 1 ? HIGH : LOW);
  digitalWrite(pin_1_3,p1 == 2 ? HIGH : LOW);
  digitalWrite(pin_2_1,p2 == 0 ? HIGH : LOW);
  digitalWrite(pin_2_2,p2 == 1 ? HIGH : LOW);
  digitalWrite(pin_2_3,p2 == 2 ? HIGH : LOW);
  
  digitalWrite(pin_mid_1,mid_pressed && p_mid == 0 ? HIGH : LOW);
  digitalWrite(pin_mid_2,mid_pressed && p_mid == 1 ? HIGH : LOW);
  digitalWrite(pin_mid_3,mid_pressed && p_mid == 2 ? HIGH : LOW);
  
  delay(100);
}

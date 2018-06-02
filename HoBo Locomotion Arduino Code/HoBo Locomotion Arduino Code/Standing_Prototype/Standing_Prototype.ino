/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
 specific load cell setup.

 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE

 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.

*/

#include "HX711.h"
#include <Q2HX711.h>

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define CLK  2
#define DOUT_1  6
#define DOUT_2  5
#define DOUT_3  4
#define DOUT_4  3

HX711 scale_1(DOUT_1, CLK);
HX711 scale_2(DOUT_2, CLK);
HX711 scale_3(DOUT_3, CLK);
HX711 scale_4(DOUT_4, CLK);

float val1, val2, val3, val4;
float forward1 = 0, forward2 = 0, forward3 = 0, forward4 = 0; //Goes from left to right on the platform by vertical pairs of two
float backward1 = 0, backward2 = 0, backward3 = 0, backward4 = 0;
float neutral1 = 0, neutral2 = 0, neutral3 = 0, neutral4 = 0;
float left, right; //left = (1 + 2)/2, Right = (3 + 4)/2    May end up doing two values 
float leftNeutral, leftForward, leftBackward, leftOutput;
float rightNeutral, rightForward, rightBackward, rightOutput;
int mapLeft, mapRight;
char serialLeft, serialRight;
String output;

void haptic(){
  digitalWrite(8, HIGH);
  digitalWrite(7,LOW);
  analogWrite(9,80);
  delay(400);
//  delay(500);
  digitalWrite(8,LOW);
  digitalWrite(7, LOW);
}

void setup() {
  //Serial.begin(9600);
  Serial.begin(4800);
  Serial.println("HX711 scale demo");
  haptic();

  scale_1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale_1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale_2.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale_2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale_3.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale_3.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  scale_4.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale_4.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  //going to need to find new calibration factors for all these scales since we're using new HX711's

  Serial.println("Stand naturally until buzzer");
  delay(2500);
  int i;
  for(i = 0; i < 30; i++){
    neutral1 += scale_1.get_units()/50;  
    neutral2 += scale_2.get_units()/50;
    neutral3 += scale_3.get_units()/50;
    neutral4 += scale_4.get_units()/50;
    Serial.print("Working   ");
    Serial.println(i);
    delay(10);
  }

  //add in a timer to find the forward neutral
  //then for the backward neutral
  //then another resting neutrsl neutral

  Serial.print(neutral1);
  Serial.print("  ");
  Serial.print(neutral2);
  Serial.print("  ");
  Serial.print(neutral3);
  Serial.print("  ");
  Serial.print(neutral4);

  //Serial.println("\nPlease lean forward until buzzer.");
  haptic();
  delay(2500);

  int j;
  for(j = 0; j < 30; j++){
    forward1 += scale_1.get_units()/50;  
    forward2 += scale_2.get_units()/50;
    forward3 += scale_3.get_units()/50;
    forward4 += scale_4.get_units()/50;
    Serial.print("Working   ");
    Serial.println(j);
    delay(10);
  }

  Serial.print(forward1);
  Serial.print("  ");
  Serial.print(forward2);
  Serial.print("  ");
  Serial.print(forward3);
  Serial.print("  ");
  Serial.print(forward4);

  //Serial.println("\nPlease lean backward until buzzer.");
  haptic();
  delay(2500);

  int k;
  for(k = 0; k < 30; k++){
    backward1 += scale_1.get_units()/50;  
    backward2 += scale_2.get_units()/50;
    backward3 += scale_3.get_units()/50;
    backward4 += scale_4.get_units()/50;
    Serial.print("Working   ");
    Serial.println(k);
    delay(10);
  }

  Serial.print(backward1);
  Serial.print("  ");
  Serial.print(backward2);
  Serial.print("  ");
  Serial.print(backward3);
  Serial.print("  ");
  Serial.print(backward4);

  //Serial.println("\nPlease shift your wait to the middle once more until two buzzers");
  haptic();
  delay(2500);
  
  int l;
  for(l = 0; l < 30; l++){
    neutral1 += scale_1.get_units()/50;  
    neutral2 += scale_2.get_units()/50;
    neutral3 += scale_3.get_units()/50;
    neutral4 += scale_4.get_units()/50;
    Serial.print("Working   ");
    Serial.println(l);
    delay(10);
  }

  //add in a timer to find the forward neutral
  //then for the backward neutral
  //then another resting neutrsl neutral

  Serial.print(neutral1);
  Serial.print("  ");
  Serial.print(neutral2);
  Serial.print("  ");
  Serial.print(neutral3);
  Serial.print("  ");
  Serial.print(neutral4);
  Serial.println("");

  leftNeutral = (neutral1 + neutral2) / 2;
  leftForward = (forward1 + forward2) / 2;
  leftBackward = (backward1 + backward2) / 2;

  rightNeutral = (neutral3 + neutral4) / 2;
  rightForward = (forward3 + forward4) / 2;
  rightBackward = (backward3 + backward4) / 2;

  haptic();
  delay(200);
  haptic();
}

void loop() {
  /*
  Serial.print("Reading: ");

  val1 = scale_1.get_units() - neutral1;
  Serial.print(val1, 1); //scale.get_units() returns a float
  Serial.print(" lbs    "); //You can change this to kg but you'll need to refactor the calibration_factor

  val2 = scale_2.get_units() - neutral2;
  Serial.print(val2, 1); //scale.get_units() returns a float
  Serial.print(" lbs    "); //You can change this to kg but you'll need to refactor the calibration_factor

  val4 = scale_3.get_units() - neutral3;
  Serial.print(scale_3.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" lbs    "); //You can change this to kg but you'll need to refactor the calibration_factor

  val4 = scale_4.get_units() - neutral4;
  Serial.print(scale_4.get_units(), 1); //scale.get_units() returns a float
  Serial.print(" lbs    "); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  */
  left = (scale_1.get_units() + scale_2.get_units()) / 2;
  right = (scale_3.get_units() + scale_4.get_units()) / 2;

  if(left > leftNeutral){
    leftOutput = abs((left / leftForward)/2);

    if(leftOutput > 1){
      leftOutput = 1;
    }
  }else{
    leftOutput = abs((left / leftBackward)/2) * -1;

    if(leftOutput < -1){
      leftOutput = -1;
    }
  }

  if(right > rightNeutral){
    rightOutput = abs((right / rightForward)/2);

    if(rightOutput > 1){
      rightOutput = 1;
    }
  }else{
    rightOutput = abs((right / rightBackward)/2) * -1;

    if(rightOutput < -1){
      rightOutput = -1;
    }
  }

  mapLeft =  leftOutput * 512;
  mapRight = rightOutput * 512;

  mapLeft = map(mapLeft, -512, 512, 1, 254);
  mapRight = map(mapRight, -512, 512, 1, 254);

  serialLeft = (char)mapLeft;
  serialRight = (char)mapRight;

  /*
  Serial.print("Left Output: ");
  Serial.print(serialLeft);
  Serial.print("    Right Output: ");
  Serial.print(serialRight);
  Serial.println("");
  */

  Serial.write('0');
  Serial.write('0');
  Serial.write(serialLeft);
  Serial.write(serialRight);
  Serial.write('F');
  Serial.write('F');  
  Serial.println("");
}

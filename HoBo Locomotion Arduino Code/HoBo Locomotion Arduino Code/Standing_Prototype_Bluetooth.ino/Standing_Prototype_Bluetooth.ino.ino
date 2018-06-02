#include "HX711.h"
#include <Q2HX711.h>
#include <SoftwareSerial.h>

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define NUM_TRIALS 10
#define CLK  2
#define DOUT_1  6
#define DOUT_2  5
#define DOUT_3  4
#define DOUT_4  3

HX711 scale_1(DOUT_1, CLK);
HX711 scale_2(DOUT_2, CLK);
HX711 scale_3(DOUT_3, CLK);
HX711 scale_4(DOUT_4, CLK);

SoftwareSerial hc_08(10, 11);

float val1, val2, val3, val4;
float forward1 = 0, forward2 = 0, forward3 = 0, forward4 = 0; //Goes from left to right on the platform by vertical pairs of two
float backward1 = 0, backward2 = 0, backward3 = 0, backward4 = 0;
float neutral1 = 0, neutral2 = 0, neutral3 = 0, neutral4 = 0;
float left, right; //left = (1 + 2)/2, Right = (3 + 4)/2    May end up doing two values
float leftNeutral, leftForward, leftBackward;
float rightNeutral, rightForward, rightBackward;
uint8_t serialLeft, serialRight;
uint8_t head = 'A';
uint8_t tail = 'B';

void haptic() {
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  analogWrite(9, 80);
  delay(400);
  //  delay(500);
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
}

void setup() {
  Serial.begin(9600);
  hc_08.begin(9600);
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
  delay(2000);
  int i;
  for (i = 0; i < NUM_TRIALS ; i++) {
    neutral1 += scale_1.get_units() / NUM_TRIALS;
    neutral2 += scale_2.get_units() / NUM_TRIALS;
    neutral3 += scale_3.get_units() / NUM_TRIALS;
    neutral4 += scale_4.get_units() / NUM_TRIALS;
    Serial.print("Working   ");
    Serial.println(i);
    delay(10);
  }
  haptic();

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

  Serial.println("\nPlease lean forward until buzzer.");
  delay(2000);

  int j;
  for (j = 0; j < NUM_TRIALS; j++) {
    forward1 += scale_1.get_units() / NUM_TRIALS;
    forward2 += scale_2.get_units() / NUM_TRIALS;
    forward3 += scale_3.get_units() / NUM_TRIALS;
    forward4 += scale_4.get_units() / NUM_TRIALS;
    Serial.print("Working   ");
    Serial.println(j);
    delay(10);
  }
  haptic();

  Serial.print(forward1);
  Serial.print("  ");
  Serial.print(forward2);
  Serial.print("  ");
  Serial.print(forward3);
  Serial.print("  ");
  Serial.print(forward4);

  Serial.println("\nPlease lean backward until buzzer.");
  delay(2000);

  int k;
  for (k = 0; k < NUM_TRIALS; k++) {
    backward1 += scale_1.get_units() / NUM_TRIALS;
    backward2 += scale_2.get_units() / NUM_TRIALS;
    backward3 += scale_3.get_units() / NUM_TRIALS;
    backward4 += scale_4.get_units() / NUM_TRIALS;
    Serial.print("Working   ");
    Serial.println(k);
    delay(10);
  }
  haptic();

  Serial.print(backward1);
  Serial.print("  ");
  Serial.print(backward2);
  Serial.print("  ");
  Serial.print(backward3);
  Serial.print("  ");
  Serial.println(backward4);

  leftNeutral = (neutral1 + neutral2) / 2;
  leftForward = (forward1 + forward2) / 2 - leftNeutral;
  leftBackward = abs((backward1 + backward2) / 2 - leftNeutral);

  rightNeutral = (neutral3 + neutral4) / 2;
  rightForward = (forward3 + forward4) / 2 - rightNeutral;
  rightBackward = abs((backward3 + backward4) / 2 - rightNeutral);
  haptic();
  Serial.print("Configuring Bluetooth Connection");
  while (!hc_08.available()) {
    Serial.print(". ");
    delay(400);
    hc_08.listen();
    if (hc_08.available()) {
      Serial.println("BLUE");
      hc_08.flush();
      break;
    }
  }
  haptic();
  delay(200);
  haptic();
}

void loop() {
  val1 = (scale_1.get_units() - neutral1);
  val2 = (scale_2.get_units() - neutral2);
  val3 = (scale_3.get_units() - neutral3);
  val4 = (scale_4.get_units() - neutral4);

  left = (val1 + val2) / 2;
  right = (val3 + val4) / 2;

  serialLeft =  (char) map(left, -128, 128, 1, 254);
  serialRight =  (char) map(right, -128, 128, 1, 254);

  Serial.print("  Left Output: ");
  Serial.print(serialLeft, DEC);
  Serial.print("    Right Output: ");
  Serial.println(serialRight, DEC);

  hc_08.write(head);
  hc_08.write(serialLeft);
  hc_08.write(serialRight);
  hc_08.write(tail);
}

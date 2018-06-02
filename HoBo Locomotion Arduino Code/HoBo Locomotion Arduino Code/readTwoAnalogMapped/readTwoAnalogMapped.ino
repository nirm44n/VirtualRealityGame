#define HALF_RANGE 15


int leftPin = A0;    // select the input pin for the potentiometer
int rightPin = A1;    // select the input pin for the potentiometer

int LEDpin = 6;
int leftVal, leftAnal = 0;
int rightVal, rightAnal = 0;
int leftMid, leftLow, leftHi;
int rightMid, rightLow, rightHi;

void setup() {
  pinMode(LEDpin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
  leftMid = analogRead(leftPin);    // read the value from the sensor
  rightMid = analogRead(rightPin);
  leftLow = leftMid - HALF_RANGE;
  rightLow = rightMid - HALF_RANGE;
  leftHi = leftMid + HALF_RANGE;
  rightHi = rightMid + HALF_RANGE;
}

void loop() {
  
// analogVal = map(analogRead(inPin),0,1023,-512,512);    // read the value from the sensor
leftAnal = analogRead(leftPin);    // read the value from the sensor
rightAnal = analogRead(rightPin);
if (leftAnal > leftHi){
    leftHi = leftAnal;
  }
if (rightAnal > rightHi){
    rightHi = rightAnal;
  }
if (leftAnal < leftLow){
    leftLow = leftAnal;
  }
if (rightAnal < rightLow){
    rightLow = rightAnal;
  }    
 
leftVal = map(leftAnal, leftLow,leftHi,512,-512);    // read the value from the sensor
rightVal = map(rightAnal,rightLow,rightHi,-512,512);    // read the value from the sensor
//  pwmLED = map(analogRead(inPin),0,1023,0,255);    // read the value from the sensor
//  analogWrite(LEDpin,pwmLED);
//  Serial.print("LeftMid: ");
//  Serial.print(leftMid);
  Serial.print("Left Value: " );
  Serial.print(leftVal);  
  Serial.print("Right Value: " );
  Serial.print(rightVal);  
//    Serial.print("Left Anal: " );
//  Serial.print(leftAnal);  
//  Serial.print("Right Anal: " );
//  Serial.println(rightAnal);  
Serial.println();
}

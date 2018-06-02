#define HALF_RANGE 50


int leftPin = A0;    // select the input pin for the potentiometer
int rightPin = A1;    // select the input pin for the potentiometer

int LEDpin = 6;
int leftVal, leftAnal = 0;
int rightVal, rightAnal = 0;
float leftMid, leftLow, leftHi;
float rightMid, rightLow, rightHi;

void setup() {
	pinMode(LEDpin, OUTPUT);  // declare the ledPin as an OUTPUT
	Serial.begin(9600);

	// ADD NO MOVEMENT WINDOW FOR CALIBRATION 0

	// FINE TUNE SCALING WINDOW
	delay(500);
	float leftSum,rightSum = 0;
	//int leftMin,leftMax;
	//int rightMin,rightMax;
	for(int i = 0; i < 1000; ++i){
		delay(3);
		leftVal = analogRead(leftPin);
		rightVal = analogRead(rightPin);
		leftSum += leftVal;
		rightSum += rightVal;
	}
	leftMid = (leftSum)/1000.0;
	rightMid = (rightSum)/1000.0;

	leftLow = leftMid - HALF_RANGE;
	rightLow = rightMid - HALF_RANGE;
	leftHi = leftMid + HALF_RANGE;
	rightHi = rightMid + HALF_RANGE;
}

void loop() {
	leftAnal = analogRead(leftPin);    // read the value from the sensor
	rightAnal = analogRead(rightPin);

	
	   if (leftAnal > leftHi) leftHi = leftAnal;
	   if (rightAnal > rightHi) rightHi = rightAnal;
	   if (leftAnal < leftLow) leftLow = leftAnal;
	   if (rightAnal < rightLow) rightLow = rightAnal;

	leftVal = map(leftAnal, leftLow,leftHi,-512,512);    // read the value from the sensor
	rightVal = map(rightAnal,rightLow,rightHi,-512,512);    // read the value from the sensor
	/*
	Serial.print("LeftMid: ");
	Serial.print(leftMid);
	Serial.print("Left Anal: " );
	Serial.print(leftAnal);  
	Serial.print("Left Low: " );
	Serial.print(leftLow);  
	Serial.print("Left Hi: " );
	Serial.print(leftHi);  
*/
	/*if (rightVal < -512) rightValDisc = -512;
	else if (rightVal < -480) rightValDisc = -480;
	else if (rightVal < -360) rightValDisc = -360;
	else if (rightVal < -240) rightValDisc = -240;
	else if (rightVal < -120) rightValDisc = -120;
	else if (rightVal < 120) rightValDisc = 0;
	else if (rightVal < 240) rightValDisc= 120;
	else if (rightVal < 360) rightValDisc = 240;
	else if (rightVal < 480) rightValDisc = 360;
	else rightVal = 480;
	if (leftVal < -512) leftVal = -512;
	else if (leftVal < -480) leftVal = -480;
	else if (leftVal < -360) leftVal = -360;
	else if (leftVal < -240) leftVal = -240;
	else if (leftVal < -120) leftVal = -120;
	else if (leftVal < 120) leftVal = 0;
	else if (leftVal < 240) leftVal = 120;
	else if (leftVal < 360) leftVal = 240;
	else if (leftVal < 480) leftVal = 360;
	else leftVal = 480;
*/
	//Serial.print("Left Value: " );
	//Serial.print(leftVal);  
	Serial.print("\tRight Value: " );
	Serial.print(rightVal);  
	    //Serial.print("Left Anal: " );
	 //Serial.print(leftAnal);  
	  Serial.print("Right Anal: " );
	  Serial.println(rightAnal);  
	Serial.println();
}

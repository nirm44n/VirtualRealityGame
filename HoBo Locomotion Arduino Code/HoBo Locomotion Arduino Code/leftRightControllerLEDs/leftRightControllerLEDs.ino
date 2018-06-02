int rightPin = A0;    // select the input pin for the potentiometer
int leftPin = A1;    // select the input pin for the potentiometer
int ledPin = 13;   // select the pin for the LED
int lLED = 6;
int rLED = 5;
int right = 0;       // variable to store the value coming from the sensor
int left = 0;       // variable to store the value coming from the sensor
int rPWM = 0;
int lPWM = 0;

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
}

void loop() {
//  right = analogRead(rightPin) - 512;    // read the value from the sensor
//  left = analogRead(leftPin) - 512;    // read the value from the sensor
  right = map(analogRead(rightPin),0,1023,-512,512);    // read the value from the sensor
  left = map(analogRead(leftPin),0,1023,-512,512);    // read the value from the sensor
  rPWM = map(analogRead(rightPin),0,1023,0,255);    // read the value from the sensor
  lPWM = map(analogRead(leftPin),0,1023,0,255);    // read the value from the sensor
  analogWrite(lLED,lPWM);
  analogWrite(rLED,rPWM);
  Serial.print("Left Value: " );
  Serial.print(left);
  Serial.print(" Right Value: " );
  Serial.println(right);  
  
}

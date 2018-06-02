int inPin = A1;    // select the input pin for the potentiometer
int LEDpin = 6;
int analogVal = 0;
//int pwmLED = 0;

void setup() {
  pinMode(LEDpin, OUTPUT);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);
}

void loop() {
  analogVal = map(analogRead(inPin),0,1023,-512,512);    // read the value from the sensor
//  pwmLED = map(analogRead(inPin),0,1023,0,255);    // read the value from the sensor
//  analogWrite(LEDpin,pwmLED);
  Serial.print("Analog Value: " );
  Serial.println(analogVal);  
}

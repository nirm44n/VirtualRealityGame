/*
Basic accelerometer recognition
*/

int led = 13;
int xPin = A0;
int yPin = A1;
int zPin = A2;

void setup() 
{
	pinMode(led, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	int xVal = analogRead(xPin);
	int yVal = analogRead(yPin);
	int zVal = analogRead(zPin);
	Serial.println(xVal);
	Serial.println(yVal);
	Serial.println(zVal);
	// Values at rest x & y = 330; z = 400
	// Check for movement
	if(xVal < 310 || xVal >350 || yVal < 310 || yVal > 350 || zVal < 380 || zVal > 420)
	{
		digitalWrite(led, HIGH);
		delay(300);
		digitalWrite(led, LOW);
	}
	delay(100);
}

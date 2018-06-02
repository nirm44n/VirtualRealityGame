/*
Basic passive infrared sensor recognition
*/

int led = 13;
int sensorPin = 2;

void setup() 
{
	pinMode(led, OUTPUT);
	pinMode(sensorPin, INPUT_PULLUP);
	delay(3000);
}

void loop()
{
	if(digitalRead(sensorPin) == LOW)
	{
		digitalWrite(led, HIGH);
		delay(1000);
		digitalWrite(led, LOW);
	}
}

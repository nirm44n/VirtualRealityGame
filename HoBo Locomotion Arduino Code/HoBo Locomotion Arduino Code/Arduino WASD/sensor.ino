/*
Basic sensor recognition
*/

int led = 13;
int sensorPin = A2;

void setup() 
{
	pinMode(led, OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	int val = analogRead(sensorPin);
	Serial.println(val);
	digitalWrite(led, HIGH);
	delay(val/4);
	digitalWrite(led, LOW);
	delay(val/4);

}

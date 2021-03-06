#include <SoftwareSerial.h>
const int rxPin = 4; //SoftwareSerial RX pin, connect to SH-M08 TX pin
const int txPin = 2; //SoftwareSerial TX pin, connect to SH-M08 RX pin
                     // level shifting to 3.3 volts may be needed
SoftwareSerial mySerial(rxPin, txPin); // RX, TX
const int ledPin = 13;  // led pin
int state = 0;        // if state is 1, the LED will turn on and
                      // if state is 0, the LED will turn off
int flag = 0;         // a flag to prevent duplicate messages

void setup() {
    // sets the pins as outputs:
    pinMode(ledPin, OUTPUT);
    mySerial.begin(9600);
    digitalWrite(ledPin, LOW); // LED is initially off
}

void loop() {
    //reads serial input and saves it in the state variable
    if(mySerial.available() > 0)
    {
      state = mySerial.read();
      flag=0; //clear the flag so we can print the state
    }
    // if the state is '0' the LED will turn off
    if (state == '0') 
    {
        digitalWrite(ledPin, LOW);
        if(flag == 0)
        {
          mySerial.println("LED: off");
          flag = 1;
        }
    }
    // if the state is '1' the led will turn on
    else if (state == '1') 
    {
        digitalWrite(ledPin, HIGH);
        if(flag == 0)
        {
          mySerial.println("LED: on");
          flag = 1;
        }
    }
}


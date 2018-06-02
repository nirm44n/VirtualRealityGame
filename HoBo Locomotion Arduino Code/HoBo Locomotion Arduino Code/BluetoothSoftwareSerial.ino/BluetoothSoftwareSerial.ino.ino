#include <SoftwareSerial.h>
#include <String.h>

int availableLEDpin = 13;
SoftwareSerial hc_08(9,10); // RX-9, TX-10

void setup() {
  pinMode(availableLEDpin, OUTPUT);
  Serial.begin(9600);
  hc_08.begin(9600);
}

void loop() {
  hc_08.listen();
  if (hc_08.available()) {
    //Serial.print((char)(hc_08.read()));
    Serial.write((hc_08.read()));
    hc_08.write("char\n");
    digitalWrite(availableLEDpin, HIGH);
  }
  else {
    digitalWrite(availableLEDpin, LOW);
    Serial.println();
  }
  delay(100);
}

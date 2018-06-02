#include "Ardunity.h"
#include "AnalogInput.h"

AnalogInput aInput1(1, A1);
AnalogInput aInput0(0, A0);

void setup()
{
  ArdunityApp.attachController((ArdunityController*)&aInput1);
  ArdunityApp.attachController((ArdunityController*)&aInput0);
  ArdunityApp.resolution(256, 1024);
  ArdunityApp.timeout(5000);
  ArdunityApp.begin(9600);
}

void loop()
{
  ArdunityApp.process();
}

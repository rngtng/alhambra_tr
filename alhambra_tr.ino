#include "RGBdriver.h"

#define CLK 2//pins definitions for the driver
#define DIO 3

RGBdriver Driver(CLK,DIO);

int pause;

void setup()
{
  pinMode(7, OUTPUT);
}

void loop()
{
  Driver.begin();
  Driver.SetColor(255,0,0);
  Driver.end();
  digitalWrite(7, HIGH);

  pause = random(5000);
  delay(pause);


  Driver.begin();
  Driver.SetColor(0,230,230);
  Driver.end();
  digitalWrite(7, LOW);

  pause = random(2000);
  delay(pause);
}

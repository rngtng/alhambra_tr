#include "RGBdriver.h"

#define CLK 1//pins definitions for the driver
#define DIO 2

RGBdriver Driver(CLK,DIO);

int pause;

void setup()
{
}

void loop()
{
  Driver.begin();
  Driver.SetColor(255,230,230);
  Driver.end();

  pause = random(5000);
  delay(pause);


  Driver.begin();
  Driver.SetColor(0,0,0);
  Driver.end();

  pause = random(2000);
  delay(pause);
}

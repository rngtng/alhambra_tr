#include "RGBdriver.h"
#include <Ultrasonic.h>

#define CLK 1//pins definitions for the driver
#define DIO 2
RGBdriver Driver(CLK,DIO);
Ultrasonic ultrasonic(7);

int distance;
int x;

void setup()
{

}

void loop()
{

  ultrasonic.MeasureInCentimeters();
  distance = ultrasonic.RangeInCentimeters;

  if(distance > 100) {
    x = 0;
  }
  else {
    x = 255 - (255 * distance / 100);
  }

  Driver.begin();
  Driver.SetColor(x, x, x);
  Driver.end();
  delay(10);
}

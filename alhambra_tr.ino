#include "RGBdriver.h"
#include <Ultrasonic.h>

#include <SerialLCD.h>
#include <SoftwareSerial.h> //this is a must

#define CLK 2//pins definitions for the driver
#define DIO 3

#define DISTANCE_SENSOR 7
#define SOUND_SENSOR A0

SerialLCD slcd(11,12);
RGBdriver Driver(CLK,DIO);
Ultrasonic ultrasonic(DISTANCE_SENSOR);

int distance;
int x;
int last_x;

int m;

void setup()
{
  pinMode(SOUND_SENSOR, INPUT);

//   slcd.begin();
//   slcd.backlight();
//   slcd.clear();
//   slcd.setCursor(0,0);
//   slcd.print("The distance:");
}

void loop()
{
  // ultrasonic.MeasureInCentimeters();
  // distance = ultrasonic.RangeInCentimeters - 40;

  x = analogRead(SOUND_SENSOR);

  // slcd.setCursor(0,1);
  // slcd.print("    ");
  // slcd.setCursor(0,1);
  // slcd.print(x,DEC);

  // slcd.setCursor(5,1);
  // slcd.print("    ");
  // slcd.setCursor(5,1);
  // slcd.print(m,DEC);

  // if(distance < 0) {
  //   distance = 0;
  // }

  // if(distance > 100) {
  //   x = 0;
  // }
  // else {
  //   x = 255 - (255 * distance / 100);
  // }

  if(last_x < x) {
    x = ( 5 * last_x + x) / 6;
  }

  if(last_x > x) {
    x = ( 5 * last_x + x) / 6;
  }

  // if(m < x) {
  //   m = x;
  // }

 int j = x;
  Driver.begin();
  Driver.SetColor(j,j,j);
  Driver.end();
  delay(10);
  last_x = x;
}

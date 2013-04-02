#include <RGBdriver.h>
#include <Ultrasonic.h>

#include <SerialLCD.h>
#include <SoftwareSerial.h>

#define RGB_PORT              2
#define DISPLAY_PORT         11
#define DISTANCE_SENSOR_PORT  7
#define SOUND_SENSOR_PORT    A0  //Analog

#ifdef DISPLAY_PORT
SerialLCD slcd(DISPLAY_PORT, DISPLAY_PORT+1);

#ifdef RGB_PORT
RGBdriver Driver(RGB_PORT, RGB_PORT+1);

#ifdef DISTANCE_SENSOR_PORT
Ultrasonic ultrasonic(DISTANCE_SENSOR_PORT);


init_sound_sensor

//#############################################

void setup()
{
  init_sound_sensor();
  pinMode(SOUND_SENSOR, INPUT);

//   slcd.begin();
//   slcd.backlight();
//   slcd.clear();
//   slcd.setCursor(0,0);
//   slcd.print("The distance:");
}

//#############################################

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

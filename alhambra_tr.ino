#include <Ultrasonic.h>
#include <RGBdriver.h>
#include <SerialLCD.h>
#include <SoftwareSerial.h>

#define DISTANCE_SENSOR_PORT  7
#define SOUND_SENSOR_PORT    A0  // Analog
#define RGB_PORT              2
#define DISPLAY_PORT         11

#ifdef DISTANCE_SENSOR_PORT
Ultrasonic ultrasonic(DISTANCE_SENSOR_PORT);
#endif

#ifdef RGB_PORT
RGBdriver Driver(RGB_PORT, RGB_PORT+1);
#endif

#ifdef DISPLAY_PORT
SerialLCD slcd(DISPLAY_PORT, DISPLAY_PORT+1);
#endif

//############ setups ##########################

void setup_distance_sensor() {
  DISTANCE_MIN =  40; // cm
  DISTANCE_MAX = 150; // cm
}

void setup_sound_sensor() {
  SOUND_MIN =   0;
  SOUND_MAX = 400; // max is 1024
  pinMode(SOUND_SENSOR_PORT, INPUT);
}

void setup_rgb() {
  RGB_DELAY_INCREACE = 2;
  RGB_DELAY_DECREACE = 6;
}

void setup_display() {
  slcd.begin();
  slcd.backlight();
  slcd.clear();
  slcd.setCursor(0,0);
}

void setup() {
  setup_sound_sensor();
  setup_display();
}

//############ helper ##########################

int normalise(int value, int lower, int upper) {
  if( value < lower) { value = lower; }
  if( value > upper) { value = upper; }
  value = 255 * (value - lower) / (upper - lower);
  return value;
}

int delayy(int value, int previous_value, int factor) { //TODO better name :)
  return ((factor - 1) * last_value + value) / factor;
}

int delayz(int value, int last_value, int inc, int dec) {  //TODO better name :)
  if(last_value < value) { // increasing
    last_value = delayy(value, last_value, inc)
  }
  if(last_value >= value) { // decreasing
    last_value = delayy(value, last_value, dec)
  }
  return last_value;
}

//############ GETS  ###############################

int get_distance() {
  ultrasonic.MeasureInCentimeters();
  int distance = ultrasonic.RangeInCentimeters;
  return normalise(distance, DISTANCE_MIN, DISTANCE_MAX);
}

int get_sound() {
  int sound = analogRead(SOUND_SENSOR_PORT);
  return normalise(sound, SOUND_MIN, SOUND_MAX);
}

//############# SETS ################################

void set_rgb(int color) {
  Driver.begin();
  Driver.SetColor(color, color, color);
  Driver.end();
}

void set_display(int x, int y, int value) {
  slcd.setCursor(x, y);
  slcd.print("    "); // clean 4 digits - TODO be smater here?
  slcd.setCursor(x, y);
  slcd.print(value, DEC);
}

//############ main ##########################

void loop() {
  delayz(color, previous_color, RGB_DELAY_INCREACE, RGB_DELAY_DECREACE);

  delay(10);
  last_x = x;
}

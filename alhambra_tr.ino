#include <Ultrasonic.h>
#include <RGBdriver.h>
#include <SerialLCD.h>
#include <SoftwareSerial.h>

#define DISTANCE_SENSOR_PORT  7
#define SOUND_SENSOR_PORT    A0  // Analog
#define RGB_PORT              2
#define DISPLAY_PORT         11

#define DISTANCE_MIN  40 // cm
#define DISTANCE_MAX 150 // cm

#define SOUND_MIN   0
#define SOUND_MAX 400    // max is 1024

#define RANDOM_OFF 2000  // milli seconds
#define RANDOM_ON  5000  // milli seconds

#define RGB_DELAY_INCREACE 2
#define RGB_DELAY_DECREACE 6

#define LOOP_DELAY 10

#define NORM_FACTOR 255

#ifdef DISTANCE_SENSOR_PORT
Ultrasonic ultrasonic(DISTANCE_SENSOR_PORT);
#endif

#ifdef RGB_PORT
RGBdriver Driver(RGB_PORT, RGB_PORT+1);
#endif

#ifdef DISPLAY_PORT
SerialLCD slcd(DISPLAY_PORT, DISPLAY_PORT+1);
#endif

int color          = 0;
int previous_color = 0;

int random_loops   = 0;
bool random_on     = true;

//############ setups ##########################

void setup_sound_sensor() {
  pinMode(SOUND_SENSOR_PORT, INPUT);
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
  value = NORM_FACTOR * (value - lower) / (upper - lower);
  return value;
}

int inverse(int value) {
  return NORM_FACTOR - value;
}

int _hesitate(int value, int previous_value, int factor) {
  return ((factor - 1) * previous_value + value) / factor;
}

int hesitate(int value, int last_value, int inc, int dec) {
  if(last_value < value) { // increasing
    last_value = _hesitate(value, last_value, inc);
  }
  else {  // decreasing
    last_value = _hesitate(value, last_value, dec);
  }
  return last_value;
}

int randomRead() {
  if(random_loops > 0) {
    random_loops -= LOOP_DELAY;
  }
  else {
    random_on = !random_on;
    random_loops = random((random_on) ? RANDOM_ON : RANDOM_OFF);
  }
  return (random_on) ? 1 : 0;
}

//############ GETS  ###############################

int get_distance() { // returns 0 = nearby, 1 = most
  ultrasonic.MeasureInCentimeters();
  int distance = ultrasonic.RangeInCentimeters;
  distance     = normalise(distance, DISTANCE_MIN, DISTANCE_MAX);
  return distance;
}

int get_sound() { // returns 0 = silent, 1 = noisy
  int sound = analogRead(SOUND_SENSOR_PORT);
  sound     = normalise(sound, SOUND_MIN, SOUND_MAX);
  return sound;
}

int get_random() { // returns 0 = off, 1 = on
  int randomv = randomRead();
  randomv     = normalise(randomv, 0, 1);
  return randomv;
}

//############# SETS ################################

void set_rgb(int color) {
  Driver.begin();
  Driver.SetColor(color, color, color);
  Driver.end();
}

void set_display(int x, int y, int value) {
  slcd.setCursor(x, y);
  slcd.print("    "); // clean 4 digits - TODO be smarter here?
  slcd.setCursor(x, y);
  slcd.print(value, DEC);
}

//############ main ##########################

void loop() {
  color          = get_distance();
  //color          = get_sound();
  //color          = get_random();

  previous_color = hesitate(color, previous_color, RGB_DELAY_INCREACE, RGB_DELAY_DECREACE);

  set_display(0,0, previous_color);

  set_rgb(previous_color);

  delay(LOOP_DELAY);
}

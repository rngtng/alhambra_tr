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
  value = (value - lower) / (upper - lower);
  return value;
}

int delayy(int value, int previous_value, int factor) { //TODO better name :)
  return ((factor - 1) * previous_value + value) / factor;
}

int delayz(int value, int last_value, int inc, int dec) {  //TODO better name :)
  if(last_value < value) { // increasing
    last_value = delayy(value, last_value, inc);
  }
  else { // decreasing
    last_value = delayy(value, last_value, dec);
  }
  return last_value;
}

//############ GETS  ###############################

int get_distance() {
  ultrasonic.MeasureInCentimeters();
  int distance = ultrasonic.RangeInCentimeters;
  distance = normalise(distance, DISTANCE_MIN, DISTANCE_MAX);
  return distance;
}

int get_sound() {
  int sound = analogRead(SOUND_SENSOR_PORT);
  sound = normalise(sound, SOUND_MIN, SOUND_MAX);
  return sound;
}

int get_random() {
  if(random_loops > 0) {
    random_loops -= LOOP_DELAY;
  }
  else {
    random_on = !random_on;
    random_loops = random((random_on) ? RANDOM_ON : RANDOM_OFF);
  }
  return (random_on) ? 1 : 0;
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

  previous_color = delayz(color, previous_color, RGB_DELAY_INCREACE, RGB_DELAY_DECREACE);

  set_display(0,0, 255 * previous_color)

  set_rgb(255 * previous_color);

  delay(LOOP_DELAY);
}

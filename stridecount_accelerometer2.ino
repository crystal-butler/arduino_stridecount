#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <EEPROM.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

int i = 0;
float smooth = 0;
const float c = 0.1;
float x_acc;
float x_acc_norm;
int strideup = 0;
int stridedown = 0;
int stridestate = -1;
int oldstridestate = -1;
int stridecount = 0;

void setup() 
{
  Serial.begin(9600);
  if(!accel.begin())
  {
    while(1);
  }
}

void loop() 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  if (stridecount == 255) {
    stridecount = 0;
    i++;
  }
  x_acc = event.acceleration.x;
  smooth = (1-c) * smooth + (c * x_acc);
  x_acc_norm = (x_acc - smooth) * 10;
  if (x_acc_norm > 0) {
      strideup++;
  }
  if (x_acc_norm <= 0) {
    stridedown++;
  }
  if (strideup == 1) {
    stridestate = 1;
  }
  if (stridedown == 1) {
    stridestate = -1;
  }
  strideup = 0;
  stridedown = 0;
 if ((stridestate == 1) && (stridestate != oldstridestate)) {
    stridecount++;
    EEPROM.write(i, stridecount);
 }
 oldstridestate = stridestate;
    delay(25);
}

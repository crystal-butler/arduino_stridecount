

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <EEPROM.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
// const int analogOutPin = 9; // Analog output pin that the LED is attached to
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

/* void displaySensorDetails()
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
} */

void setup() 
{
 // Serial.begin(9600);
 // Serial.println("Accelerometer Test"); Serial.println("");
  
  // pinMode (analogOutPin, OUTPUT); 
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    // Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  
  /* Display some basic information on this sensor */
 // displaySensorDetails();
}

void loop() 
{
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);
  
   /* Display the results (acceleration is measured in m/s^2) */
    if (stridecount == 254) {
      stridecount = 0;
      i++;
    }
    x_acc = event.acceleration.x;
    smooth = (1-c) * smooth + (c * x_acc);
    x_acc_norm = x_acc - smooth;
    if (x_acc_norm > 0) {
      strideup++;
    } else {
      stridedown++;
    }
    if (strideup >= 3) {
      stridestate = 1;
    } else {
      stridestate = -1;
    }
    if ((stridestate == 1) && (stridestate != oldstridestate)) {
      stridecount++;
      EEPROM.write(i, stridecount);
      strideup = 0;
      stridedown = 0;
    }
    oldstridestate = stridestate;
    
    delay(50);
}

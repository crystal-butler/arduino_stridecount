/*gather a set of test volatge values for an IR distance sensor
to use as the basis for distance calculation */

int sensorValue = 0;  // variable for volatage readings
int sensorPin = A0;   // input pin for IR sensor

void setup() {
  
  Serial.begin(9600); 
  pinMode(sensorPin, INPUT);

}

void loop() {
    
    sensorValue = analogRead(sensorPin);
    Serial.print(sensorValue );
    Serial.print(' ');

}

//#include <JeeLib.h>

float thresholdVoltage = 0.5;
int dividerRatio = 10;
float runningVoltage = 3.3;
int solarVoltagePin = A3;
int ledOutputPin = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(ledOutputPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(solarVoltagePin);

  //Serial.println(sensorValue);

  float voltage = sensorValue * (runningVoltage / 1023.0) * dividerRatio;

  //Serial.println(voltage);
  
  if (voltage < thresholdVoltage)
    digitalWrite(ledOutputPin, HIGH);
  else
    digitalWrite(ledOutputPin, LOW);
    
    delay(100);
  //Sleepy::loseSomeTime(5000);
}

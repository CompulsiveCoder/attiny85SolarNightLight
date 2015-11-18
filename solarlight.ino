int thresholdPin = A2;
int dividerRatio = 10;
float runningVoltage = 3.3;
int solarVoltagePin = A3;
int ledOutputPin = 0;

void setup() {
  pinMode(ledOutputPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(solarVoltagePin);
  int thresholdRawValue = analogRead(thresholdPin);

  float voltage = sensorValue * (runningVoltage / 1023.0) * dividerRatio;

  float thresholdVoltage = (thresholdRawValue / 1023.0) * 5;
  
  if (voltage < thresholdVoltage)
    digitalWrite(ledOutputPin, HIGH);
  else
    digitalWrite(ledOutputPin, LOW);

  delay(100);
}

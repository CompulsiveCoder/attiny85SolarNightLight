#define solarVoltageDividerRatio 10
#define solarVoltagePin A3
#define solarThresholdPin A2

double runningVoltage = 3.3;

int ledOutputPin = 0;

float batteryLowVoltageThreshold = 3; // absolute minimum is 3

void setup() {
  pinMode(ledOutputPin, OUTPUT);
}

void loop() {
  int solarReading = analogRead(solarVoltagePin);
  int thresholdRawValue = analogRead(solarThresholdPin);

  float solarVoltage = solarReading * (runningVoltage / 1023.0) * solarVoltageDividerRatio;

  float solarVoltageThreshold = (thresholdRawValue / 1023.0) * 5;

  float batteryVoltage = readVcc();
  
  if (solarVoltage < solarVoltageThreshold
    && batteryVoltage > batteryLowVoltageThreshold)
    digitalWrite(ledOutputPin, HIGH);
  else
    digitalWrite(ledOutputPin, LOW);

  delay(100);
}

long readVcc() {
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  
 
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring
 
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both
 
  long result = (high<<8) | low;
 
  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}


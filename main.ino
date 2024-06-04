const int moistPin = 34; // Moisture sensor pin
const int pumpPin = 25;  // Pump control pin

int moistValue = 0;

// Define the known dry and wet values for calibration
const int dryValue = 2000;
const int wetValue = 1600;
const int moistureThreshold = 30; // Threshold below which the pump will turn on

void setup() {
  Serial.begin(9600);
  delay(1000);
  analogSetPinAttenuation(moistPin, ADC_11db); // Optional: set ADC attenuation

  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW); // Ensure pump is off initially
}

void loop() {
  moistValue = analogRead(moistPin);

  // Map the values to a percentage
  int moistPercent = map(moistValue, wetValue, dryValue, 100, 0);
  moistPercent = constrain(moistPercent, 0, 100); // Ensure value is within 0-100%

  Serial.print("Analog output: ");
  Serial.print(moistValue);
  Serial.print(" - Moisture Level: ");
  Serial.print(moistPercent);
  Serial.println("%");

  // Control the pump based on the moisture level
  if (moistPercent < moistureThreshold) {
    digitalWrite(pumpPin, HIGH); // Turn on the pump
    Serial.println("Pump ON");
  } else {
    digitalWrite(pumpPin, LOW); // Turn off the pump
    Serial.println("Pump OFF");
  }

  delay(1000);
}

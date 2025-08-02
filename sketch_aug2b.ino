const int batteryPin = A0; // Battery voltage via voltage divider
const int chargeControlPin = 8; // Control charging (e.g., MOSFET)
const int dischargeControlPin = 9; // Control discharging

float voltage = 0.0;

void setup() {
  pinMode(chargeControlPin, OUTPUT);
  pinMode(dischargeControlPin, OUTPUT);
  digitalWrite(chargeControlPin, LOW);
  digitalWrite(dischargeControlPin, LOW);
  
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(batteryPin);
  
  // Convert ADC value to actual voltage (assuming 10-bit ADC and 5V ref)
  voltage = (raw * 5.0 / 1023.0) * 2; // Multiply by 2 because of voltage divider

  Serial.print("Battery Voltage: ");
  Serial.println(voltage);

  // Charging logic
  if (voltage < 4.1) {
    digitalWrite(chargeControlPin, HIGH); // Allow charging
  } else {
    digitalWrite(chargeControlPin, LOW);  // Stop charging
  }

  // Discharging logic
  if (voltage > 3.2) {
    digitalWrite(dischargeControlPin, HIGH); // Allow discharging
  } else {
    digitalWrite(dischargeControlPin, LOW);  // Stop discharging to protect battery
  }

  delay(1000);
}

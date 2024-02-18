
#include <DHT.h>

// Define the analog pin the moisture sensor is connected to
const int moistureSensorPin = A0;
// Define the analog pin the additional sensor is connected to
const int photoresistorPin = A1;
// Define the digital pin the DHT11 sensor is connected to
const int dhtPin = 2;

// Initialize DHT sensor
DHT dht(dhtPin, DHT11);

void setup() {
  // Start serial communication
  Serial.begin(9600);
  pinMode(moistureSensorPin, INPUT);
  pinMode(photoresistorPin, INPUT);

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read sensor data
  int moistureLevel = analogRead(moistureSensorPin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int lightValue = analogRead(photoresistorPin);

  // Send sensor data to ESP32
  Serial.print("M");
  Serial.print(moistureLevel);
  Serial.print("H");
  Serial.print(humidity);
  Serial.print("T");
  Serial.print(temperature);
  Serial.print("L");
  Serial.println(lightValue);

  // Add a delay to prevent flooding the Serial Monitor
  delay(1000); // 1 second delay
}

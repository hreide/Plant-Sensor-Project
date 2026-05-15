/*
  ESP32 Environmental Sensor Node

  Reads:
    - Capacitive analog soil moisture sensor
    - BH1750 light sensor over I2C
    - BME280 temperature/humidity/pressure sensor over I2C

  Outputs CSV over USB serial.

  Target platform:
    ESP32 Arduino framework

  Libraries to install:
    - BH1750 by Christopher Laws
    - Adafruit BME280 Library
    - Adafruit Unified Sensor
*/

#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_BME280.h>

// ESP32 I2C pins. Change if your board uses a different routing.
static constexpr int I2C_SDA_PIN = 21;
static constexpr int I2C_SCL_PIN = 22;

// Use an ADC-capable GPIO pin for the soil moisture sensor.
// Update this pin to match your wiring.
static constexpr int SOIL_ADC_PIN = 34;

static constexpr uint32_t SERIAL_BAUD = 115200;
static constexpr uint32_t SAMPLE_PERIOD_MS = 1000;

BH1750 lightMeter;
Adafruit_BME280 bme;

bool bh1750_ok = false;
bool bme280_ok = false;
uint32_t last_sample_ms = 0;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(500);

  analogReadResolution(12);  // ESP32 ADC range: 0-4095
  pinMode(SOIL_ADC_PIN, INPUT);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  bh1750_ok = lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);
  bme280_ok = bme.begin(0x76);  // Common BME280 addresses are 0x76 and 0x77.

  if (!bme280_ok) {
    bme280_ok = bme.begin(0x77);
  }

  Serial.println("timestamp_ms,soil_raw,light_lux,temp_c,humidity_pct,pressure_hpa");
}

void loop() {
  const uint32_t now_ms = millis();
  if (now_ms - last_sample_ms < SAMPLE_PERIOD_MS) {
    return;
  }
  last_sample_ms = now_ms;

  const int soil_raw = analogRead(SOIL_ADC_PIN);

  float light_lux = NAN;
  float temp_c = NAN;
  float humidity_pct = NAN;
  float pressure_hpa = NAN;

  if (bh1750_ok) {
    light_lux = lightMeter.readLightLevel();
  }

  if (bme280_ok) {
    temp_c = bme.readTemperature();
    humidity_pct = bme.readHumidity();
    pressure_hpa = bme.readPressure() / 100.0F;
  }

  Serial.print(now_ms);
  Serial.print(',');
  Serial.print(soil_raw);
  Serial.print(',');
  Serial.print(light_lux, 2);
  Serial.print(',');
  Serial.print(temp_c, 2);
  Serial.print(',');
  Serial.print(humidity_pct, 2);
  Serial.print(',');
  Serial.println(pressure_hpa, 2);
}

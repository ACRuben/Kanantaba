/* ---------------------------------- make2explore.com----------------------------------------------------*/
// Project           - Reyax LoRa Module RYLR998 Testing - IoT mini Project - Remote GreenHouse Monitoring
// Created By        - blog@make2explore.com
// Version - 1.0     - Sender Code
// Last Modified     - 31/05/2022 20:36:00 @admin
// Software          - C/C++, Arduino IDE, ESP8266 SDK, Libraries
// Hardware          - NodeMCU ESP8266, Reyax LoRa RYLR998 Module, DS18B20 Temperature Sensor, Relay Module              
// Sensors Used      - DS18B20 Temperature Sensor, Soil Moisture Sensor
// Source Repo       - github.com/make2explore
/* -------------------------------------------------------------------------------------------------------*/
// LoRa Module Configurations Transmitter Node
String lora_band = "915000000";     // Enter LoRa band as per your country
String lora_networkid = "7";        // Enter Lora Network ID - Must be same for Tx and Rx Nodes
String lora_TX_address = "126";     // Enter Lora RX address

#include <SoftwareSerial.h>         // include Software Serial library
#include <OneWire.h>                // include OneWire library
#include <DallasTemperature.h>      // include DallasTemperature library

const byte rxPin = D7;              // Software Serial Pins Rx and Tx
const byte txPin = D8;
              
const int sensor_pin = D2                                                                                                                                                                                                    ;          // Connect Soil moisture analog sensor pin to A0 of NodeMCU
//const int Relay1_Pump = D6;         // Connect Relay to D6 of NodeMCU

// Set up a new SoftwareSerial object
SoftwareSerial sendLoRa(rxPin, txPin);   // Software Serial Pins Rx=D7 and Tx=D8

// Set up a new OneWire object
OneWire oneWire(D5);                // Data wire is connected to GPIO D5 (NodeMCU Pin D1)
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);               // Initialize the Serial Monitor
  sendLoRa.begin(9600);             // Initialize the Software Serial for LoRa Module
  sensors.begin();                  // Initialize the DS18B20 temperature sensor
}

void loop() {
  float temperature = getTemperature();   // Read temperature from DS18B20 sensor
  int soilMoisture = analogRead(sensor_pin);   // Read soil moisture level

  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoisture);

  // Transmit the temperature and soil moisture values over LoRa
  sendLoRa.println("Temperature: " + String(temperature) + " C");
  sendLoRa.println("Soil Moisture: " + String(soilMoisture));

  delay(5000);  // Delay for 5 seconds
}

float getTemperature() {
  sensors.requestTemperatures();     // Send the command to get temperatures

  // Read temperature in Celsius
  float temperature = sensors.getTempCByIndex(0);
  return temperature;
}

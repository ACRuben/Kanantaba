#include <SX126x.h>
#include <SPI.h>
#include <RadioLib.h>

// Define los pines de conexión del SX1262
#define LORA_SS       10
#define LORA_DIO1     2
#define LORA_RESET    6
#define LORA_BW       125000
#define LORA_SF       7
#define LORA_CR       4/5
#define LORA_POWER    20

SX126x radio = new SX126x(LORA_SS, LORA_DIO1, LORA_RESET);

// Define una cadena de datos a enviar al otro módulo LoRa
char txData[] = "Hola, esto es una prueba.";

// Define las variables que almacenarán los datos recibidos
char rxData[100];
int rxCount = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  radio.setFrequency(915000000);
  radio.setBandwidth(LORA_BW);
  radio.setSpreadingFactor(LORA_SF);
  radio.setCodingRate4(LORA_CR);
  radio.setTxPower(LORA_POWER);
  Serial.println("[LoRa] Initialized.");
}

void loop() {
  // Envía los datos cada 10 segundos
  radio.transmit(txData, sizeof(txData));
  Serial.println("[LoRa] Datos enviados.");
  delay(10000);
}

#include <SoftwareSerial.h>

// Configuración del módulo LoRa
SoftwareSerial loraSerial(D7, D8); // RX, TX (conexiones del módulo LoRa al ESP8266)

// Configuración del LED
const int ledPin = 4; // Pin del LED

void setup() {
  // Configurar el puerto serial para la comunicación con la consola
  Serial.begin(9600);

  // Configurar el puerto serial para la comunicación con el módulo LoRa
  loraSerial.begin(9600);

  // Configurar el pin del LED como salida
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    // Si hay datos disponibles en el puerto serial, leerlos y enviarlos a través del módulo LoRa
    char c = Serial.read();
    loraSerial.print(c);

    // Encender el LED
    digitalWrite(ledPin, HIGH);
  }

  if (loraSerial.available()) {
    // Si hay datos disponibles en el módulo LoRa, leerlos y enviarlos a través del puerto serial
    char c = loraSerial.read();
    Serial.print(c);

    // Encender el LED
    digitalWrite(ledPin, HIGH);
  }

  // Si no hay datos disponibles en ninguna de las comunicaciones
  // apagar el LED
  digitalWrite(ledPin, LOW);
}

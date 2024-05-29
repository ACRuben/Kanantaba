#include <esp_now.h>
#include <WiFi.h>

// Estado de la comunicación
bool communicationStatus = false;

// Callback que se ejecuta cuando se recibe un mensaje del dispositivo maestro
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  // Verificar si la longitud de los datos recibidos es válida
  if (data_len >= 1) {
    // Actualizar el estado de la comunicación
    communicationStatus = data[0];
    //digitalWrite(LED, data[0]);
  }
}

void setup() {
  // Inicializar el LED integrado
  #define LED 2
  pinMode(LED, OUTPUT);
  
  // Inicializar el protocolo ESP-NOW
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(WIFI_PS_NONE);  // Deshabilitar el ahorro de energía
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error al inicializar ESP-NOW");
    return;
  }
  
  // Registrar el callback para recibir datos
  esp_now_register_recv_cb(OnDataRecv);
  
  Serial.begin(115200);  // Iniciar comunicación con el Monitor Serial
  Serial.println("Dispositivo esclavo listo");
  Serial.println("Esperando conexión del dispositivo maestro...");
}

void loop() {
  // Verificar el estado de la comunicación
  if (communicationStatus) {
    // Encender el LED intermitentemente si hay comunicación
    digitalWrite(LED, (millis() / 500) % 2 == 0 ? HIGH : LOW);
    Serial.println("Comunicación en línea");
  } 
  else{
    // Mantener el LED encendido si se pierde la comunicación
    digitalWrite(LED, HIGH);
    Serial.println("Comunicación interrumpida");
  }
}

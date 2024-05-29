#include <esp_now.h>
#include <WiFi.h>
#define LED 2
// Dirección MAC del dispositivo esclavo
uint8_t slaveMac[] = {0x7C, 0x9E, 0xBD, 0x66, 0x68, 0xDC};

// Estado de la comunicación
bool communicationStatus = false;

// Callback que se ejecuta cuando se recibe un mensaje del dispositivo esclavo
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
  Serial.println("Dispositivo maestro listo");
  Serial.println("Conectando al dispositivo esclavo...");

  // Agregar el dispositivo esclavo
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, slaveMac, 6);
  peerInfo.channel = 0;  // Canal de comunicación
  peerInfo.encrypt = false;  // Sin encriptación
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Error al agregar el dispositivo esclavo");
    return;
  }
  Serial.println("Dispositivo Maestro LISTO!!!");
}

void loop() {
  // Enviar un mensaje al dispositivo esclavo para indicar la comunicación
  uint8_t data = 1;  // Valor para indicar la comunicación
  esp_now_send(slaveMac, &data, 1);
  delay(1000);  // Esperar 1 segundo
  
  // Verificar el estado de la comunicación
  if (communicationStatus) {
    // Encender el LED para indicar que hay comunicación
    digitalWrite(LED, HIGH);
    Serial.println("Comunicación en línea");
  } else {
    // Apagar el LED si se pierde la comunicación
    digitalWrite(LED, LOW);
    Serial.println("Comunicación interrumpida");
  }
}

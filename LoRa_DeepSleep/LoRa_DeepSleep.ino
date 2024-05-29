#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 5
String lora_band = "915000000"; //Banda de frecuencia (Hz)
String lora_networkid = "18";   //Identificación de la red Lora
String lora_address = "1";      //Dirección del módulo
String lora_RX_address = "2";   //Dirección del módulo receptor

RTC_DATA_ATTR int bootCount = 0;
int led = 21;

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}


   
void setup(){
  
  Serial2.begin(115200,SERIAL_8N1, 16,17);
  pinMode(led,OUTPUT);
  
  delay(1500);
  Serial2.println("AT+BAND=" + lora_band);
  delay(500);
  Serial2.println("AT+ADDRESS=" + lora_address);
  delay(500);
  Serial2.println("AT+NETWORKID=" + lora_networkid);
  delay(1500);

  Serial.begin(115200);
  delay(1000);

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  print_wakeup_reason();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println(
     "Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP)
     + " Seconds"
    );
  digitalWrite(led, HIGH);
   Serial2.println("AT+SEND="+ lora_RX_address +",2,ON"); 
   delay(1000);
  digitalWrite(led, LOW);
  delay(5000);
    Serial.println("Going to sleep now");
    Serial.flush();
    esp_deep_sleep_start();
    Serial.println("This will never be prnted");
}

void loop()
{
//  delay(100);
//  digitalWrite(led, HIGH);
//   Serial2.println("AT+SEND="+ lora_RX_address +",2,ON"); 
//   delay(1000);
//  digitalWrite(led, LOW);
//  delay(1000);
//  if(digitalRead(pulsador) == LOW){
//    digitalWrite(led, HIGH);
//    Serial2.println("AT+SEND="+ lora_RX_address +",2,ON");  
//  }else{
//     digitalWrite(led, LOW);
//  }
}

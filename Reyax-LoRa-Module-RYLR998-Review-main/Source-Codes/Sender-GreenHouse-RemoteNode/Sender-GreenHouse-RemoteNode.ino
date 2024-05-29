String lora_band = "915000000"; //Banda de frecuencia (Hz)
String lora_networkid = "18";   //Identificación de la red Lora
String lora_address = "1";      //Dirección del módulo
String lora_RX_address = "2";   //Dirección del módulo receptor

int led = 21;
   
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
  

}

void loop()
{
  delay(100);
  digitalWrite(led, HIGH);
   Serial2.println("AT+SEND="+ lora_RX_address +",2,ON"); 
   delay(1000);
  digitalWrite(led, LOW);
  delay(1000);
  
   /*if(digitalRead(pulsador) == LOW){
    digitalWrite(led, HIGH);
    Serial2.println("AT+SEND="+ lora_RX_address +",2,ON");  
  }else{
     digitalWrite(led, LOW);
  }*/
}

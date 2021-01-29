#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Ping.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>
#define BLYNK_PRINT Serial // Defines the object that is used for printing
#define BLYNK_DEBUG        // Optional, this enables more detailed prints
WiFiUDP UDP;
WakeOnLan WOL(UDP);
#define LED 32

char auth[] = "TOKEN";
char ssid[] = "SSID";
char pass[] = "PASS";
const IPAddress remote_ip(10, 136, 213, 166);

int LED_Flag = 0;
int Flag2=0;

WidgetTerminal terminal(V3);


void setup()
{
  WOL.setRepeat(3, 100);
  //LED settings
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  delay(200);
  
  Serial.begin(115200);

  WiFi.begin(ssid, pass);
  int i = 0;

  while (WiFi.status() != WL_CONNECTED) {
    if(i==10){
      WiFi.begin(ssid, pass);
      i=0;
     
    }
    else{
       delay(1000);
       Serial.print("F");
       i++;
    }

  }

  Blynk.config(auth);
  Blynk.connect(30);

  while (Blynk.connect() != true) {
       delay(1000);
       Serial.print("B");
  }

  


  Serial.println("connected");
}
WidgetLED led1(V1);
WidgetLED led2(V2);
void loop()
{
  Blynk.run();
  Ping_fn();

}


BLYNK_WRITE(V0)
{
  const char *MACAddress = "A8:A1:59:37:D1:1C";
  LED_Flag = param.asInt();
  if(LED_Flag == 1){
    digitalWrite(LED,LOW);
    led2.on();

    //WOL.sendMagicPacket(MACAddress);
    //Serial.println("WoL");

  }
  else if(LED_Flag==0){
    digitalWrite(LED,HIGH);
    led2.off();

  }
}


int count=0;
void Ping_fn(){
  if(count==10000){
    
    if(Ping.ping(remote_ip)) {
      Serial.println("Success!!");
      led1.on();
    } 
    else {
      led1.off();
      Serial.println("Error :(");
    }
    count=0;
    Serial.println(count);
  }
  else{
    count+=1;
    Serial.println(count);
    terminal.println(count);
  }
}

 

/* 
 *  This code is for an end-device running on an M5Core2 for AWS
 *  The purpose of this code snip is to check the wi-Fi and reconnect 
 *  if the connection is lost. In the file there is also examples of how to reconnect 
 *  the mqtt client to the server.
 *  It is connecting to an MQTT broker over WiFi and TCP/IP
 *  Subscribing to: 
 *  Publiching to: 
 *  Device ID is xx
 *
 *  Mogens Iversen & Ib Helmer Nielsen - UCN/2023
 */
#define DEBUG             // Enable DBPRINT
#define VERSION "0.10"    
#include "DebugUtils.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <M5Core2.h>

// Custom colour1: Yellow
#define RED_VAL_1       255
#define GREEN_VAL_1     255
#define BLUE_VAL_1      0

// Constants
// IoT Device
// Subscription and publish channel
#define      DEVID     "esp99"
#define      DEVCLIENT "esp99Client"
#define      LED1SUB   "esp99/Led1"
#define      LED2SUB   "esp99/Led2"
#define      LED3SUB   "esp99/Led3"
#define      SW1PUB    "esp99/Sw1"
#define      AN0PUB    "esp99/An0"
#define      TEMPPUB   "esp99/Temp"
#define      HUMPUB    "esp99/Hum"
#define      NEORSUB   "esp99/NeoRed"
#define      NEOGSUB   "esp99/NeoGreen"
#define      NEOBSUB   "esp99/NeoBlue"

// Measurement setup and constants

// WiFi Setup and constants
#include "wifi_setup.h"
#define  WIFI_TIMEOUT_MS  20000               // Time between wifi connection check

// MQTT Broker address and port
const char * mqtt_server = "mqtt.sof60.dk";   // Host name of MQTT broker
const uint16_t mqtt_port = 1883;              // TCP port used by the MQTT broker


// Objects 
WiFiClient esp32;                                     // WiFi
//PubSubClient client(esp32);                           // MQTT client object

portMUX_TYPE taskMux = portMUX_INITIALIZER_UNLOCKED;  // Mutex for locking critical code regions

void setup()
{
    Serial.begin(115200);
    M5.begin();  // Init M5Core2
    // Setup ESP's Pin's
    // Setup MQTT Client
    //client.setServer(mqtt_server, mqtt_port);
    //client.setCallback(callback);
    // Setup WiFi task for ensuring connection to WiFi
    xTaskCreatePinnedToCore(
      keepWiFiAlive,
      "Keep WiFi Alive",
      4096,
      NULL,
      1,
      NULL,
      CONFIG_ARDUINO_RUNNING_CORE
    );
//    xTaskCreatePinnedToCore(
//      measurement,
//      "Measurement task",
//      4096,
//      NULL,
//      1,
//      NULL,
//      CONFIG_ARDUINO_RUNNING_CORE
//    );
//    xTaskCreatePinnedToCore(
//      keyscan,
//      "Key scanning task",
//      4096,
//      NULL,
//      1,
//      NULL,
//      CONFIG_ARDUINO_RUNNING_CORE
//    );       
}

void keepWiFiAlive(void * parameters){
  for(;;){
    if(WiFi.status() == WL_CONNECTED){
      DBPRINTLN("WiFi is connected");
      vTaskDelay(10000 / portTICK_PERIOD_MS);
      continue; 
    }
    DBPRINTLN("WiFi is not connected\n");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passwd);
    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS){}
    if (WiFi.status() != WL_CONNECTED){
      DBPRINTLN("WiFi Failed!!");
      vTaskDelay(20000 / portTICK_PERIOD_MS);
      continue;
    }
    DBPRINT("WiFi is Connected : "); // 
    DBPRINTLN(WiFi.localIP());
    M5.Lcd.SetTextColor(YELLOW,BLACK);
    M5.Lcd.print(WiFi.localIP());
  }
}

// Variables

/*
void callback(char* topic, byte* message, unsigned int length) {
  String messageTemp; 
}

void reconnect() {
  // Loop until reconnected
  while (!client.connected()) {
   // lcd.setRGB(colorHalf, colorNo, colorNo); // Display red if not connected to broker
    DBPRINT("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(DEVCLIENT)) {
      DBPRINTLN("connected");
      // Subscribe to channel
      client.subscribe(LED1SUB);
      client.subscribe(LED2SUB);
      client.subscribe(LED3SUB);
      client.subscribe(NEORSUB);
      client.subscribe(NEOGSUB);
      client.subscribe(NEOBSUB);   
    } else {
      DBPRINT("failed, rc=");
      DBPRINTLN(client.state());
      DBPRINTLN("Try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
 // lcd.setRGB(colorNo, colorHalf, colorNo); // Display geeen if connected to broker
}

void keyscan(void * parameters){
  int sw1State = 0;
  int lastSw1State = 0;
  for(;;)
  {
    sw1State = digitalRead(sw1Pin);
    if (sw1State != lastSw1State){
      if (sw1State==HIGH)
      {
        client.publish(SW1PUB,"on");
        DBPRINTLN("SW1 Pressed");
      } else {
        client.publish(SW1PUB,"off");
      } 
      lastSw1State = sw1State;
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);  
  }
}

void measurement(void * parameters){

  char rstr[7]; // Buffer big enough for 6-character float
  for(;;)
  {
    portENTER_CRITICAL (&taskMux);
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    portEXIT_CRITICAL(&taskMux);
    if (isnan(h) || isnan(t)){
      DBPRINTLN("Measurement error");
    }
    else { 
      DBPRINT(h);
      DBPRINT(" , ");
      DBPRINTLN(t);
      dtostrf(t, 3, 2, rstr);
      client.publish(TEMPPUB,rstr);
      dtostrf(h, 3, 2, rstr);
      client.publish(HUMPUB,rstr);
    }
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
*/
void loop()
{
 // if (!client.connected()) {
 //     reconnect();
 //   }
 //   client.loop();
    //vTaskDelay(10/portTICK_PERIOD_MS);
}

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <DHT.h>
#include <TaskScheduler.h>
#include <string.h>


WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

#define LED_PIN 13
#define DHTPIN 12
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi Connected");

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  //client.begin(AWS_IOT_ENDPOINT, 8883, net);

  client.setServer(AWS_IOT_ENDPOINT, 8883);
  client.connect(THINGNAME);

  // Create a message handler
  client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    client.connect(THINGNAME);
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

// We declare the function that we are going to use
void read_dht();

// We create the Scheduler that will be in charge of managing the tasks
Scheduler runner;

// We create the task indicating that it runs every 500 milliseconds, forever, and call the led_blink function
Task readDHT(2000, TASK_FOREVER, &read_dht);

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["time"] = millis();
  doc["sensor_a0"] = analogRead(0);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(char* topic, byte* payload, unsigned int length) {
  
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();


    //contol LED
    if ((char)payload[0] == '1') {   
      digitalWrite(LED_PIN,1);
      Serial.print("Turning on LED");
    }
    else if ((char)payload[0] == '0') {
      digitalWrite(LED_PIN,0);
      Serial.print("Turning off LED");
    }
    
    Serial.println();
}

void setup() {
  Serial.begin(115200);
  connectAWS();

  pinMode (LED_PIN, OUTPUT);

  dht.begin();

  // We add the task to the task scheduler
  runner.addTask(readDHT);
  
  // We activate the task
  readDHT.enable();
}

void loop() {
  client.loop();
  runner.execute();
  delay(10);
}

void read_dht(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

   StaticJsonDocument<200> doc;
   doc["device_id"] = THINGNAME;

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
   
    doc["temperature"] = "0";
    doc["humidity"] = "0";
   
  }
  else{
   
    doc["temperature"] = String(t);
    doc["humidity"] = String(h);
    
  }
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

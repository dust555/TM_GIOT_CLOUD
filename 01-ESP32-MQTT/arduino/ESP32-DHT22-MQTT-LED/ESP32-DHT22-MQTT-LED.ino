#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <TaskScheduler.h>


const char* ssid = "GraduaatIOT"; // Enter your WiFi name
const char* password =  "CloudAndSecurity101"; // Enter WiFi password
const char* mqtt_server  = "10.54.32.1";
const int mqtt_port  = 1883;
//const char* mqttUser = "eapcfltj";
//const char* mqttPassword = "3EjMIy89qzVn";
#define MQTT_SERIAL_PUBLISH_CH "u0118137/measurement"
#define MQTT_SERIAL_RECEIVER_CH "u0118137/led"
const String DEVICE_ID = "u0118137";

#define LED_PIN 13
#define DHTPIN 32
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifiClient;

PubSubClient client(wifiClient);

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish("u0118137/connected", "hello world");
      // ... and resubscribe
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {

   int value = (int) *payload;
  
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();


    //contol LED
    if(value == 49){                //1 in ASCII
      digitalWrite(LED_PIN,1);
      Serial.print("Turning on LED");
    }
    else if(value == 48){         //0 in ASCII
      digitalWrite(LED_PIN,0);
      Serial.print("Turning off LED");
    }
    
    Serial.println();
}



// We declare the function that we are going to use
void read_dht();

// We create the Scheduler that will be in charge of managing the tasks
Scheduler runner;

// We create the task indicating that it runs every 500 milliseconds, forever, and call the led_blink function
Task readDHT(2000, TASK_FOREVER, &read_dht);

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();

  pinMode (LED_PIN, OUTPUT);

  dht.begin();

  // We add the task to the task scheduler
  runner.addTask(readDHT);
  
  // We activate the task
  readDHT.enable();
  
}

void publishSerialData(char *serialData){
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH_CH, serialData);
}




void loop() {
   client.loop();
//   if (Serial.available() > 0) {
//     char mun[501];
//     memset(mun,0, 501);
//     Serial.readBytesUntil( '\n',mun,500);
//     publishSerialData(mun);
//   }

  runner.execute();
   delay(10);
   
}
void read_dht(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else{
    String json = "{\"device_id\":\""+DEVICE_ID+"\",\"temperature\":\""+String(t)+"\",\"humidity\":\""+String(h)+"\"}";
    char jsondata[json.length()+1];
    json.toCharArray(jsondata,json.length());
    publishSerialData(jsondata);
  }
}

 

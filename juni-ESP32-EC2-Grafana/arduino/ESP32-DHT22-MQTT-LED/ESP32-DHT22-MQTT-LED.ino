#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>


//use one of the following:
//const String serverName = "http://<EC2_IP>/api.php";
//const String serverName = "http://<DNS_NAME>/api.php";
//const String serverName = "https://<DNS_NAME>/api.php";


#define ssid "<WIFI_SSID>"
#define password "<WIFI_PASSWORD>"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

WiFiClient wifiClient;

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


// We declare the function that we are going to use
void read_dht();


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
  
  dht.begin();

 
}


void loop() {
  read_dht();
  delay(5000);
   
}


void read_dht(){
  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  else{
    if(WiFi.status()!= WL_CONNECTED){
      Serial.println("WiFi Disconnected");
    }
    else{
      HTTPClient http;
      
      String temp = String(t);
      String serverPath = serverName + "?temp="+String(t);
  
      http.begin(serverPath.c_str());
  
      int httpResponseCode = http.GET();
  
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
    }
  }
}

 

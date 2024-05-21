#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
WiFiClient client;
HTTPClient http;


DHT dht(22, DHT22);

const char * ssid="progettotemperatura"; 
const char * wifipw="progettotemperatura";


void setup(){
  dht.begin();
  Serial.begin(115200);
  startWifi();
  Serial.println("");
  Serial.println("WiFi connected.");
  delay (3000);
}

void loop() {
  float t = gettemperatura();
  Serial.println(t);
  String buf;
  buf = F("http://10.0.3.94:5000/add?aula=MM1&valore=");
  buf += String (t);
  Serial.println(buf);
  String oj = httpGETRequest(buf);
  delay(5000);
    
}

float gettemperatura(){
  float temp;
  temp = dht.readTemperature();
  Serial.println(temp);  
  return temp;
}

void  startWifi(){
  WiFi.begin(ssid, wifipw);
  Serial.println("Connecting Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
}

void  segnale_rssi(){
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wifi RSSI=");
  Serial.println(WiFi.RSSI());
}

String httpGETRequest(String serverName) {
  WiFiClient client;
  HTTPClient http;
  
  http.begin(client, serverName);
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}
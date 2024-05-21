#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <stdio.h>
WiFiClient client;
HTTPClient http;


DHT dht(22, DHT22);

void setup() {
  Serial.begin(115200);

  // Scannerizziamo le reti disponibili
  Serial.println("Scansione reti WiFi disponibili...");
  int numReti = WiFi.scanNetworks();

  if (numReti == 0) {
    // Se nessuna rete trovata, stampiamo errore
    Serial.println("Nessuna rete trovata");
  } else {
    // Stampiamo le reti disponibili
    Serial.print(numReti);
    Serial.println(" reti trovate");
    for (int i = 0; i < numReti; ++i) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " (Aperta)" : " (Protetta)");
    }

    // Chiedo SSID rete fino a quando non e valido
    char ssid[33];
    bool ssidValido = false;
    while (!ssidValido) {
      Serial.print("Inserisci l'SSID della rete a cui connetterti: ");
      readLine(ssid, sizeof(ssid));
      for (int i = 0; i < numReti; ++i) {
        if (strcmp(ssid, WiFi.SSID(i).c_str()) == 0) {
          ssidValido = true;
          break;
        }
      }
      if (!ssidValido) {
        Serial.println("L'SSID inserito non e' presente nell'elenco delle reti trovate.");
      }
    }
    //richiedi password
    char password[65];
    Serial.print("Inserisci la password per ");
    Serial.print(ssid);
    Serial.print(": ");
    readLine(password, sizeof(password));
    // Connettiti alla rete WiFi
    WiFi.begin(ssid, password);
    Serial.print("Connessione a ");
    Serial.print(ssid);
    Serial.println("...");
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connesso!");
    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  /* Ricaviamo e stampiamo la temperature
   * con la funzione che abbiamo definito
   */
  float t = gettemperatura();
  Serial.println("temperatura: ");
  Serial.println(t);

  // facciamo una richiesta HTTP
  String buf;
  buf = F("http://10.0.3.94:5000/add?aula=MM1&valore=");
  buf += String (t);
  Serial.println(buf);
  String oj = httpGETRequest(buf); /* httpGETRequest e' una 
                                    * funzione definita da noi
                                    */
  delay(3600000);
}

void readLine(char* buffer, int bufferSize) {
  int i = 0;
  while (i < bufferSize - 1) {
    int c = Serial.read();
    if (c == -1) {
      continue;
    } else if (c == '\n') {
      buffer[i] = '\0';
      return;
    } else {
      buffer[i++] = (char)c;
    }
  }
  buffer[bufferSize - 1] = '\0';
}

float gettemperatura(){
  float temp;
  temp = dht.readTemperature();
  Serial.println(temp);  
  return temp;
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

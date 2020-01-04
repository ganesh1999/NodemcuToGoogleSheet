#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>


const char* ssid = "1 FLOOR"; 
const char* password = "12345678";
const char* host = "script.google.com";
const int httpsPort = 443;
WiFiClientSecure client;
String GAS_ID = "AKfycbw6mRQol9AAbErQY0wXaV-rvjtOIqKdnBGNGY3h";
void setup() 
{
 
  Serial.begin(115200); //Serial

  //connecting to internet
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 

}

void loop() 
{
  client.setInsecure();
  sendData();
  delay(2000);
}

// Function for Send data into Google Spreadsheet
void sendData()
{
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  int random1 = random(1,100);
  int random2 = random(100,200);
  int random3 = random(201,300);
  String url = "/macros/s/" + GAS_ID + "/exec?randomvalueone=" + String(random1) + "&randomvaluetwo=" + String(random2) + "&randomvaluethree=" + String(random3);
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
         "Host: " + host + "\r\n" +
         "User-Agent: BuildFailureDetectorESP8266\r\n" +
         "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
} 

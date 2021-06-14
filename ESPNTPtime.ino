#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#ifndef STASSID
#define STASSID "A21"
#define STAPSK  "1234567890"
#endif

const char * ssid = STASSID; // your network SSID (name)
const char * pass = STAPSK;  // your network password
WiFiUDP u;
NTPClient n(u, "1.asia.pool.ntp.org", 7 * 3600);
String h, m, s;
String Time;
unsigned long epochtime, Time1;
void Setupwifi(){
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN , 1);
  // We start by connecting to a WiFi network
  Setupwifi();
}

void loop() {
  n.update();
  epochtime = n.getEpochTime();
  h = n.getHours();
  m = n.getMinutes();
  s = n.getSeconds();
  Time = h + ":" + m + ":" + s + "w";
  Serial.println(Time);
  delay(1000);
  while (WiFi.status() != WL_CONNECTED) {
    epochtime += 1;
    h = ((epochtime % 86400L) / 3600);
    m = ((epochtime % 3600) / 60);
    s = (epochtime % 60);
    Time = h + ":" + m + ":" + s;
    Serial.println(Time);
    if ( h.toInt() == 11 & m.toInt() == 48) {
      digitalWrite(LED_BUILTIN , 0);
    }
    if ( h.toInt() == 11 & m.toInt() == 49) {
      digitalWrite(LED_BUILTIN , 1);
    }
    delay(1000);
  }
}

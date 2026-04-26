#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

char auth[] = "YOUR_BLYNK_AUTH";
char ssid[] = "YOUR_WIFI";
char pass[] = "YOUR_PASSWORD";

TinyGPSPlus gps;
SoftwareSerial gpsSerial(D6, D5);

#define METAL_PIN D7

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  pinMode(METAL_PIN, INPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (digitalRead(METAL_PIN) == HIGH) {
    if (gps.location.isValid()) {
      float lat = gps.location.lat();
      float lng = gps.location.lng();

      Serial.println("Landmine detected");

      Blynk.virtualWrite(V0, lat);
      Blynk.virtualWrite(V1, lng);

      delay(5000);
    } else {
      Serial.println("GPS not fixed");
    }
  }
}

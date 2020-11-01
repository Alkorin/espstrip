#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#ifndef WIFI_SSID
#error "WIFI_SSID is not set"
#endif

#ifndef WIFI_PSK
#error "WIFI_SSID is not set"
#endif

// Strip object
NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart1800KbpsMethod> strip(PIXEL_COUNT);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  // Clear strip at startup
  strip.Begin();
  strip.ClearTo(RgbColor(0, 0, 0));
  strip.Show();

  // Start WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // OTA callbacks
  ArduinoOTA.onStart([]() {
    strip.ClearTo(RgbColor(0, 0, 0));
    strip.Show();
  });
  ArduinoOTA.onEnd([]() {
    strip.ClearTo(RgbColor(0, 128, 0));
    strip.Show();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    strip.ClearTo(RgbColor(128,0,0), 0, (progress * PIXEL_COUNT) / total);
    strip.Show();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();

  Serial.println("Started");
}

void loop() {
  ArduinoOTA.handle();
  strip.ClearTo(RgbColor(128, 128, 0));
  strip.Show();
}

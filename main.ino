#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include "genericStrip.h"
#include "animations.h"
#include "udp_server.h"

#ifndef WIFI_SSID
#error "WIFI_SSID is not set"
#endif

#ifndef WIFI_PSK
#error "WIFI_SSID is not set"
#endif

// Strip object
Strip<NeoGrbFeature, NeoEsp8266Uart1Sk6812Method> strip(PIXEL_COUNT);

// UDP server
UdpLedServer server(strip);

GenericAnimation *anim;

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting...");

  // Clear strip at startup
  strip.Begin();
  strip.ClearTo(RgbColor(0, 0, 0));
  strip.Show();

  // Start WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Setup OTA updates
  ArduinoOTA.onStart([]() {
    strip.ClearTo(RgbColor(0, 0, 0));
    strip.Show();
  });
  ArduinoOTA.onEnd([]() {
    strip.ClearTo(RgbColor(0, 128, 0));
    strip.Show();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    strip.ClearTo(RgbColor(128, 0, 0), 0, (progress * PIXEL_COUNT) / total);
    strip.Show();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();

  // Start UDP follower server
  server.begin(8080);

  Serial.println("Started");
  //anim = new RandomSwitchColor(strip, RgbColor(255, 0, 255), RgbColor(0, 255, 0), RANDOM_LEDS);
  anim = new Sparks(strip, RgbColor(255, 255, 255), RANDOM_LEDS);
}

void loop()
{
  ArduinoOTA.handle();

  if (!server.handle())
  {
    anim->Animate();
    strip.Show();
  }
}

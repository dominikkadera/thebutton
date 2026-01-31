#include "config.h"
#include "secret.h"
#include <FastLED.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Declare here, so it can be used where needed
void setStripColor(CRGB *ledStrip, CRGB color);
time_t getClock();

class TheButton {
private:
  boolean lastButtonState = false;
  boolean debouncedButtonState = false;
  unsigned long debounceTime = 0;
  unsigned long limit = 0;
  unsigned long blinkLimit = 0;
  unsigned long buttonDownAt = 0;
  unsigned long buttonReleasedAt = 0;
  boolean buttonIsDown = false;
  boolean blinkState = false;
  boolean sendeeCandidate = false;
  boolean abortRequest = false;
  String sequence = "";
  char currentPressChar = 0;
  void sendRequest(String u) {
    setStripColor(ledStrip, COLOR_SENDING);
    if ((WiFi.status() == WL_CONNECTED)) {
      WiFiClientSecure *client = new WiFiClientSecure;

      if (client) {
        client->setInsecure();

        HTTPClient http;
        String fullUrl = u + (u.indexOf('?') == -1 ? "?" : "&") + "ts=" + getClock();

        if (http.begin(*client, fullUrl)) {
          int code = http.GET();

          if (code < 100 || code >= 400) {
            setStripColor(ledStrip, COLOR_CONNECTION_FAILED);
            delay(FAIL_NOTIFICATION_LENGTH);
          }
          http.end();
        }

        delete client;
      }
    }
    setStripColor(ledStrip, COLOR_NONE);
  }
public:
  void readInput();
  void onTick();
  void onReleased();
  void onPressed();
  CRGB ledStrip[NUM_LEDS];
};

TheButton *button = new TheButton();

void setup() {
  // Serial.begin(115200);
  delay(STARTUP_SANITY_DELAY);
  FastLED.addLeds<WS2812, LED_PIN, COLOR_ORDER>(button->ledStrip, NUM_LEDS);
  FastLED.setBrightness(LED_BRIGHTNESS);
  setStripColor(button->ledStrip, COLOR_CONNECTING);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.setHostname("thebutton");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  for (int i = 0; i < WIFI_CONNECTION_CHECKS; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    } else {
      delay(WIFI_CHECK_DELAY);
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    setStripColor(button->ledStrip, COLOR_INITIALIZING);
    setClock();
  } else {
    setStripColor(button->ledStrip, COLOR_CONNECTION_FAILED);
    delay(FAIL_NOTIFICATION_LENGTH);
  }
  setStripColor(button->ledStrip, COLOR_NONE);
}

void loop() {
  button->readInput();
  button->onTick();
}

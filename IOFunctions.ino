#include "config.h"

boolean readButtonState() {
  return (digitalRead(BUTTON_PIN) == LOW);
}

// Optimization for cases when setStripColor gets called with the same color again
CRGB lastColor = CRGB::Black;

void setStripColor(CRGB * ledStrip, CRGB color) {
  if(lastColor == color) {
    return;
  }
  for(int i = 0; i < NUM_LEDS; ++i) {
    ledStrip[i] = color;
  }
  FastLED.show();
  lastColor = color;
}

void setClock() {
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  time_t nowSecs = time(nullptr);
  int retries = 0;
  while (nowSecs < 8 * 3600 * 2 && retries < 20) {
    delay(500);
    yield();
    nowSecs = time(nullptr);
    retries++;
  }
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
}

time_t getClock() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  return tv.tv_sec;
}

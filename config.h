#define LED_PIN                   27
#define LED_BRIGHTNESS            128
#define BUTTON_PIN                5
#define BUTTON_DEBOUNCE_MS        50
#define NUM_LEDS                  16
#define COLOR_ORDER               GRB
#define STARTUP_SANITY_DELAY      2000
#define BLINK_TIME                400
#define COLOR_NONE                CRGB::Black
#define COLOR_CONNECTING          CRGB::Lime
#define COLOR_SENDING             CRGB::Lime
#define COLOR_CONNECTION_FAILED   CRGB::Red
#define WIFI_CONNECTION_CHECKS    40   // max 40 * 250 = 10000 ms = 10 seconds timeout
#define WIFI_CHECK_DELAY          250  // .........^^^
#define FAIL_NOTIFICATION_LENGTH  1000 // 1 second

// ^^^^^^ GENERAL VALUES ----- | ----- BUTTON SPECIFIC vvvvvv //

#define SHORT_PRESS_MS     500
#define MEDIUM_PRESS_MS    1000
#define LONG_PRESS_MS      2000
#define ABORT_PRESS_MS     5000
#define SPACE_MS           1000
#define SHORT_PRESS_COLOR  CRGB::DarkMagenta
#define MEDIUM_PRESS_COLOR CRGB::Blue
#define LONG_PRESS_COLOR   CRGB::DeepPink

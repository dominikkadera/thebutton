#include "config.h"

/**
     This function gets called every tick of the main loop.
*/
void TheButton::onTick() {
  // If the button is down, then light it according to the length of the press
  if(buttonIsDown) {
    unsigned long downFor = millis() - buttonDownAt;
    if(downFor <= SHORT_PRESS_MS) {
      setStripColor(ledStrip, SHORT_PRESS_COLOR);
      currentPressChar = 'S';
    } else if(downFor <= MEDIUM_PRESS_MS) {
      setStripColor(ledStrip, MEDIUM_PRESS_COLOR);
      currentPressChar = 'M';
    } else if (downFor <= ABORT_PRESS_MS){
      setStripColor(ledStrip, LONG_PRESS_COLOR);
      currentPressChar = 'L';
    } else {
      setStripColor(ledStrip, COLOR_NONE);
      currentPressChar = '\0';
      abortRequest = true;
    }
  } else {
    if(abortRequest) {
      abortRequest = false;
      sendeeCandidate = false;
      sequence = "";
    } else if(sendeeCandidate && millis() - buttonReleasedAt > SPACE_MS) {
      sendeeCandidate = false;
      String u = String(WEBHOOK_URL);
      sendRequest(u + (u.indexOf('?') == -1 ? "?" : "&") + "sequence=" + sequence);
      sequence = "";
    }
  }
}

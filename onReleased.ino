#include "config.h"

/**
   This function gets called when the button is released.
*/
void TheButton::onReleased() {
  buttonReleasedAt = millis();
  buttonIsDown = false;
  sendeeCandidate = true;
  sequence += currentPressChar;
  setStripColor(ledStrip, COLOR_NONE);
}

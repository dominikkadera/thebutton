#include "config.h"

/**
   This function gets called when the button is pressed.
*/
void TheButton::onPressed() {
  buttonIsDown = true;
  sendeeCandidate = false;
  buttonDownAt = millis();
}

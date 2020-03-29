#include "config.h"

/**
   This function reads the input button and debounces the reading.
   It fires the handler function only once, when the button is pressed or released.
*/
void TheButton::readInput() {
  // Read the button
  boolean currentButtonState = readButtonState();

  // If the state has changed, then reset the debounce time
  if (currentButtonState != lastButtonState) {
    debounceTime = millis();
  }

  // If input is stable, debounced and the state has truly changed, then ...
  if (((millis() - debounceTime) > BUTTON_DEBOUNCE_MS) && (currentButtonState != debouncedButtonState)) {

    // Set the current state as the debounded state
    debouncedButtonState = currentButtonState;

    // Fire the correct handler
    if (debouncedButtonState == true) {
      onPressed();
    } else {
      onReleased();
    }
  }

  // The currentButtonState is the lastButtonState now
  lastButtonState = currentButtonState;
}

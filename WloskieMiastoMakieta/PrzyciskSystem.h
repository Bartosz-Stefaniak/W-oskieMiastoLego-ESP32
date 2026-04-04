#ifndef PRZYCISKSYSTEM_H
#define PRZYCISKSYSTEM_H
// przyciskSystem.h
#include "Konfiguracja.h"

bool lastSystemState = HIGH;
unsigned long lastSystemDebounce = 0;

bool isSystemClicked() {
    bool currentState = digitalRead(BUTTON_SYSTEM_PIN);
    bool clicked = false;

    if (currentState != lastSystemState) {
        if ((millis() - lastSystemDebounce) > DEBOUNCE_DELAY) {
            if (currentState == LOW) {
                clicked = true;
            }
            lastSystemDebounce = millis();
        }
    }
    lastSystemState = currentState;
    return clicked;
}
#endif
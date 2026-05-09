#ifndef PRZYCISKTRAMWAJ_H
#define PRZYCISKTRAMWAJ_H
// PrzyciskTramwaj.h
#include "Konfiguracja.h"

bool lastTramState = HIGH;
unsigned long lastTramDebounce = 0;

bool isTramClicked() {
    bool currentState = digitalRead(BUTTON_TRAM_PIN);
    bool clicked = false;

    if (currentState != lastTramState) {
        if ((millis() - lastTramDebounce) > DEBOUNCE_DELAY) {
            if (currentState == LOW) {
                clicked = true;
            }
            lastTramDebounce = millis();
        }
    }
    lastTramState = currentState;
    return clicked;
}
#endif
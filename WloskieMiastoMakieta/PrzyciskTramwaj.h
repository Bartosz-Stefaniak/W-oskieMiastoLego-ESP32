#ifndef PRZYCISKTRAMWAJ_H
#define PRZYCISKTRAMWAJ_H
// PrzyciskTramwaj.h
#include "Konfiguracja.h"

bool lastTramState = HIGH;
bool stableTramState = HIGH;
unsigned long lastTramDebounce = 0;

bool isTramClicked() {
    bool currentState = digitalRead(BUTTON_TRAM_PIN);
    bool clicked = false;
    unsigned long now = millis();

    if (currentState != lastTramState)
    {
        lastTramDebounce=now;
        lastTramState = currentState;
    } 
    if ((now - lastTramDebounce) > DEBOUNCE_DELAY) {
            if (currentState != stableTramState) {
               stableTramState = currentState;
               if (stableTramState == LOW)
               {
                clicked=true;
               }
            }
        }
    return clicked;
}
#endif
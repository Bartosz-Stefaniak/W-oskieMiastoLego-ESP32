#ifndef FOTOREZYSTOR_H
#define FOTOREZYSTOR_H
// fotorezystor.h
#include "Konfiguracja.h"
const int LDR_THRESHOLD_DARK  = 2700; // poniżej → ciemno
const int LDR_THRESHOLD_LIGHT = 3000; // powyżej → jasno (wyższy próg uwzględnia świecące diody)

unsigned long lastPhotoresistorCheckTime = 0;
bool currentDarkState = false;

int realLDR() {
  return analogRead(LDR_PIN);
}

// Zwraca true jeśli ciemność potwierdzona przez LDR_CHECK_DELAY ms
bool isDark() {
  int val = realLDR();

  if (currentDarkState) {
    // Aktualnie ciemno — gaś tylko jeśli przekroczono WYŻSZY próg (jasno)
    if (val > LDR_THRESHOLD_LIGHT) {
      lastPhotoresistorCheckTime = millis();
      currentDarkState = false;
    }
  } else {
    // Aktualnie jasno — zapal tylko jeśli przekroczono NIŻSZY próg (ciemno)
    if (val < LDR_THRESHOLD_DARK) {
      if ((millis() - lastPhotoresistorCheckTime) > LDR_CHECK_DELAY) {
        currentDarkState = true;
        lastPhotoresistorCheckTime = millis();
      }
    } else {
      lastPhotoresistorCheckTime = millis(); // resetuj timer gdy nie jest ciemno
    }
  }

  return currentDarkState;
}

#endif
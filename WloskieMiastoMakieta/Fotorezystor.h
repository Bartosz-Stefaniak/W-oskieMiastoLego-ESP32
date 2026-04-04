#ifndef FOTOREZYSTOR_H
#define FOTOREZYSTOR_H
// fotorezystor.h
#include "Konfiguracja.h"
unsigned long lastPhotoresistorCheckTime = 0;

bool checkSensor() {
  return analogRead(LDR_PIN) < 3100;
}

bool isDark() {
  if (!checkSensor()) {
    lastPhotoresistorCheckTime = millis();
    return false; // Jest jasno
  } else {
    // Jeśli jest ciemno, sprawdź czy minął czas stabilizacji (2 sekundy)
    if ((millis() - lastPhotoresistorCheckTime) > LDR_CHECK_DELAY) {
      return true; // Potwierdzono: jest ciemno
    }
  }
  return false; // Jeszcze czekamy na potwierdzenie (CHECK_DELAY)
}
#endif
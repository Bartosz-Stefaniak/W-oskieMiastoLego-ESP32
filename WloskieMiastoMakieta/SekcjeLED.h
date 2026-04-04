#ifndef SEKCJELED_H
#define SEKCJELED_H
#include "Konfiguracja.h"
#include "Fotorezystor.h"

const unsigned long SECTION_INTERVAL = 300000; // 5 minut
unsigned long lastSectionTime = 0;
bool section1Active = false;
void resetSekcji() {
  section1Active = false;
  firstRunDark = true;
  firstRunLight = true;
  lastSectionTime = 0;
  digitalWrite(LED_SECTION_1, LOW);
}

void initializeLEDs() {
  bool dark = isDark();
  unsigned long now = millis();

  if (dark && !section1Active) {
    if (firstRun || (now - lastSectionTime) > SECTION_INTERVAL) {
      firstRun = false;
      section1Active = true;
      digitalWrite(LED_SECTION_1, HIGH);
      lastSectionTime = now;
      Serial.println("Sekcja 1 WLACZONA");
    }
  }

  if (!dark && section1Active) {
    if ((now - lastSectionTime) > SECTION_INTERVAL) {
      section1Active = false;
      digitalWrite(LED_SECTION_1, LOW);
      lastSectionTime = now;
      Serial.println("Sekcja 1 WYLACZONA");
    }
  }
}

#endif
#ifndef SEKCJELED_H
#define SEKCJELED_H
#include "Konfiguracja.h"
#include "Fotorezystor.h"

const unsigned long SECTION_INTERVAL = 30000; // 5 minut
unsigned long lastSectionTime = 0;
bool section1Active = false;
bool firstRunDark = true;
bool firstRunLight = true;

void resetSekcji() {
  section1Active = false;
  firstRunDark = true;
  firstRunLight = true;
  lastSectionTime = 0;
  digitalWrite(LED_SECTION_STREETLIGHTS, LOW);
}

void initializeLEDs() {
  bool dark = isDark();
  unsigned long now = millis();

  if (dark && !section1Active) {
    if (firstRunDark || (now - lastSectionTime) > SECTION_INTERVAL) {
      firstRunDark = false;
      firstRunLight = true; // reset gaszenia
      section1Active = true;
      digitalWrite(LED_SECTION_STREETLIGHTS, HIGH);
      lastSectionTime = now;
      Serial.println("Sekcja 1 WLACZONA");
    }
  }

  if (!dark && section1Active) {
    if (firstRunLight || (now - lastSectionTime) > SECTION_INTERVAL) {
      firstRunLight = false;
      firstRunDark = true; // reset zapalania
      section1Active = false;
      digitalWrite(LED_SECTION_STREETLIGHTS, LOW);
      lastSectionTime = now;
      Serial.println("Sekcja 1 WYLACZONA");
    }
  }
}

#endif
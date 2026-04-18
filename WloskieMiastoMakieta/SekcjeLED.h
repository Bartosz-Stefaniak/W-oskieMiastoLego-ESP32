#ifndef SEKCJELED_H
#define SEKCJELED_H
#include "Konfiguracja.h"
#include "Fotorezystor.h"
#include "SekcjaPWM.h"
// --- INTERWAŁY ---
const unsigned long TURN_ON_INTERVAL  = 2000;  // 1 minuta między włączaniem
const unsigned long TURN_OFF_INTERVAL = 5000;  // 30 sekund między wyłączaniem

// --- STAN ---
unsigned long lastSectionTime = 0;
int activeSections = 0; // ile sekcji aktualnie włączonych (0-6)
bool firstRunDark  = true;
bool firstRunLight = true;

// --- KOLEJNOŚĆ WŁĄCZANIA I WYŁĄCZANIA ---
// Włączanie: 1, STREETLIGHTS, AMBIENT, 2, TARASY(PWM), 3
// Wyłączanie: 3, 2, TARASY(PWM), 1, AMBIENT, STREETLIGHTS

const int SECTION_COUNT = 6;

int onOrder[SECTION_COUNT] = {
  LED_SECTION_1,
  LED_SECTION_STREETLIGHTS,
  LED_SECTION_AMBIENTBUILDINGS,
  LED_SECTION_2,
  LED_SECTION_TERRACESPWM,
  LED_SECTION_3
};

int offOrder[SECTION_COUNT] = {
  LED_SECTION_3,
  LED_SECTION_2,
  LED_SECTION_TERRACESPWM,
  LED_SECTION_1,
  LED_SECTION_AMBIENTBUILDINGS,
  LED_SECTION_STREETLIGHTS
};

void resetSekcji() {
  for (int i = 0; i < SECTION_COUNT; i++) {
    if (onOrder[i] != LED_SECTION_TERRACESPWM) {
      digitalWrite(onOrder[i], LOW);
    }
    // PWM — logika w SekcjaPWM.h, tutaj tylko sygnał do wyłączenia
  }
  disablePWM();
  activeSections = 0;
  firstRunDark   = true;
  firstRunLight  = true;
  lastSectionTime = 0;
}

void initializeLEDs() {
  bool dark = isDark();
  unsigned long now = millis();

  // --- WŁĄCZANIE sekwencyjne ---
  if (dark && activeSections < SECTION_COUNT) {
    if (firstRunDark || (now - lastSectionTime) > TURN_ON_INTERVAL) {
      firstRunDark = false;
      firstRunLight = true;
      lastSectionTime = now;

      int pin = onOrder[activeSections];
      if (pin != LED_SECTION_TERRACESPWM) {
        digitalWrite(pin, HIGH);
      } else
      {
        enablePWM();
      }
      // LED_SECTION_TERRACESPWM — SekcjaPWM.h samo to obsłuży gdy activeSections == 4

      Serial.print("Wlaczono sekcje: ");
      Serial.println(activeSections + 1);
      activeSections++;
    }
  }

  // --- WYŁĄCZANIE sekwencyjne ---
  if (!dark && activeSections > 0) {
    if (firstRunLight || (now - lastSectionTime) > TURN_OFF_INTERVAL) {
      firstRunLight = false;
      firstRunDark = true;
      lastSectionTime = now;

      activeSections--;
      int pin = offOrder[SECTION_COUNT - 1 - activeSections];
      if (pin != LED_SECTION_TERRACESPWM) {
        digitalWrite(pin, LOW);
      }else{
        disablePWM();
      }
      // LED_SECTION_TERRACESPWM — SekcjaPWM.h samo to obsłuży

      Serial.print("Wylaczono sekcje: ");
      Serial.println(activeSections + 1);
    }
  }
}

#endif
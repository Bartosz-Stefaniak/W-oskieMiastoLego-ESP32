#include "Konfiguracja.h"
#include "PrzyciskSystem.h"
#include "Fotorezystor.h"
#include "SekcjaPWM.h"      // ← nowe
#include "SekcjeLED.h"

bool systemActive = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  pinMode(LED_SECTION_STREETLIGHTS, OUTPUT);
  digitalWrite(LED_SECTION_STREETLIGHTS, LOW);
  pinMode(LED_SECTION_1, OUTPUT);
  digitalWrite(LED_SECTION_1, LOW);
  pinMode(LED_SECTION_2, OUTPUT);
  digitalWrite(LED_SECTION_2, LOW);
  pinMode(LED_SECTION_3, OUTPUT);
  digitalWrite(LED_SECTION_3, LOW);
  pinMode(LED_SECTION_AMBIENTBUILDINGS, OUTPUT);
  digitalWrite(LED_SECTION_AMBIENTBUILDINGS, LOW);
  pinMode(BUTTON_SYSTEM_PIN, INPUT);
  initPWM();                // ← nowe
}

void loop() {
  if (isSystemClicked()) {
    systemActive = !systemActive;
    digitalWrite(BUILTIN_LED, systemActive ? HIGH : LOW);
    resetSekcji();
  }

  if (systemActive) {
    initializeLEDs();
    updatePWM();            // ← nowe
  }
}
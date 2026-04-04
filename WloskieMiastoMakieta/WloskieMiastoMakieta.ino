#include "Konfiguracja.h"
#include "przyciskSystem.h"
#include "fotorezystor.h"
#include "SekcjeLED.h"
bool systemActive = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  pinMode(LED_SECTION_1, OUTPUT);
  digitalWrite(LED_SECTION_1, LOW);
  pinMode(BUTTON_SYSTEM_PIN, INPUT);
}

void loop() {
  // --- OBSŁUGA SYSTEMU ---
  if (isSystemClicked()) {
    systemActive = !systemActive;
    digitalWrite(BUILTIN_LED, systemActive ? HIGH : LOW);
    resetSekcji(); // zawsze resetuj przy każdej zmianie stanu
}

  // --- URUCHOMIENIE PROGRAMU PO SPRAWDZENIU WARUNKU ---
  if (systemActive) {
    Serial.print("LDR: ");
    Serial.print(realLDR());
    Serial.print(" | isDark: ");
    Serial.print(isDark());
    Serial.print(" | section1Active: ");
    Serial.println(section1Active);
    Serial.print(" | firstRun: ");
Serial.print(firstRunDark);
Serial.print(" | timeDiff: ");
Serial.println(millis() - lastSectionTime);
    initializeLEDs();
  }
}
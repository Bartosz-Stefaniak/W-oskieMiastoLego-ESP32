#include "Konfiguracja.h"
#include "przyciskSystem.h"
#include "fotorezystor.h"

bool systemActive = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(LED_SECTION_1, OUTPUT);
  pinMode(BUTTON_SYSTEM_PIN, INPUT);
}

void loop() {
  // --- OBSŁUGA SYSTEMU ---
  if (isSystemClicked()) {
    systemActive = !systemActive;
    digitalWrite(BUILTIN_LED, systemActive ? HIGH : LOW);
  }

  // BLOKADA: Jeśli system wyłączony, procesor nie idzie dalej
  if (!systemActive) {
    digitalWrite(LED_SECTION_1, LOW);
    lastSystemCheckTime = millis(); 
    return; 
  }

  // --- OBSŁUGA TRAMWAJU (Tylko gdy systemActive == true) ---
 
  // Logika fotorezystora
  obslugaFotorezystora(LED_PIN);
}
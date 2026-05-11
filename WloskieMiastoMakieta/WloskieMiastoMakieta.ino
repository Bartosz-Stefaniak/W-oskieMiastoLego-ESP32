#include "Konfiguracja.h"
#include "PrzyciskSystem.h"
#include "Fotorezystor.h"
#include "SekcjaPWM.h"      // ← nowe
#include "SekcjeLED.h"
#include "PrzyciskTramwaj.h"
#include "Tramwaj.h"

bool systemActive = false;
bool tramRunning = false;
bool lastTramRunning = false;
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
  pinMode(BUTTON_TRAM_PIN, INPUT);
  initTramwaj();
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
    updatePWM();           // ← nowe
  if (isTramClicked()) {
      tramRunning = !tramRunning;
  }
  }else 
  {
    tramRunning=false;
  }
  updateTramwaj(tramRunning && systemActive);

  if (tramRunning != lastTramRunning) {
    Serial.print("Tram running state changed to: "); 
    Serial.println(tramRunning ? "START / WORKING" : "WAITING FOR STOP");
    lastTramRunning = tramRunning; // Zapamiętaj obecny stan
  }
}
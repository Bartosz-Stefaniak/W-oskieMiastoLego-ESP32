#include "Konfiguracja.h"
#include "PrzyciskSystem.h"
#include "Fotorezystor.h"
#include "SekcjaPWM.h"      // ← nowe
#include "SekcjeLED.h"

bool systemActive = false;
bool tramRunning = false;
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
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  pinMode(MOTOR_ENB, OUTPUT);
  initPWM();                // ← nowe
}

void loop() {
  if (isSystemClicked()) {
    systemActive = !systemActive;
    digitalWrite(BUILTIN_LED, systemActive ? HIGH : LOW);
    resetSekcji();
    if (!systemActive) tramRunning = false;
  }

  if (systemActive) {
    initializeLEDs();
    updatePWM();            // ← nowe
  if (isTramClicked()) {
      tramRunning = !tramRunning;
  }
      updateTramwaj(tramRunning);
  } else {
    // Całkowite zatrzymanie gdy system wyłączony
    stopPhysicalMotor();
    tramRunning = false;
  }
}
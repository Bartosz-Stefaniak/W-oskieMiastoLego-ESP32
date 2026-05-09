#ifndef TRAMWAJ_H
#define TRAMWAJ_H
// PrzyciskTramwaj.h
#include "Konfiguracja.h"
enum TramState { STOPPED, ACCEL, CONSTANT, DECEL, WAIT };
TramState currentTramState = STOPPED;

unsigned long tramTimer = 0;
int currentSpeed = 0;
bool directionForward = true;
int cursesDone = 0;
bool isStop = false;
void initTramwaj() {
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  // Inicjalizacja PWM dla ESP32 (kanał 1, 5000Hz, 8 bitów rozdzielczości)
  ledcAttach(MOTOR_ENB, 5000, 8); 
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
  ledcWrite(MOTOR_ENB, 0);
}

void stopPhysicalMotor() {
  ledcWrite(MOTOR_ENB, 0);
  digitalWrite(MOTOR_IN3, LOW);
  digitalWrite(MOTOR_IN4, LOW);
}

void updateTramwaj(bool active) {
  unsigned long now = millis();

  // Jeśli system zostanie wyłączony w trakcie jazdy
  if (!active && currentTramState == STOPPED) {
    isStop=true;
  }
  if (!active && currentTramState != STOPPED) {
    // Tutaj w przyszłości dodamy logikę "powrotu do bazy"
    // Na razie dla bezpieczeństwa hamujemy gwałtownie
    stopPhysicalMotor();
    currentTramState = STOPPED;
    return;
  }

  switch (currentTramState) {
    case STOPPED:
      if (active && !isStop) {
        currentTramState = ACCEL;
        tramTimer = now;
        // Ustawienie kierunku
        if (directionForward) {
          digitalWrite(MOTOR_IN3, HIGH); digitalWrite(MOTOR_IN4, LOW);
        } else {
          digitalWrite(MOTOR_IN3, LOW); digitalWrite(MOTOR_IN4, HIGH);
        }
      }
      }
      break;

    case ACCEL: // 2 sekundy przyspieszania
      if (now - tramTimer <= 2000) {
        currentSpeed = map(now - tramTimer, 0, 2000, 0, 180);
        ledcWrite(MOTOR_ENB, currentSpeed);
      } else {
        currentTramState = CONSTANT;
        tramTimer = now;
      }
      break;

    case CONSTANT: // 1 sekunda jazdy
      if (now - tramTimer <= 1000) {
        ledcWrite(MOTOR_ENB, 180);
      } else {
        currentTramState = DECEL;
        tramTimer = now;
      }
      break;

    case DECEL: // 2 sekundy hamowania
      if (now - tramTimer <= 2000) {
        currentSpeed = map(now - tramTimer, 0, 2000, 180, 0);
        ledcWrite(MOTOR_ENB, currentSpeed);
      } else {
        stopPhysicalMotor();
        directionForward = !directionForward; // Zmiana kierunku na następny raz
        coursesDone++;
        currentTramState = WAIT; 
        tramTimer = now;
      }
      break;

    case WAIT: // Chwila postoju na przystanku (np. 1 sekunda) przed możliwością kolejnego startu
      if (now - tramTimer > 1000) {
        currentTramState = STOPPED;
        if (isStop && (coursesDone % 2 == 0)) {
          currentTramState = STOPPED;
          isStop = false; // Reset flagi po całkowitym zatrzymaniu
          coursesDone = 0;     // Reset licznika
        } 
        else if (!active && (coursesDone % 2 == 0)) {
           // Dodatkowe zabezpieczenie gdyby flaga active spadła nagle
           currentTramState = STOPPED;
        }
        else {
          // Kontynuuj jazdę (albo powrót do bazy, albo kolejny cykl)
          currentTramState = STOPPED; // Wróć do STOPPED, a tam case STOPPED od razu go odpali ponownie
        }
      }
      break;
  }
}

#endif
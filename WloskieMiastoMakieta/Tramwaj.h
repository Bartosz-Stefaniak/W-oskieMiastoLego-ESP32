#ifndef TRAMWAJ_H
#define TRAMWAJ_H
// PrzyciskTramwaj.h
#include "Konfiguracja.h"
enum TramState { STOPPED, ACCEL, CONSTANT, DECEL, WAIT };
TramState currentTramState = STOPPED;

unsigned long tramTimer = 0;
int currentSpeed = 0;
bool directionForward = true;
int coursesDone = 0;
bool isStop = false;
int driveTime;
void initTramwaj() {
  pinMode(MOTOR_IN3, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  // Inicjalizacja PWM dla ESP32 (kanał 1, 500Hz, 8 bitów rozdzielczości)
  ledcAttach(MOTOR_ENB, 500, 8); 
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
  if(!active) {
    isStop=true;
  } else {
    isStop = false;
  }

  // Jeśli system zostanie wyłączony w trakcie jazdy


  switch (currentTramState) {
    case STOPPED:
      if ((active && !isStop)|| (isStop && coursesDone%2 != 0)) {
        Serial.println("TRAMWAJ: START");
        currentTramState = ACCEL;
        tramTimer = now;
        // Ustawienie kierunku
        if (directionForward) {
          digitalWrite(MOTOR_IN3, LOW); digitalWrite(MOTOR_IN4, HIGH);
        } else {
          digitalWrite(MOTOR_IN3, HIGH); digitalWrite(MOTOR_IN4, LOW);
        }
      }
      break;

    case ACCEL: // 3 sekundy przyspieszania
      if (now - tramTimer <= 3000) {
        if(directionForward){
        currentSpeed = map(now - tramTimer, 0, 3000, 25, 70);
        ledcWrite(MOTOR_ENB, currentSpeed);
      }else{
        currentSpeed = map(now - tramTimer, 0, 3000, 35, 80);
        ledcWrite(MOTOR_ENB, currentSpeed);
      }
      } else {
        Serial.println("TRAMWAJ: PREDKOSC STALA");
        currentTramState = CONSTANT;
        tramTimer = now;
      }
      break;

    case CONSTANT: // 4 sekundy jazdy
    if(directionForward)
    {
      driveTime=8750;
    }
    else{
      driveTime=8965;
    }
      if (now - tramTimer <= driveTime) {
      if(directionForward){
        ledcWrite(MOTOR_ENB, 70);
      }else{
        ledcWrite(MOTOR_ENB, 80);
      }
    
      } else {
        Serial.println("TRAMWAJ: HAMOWANIE");
        currentTramState = DECEL;
        tramTimer = now;
      }
      break;

    case DECEL: // 4 sekundy hamowania
      if (now - tramTimer <= 9000) {
        currentSpeed = map(now - tramTimer, 0, 4000, 70, 30);
        ledcWrite(MOTOR_ENB, currentSpeed);
      } else {
        stopPhysicalMotor();
        directionForward = !directionForward; // Zmiana kierunku na następny raz
        coursesDone++;
        Serial.print("TRAMWAJ: PRZYSTANEK. Kursow: ");
        Serial.println(coursesDone);
        currentTramState = WAIT; 
        tramTimer = now;
      }
      break;

    case WAIT: // Chwila postoju na przystanku (np. 1 sekunda) przed możliwością kolejnego startu
      if (now - tramTimer > 6000) {
        if (isStop && (coursesDone % 2 == 0)) {
          currentTramState = STOPPED;
          coursesDone = 0;     // Reset licznika
        } 
        else if (isStop && (coursesDone % 2 != 0)) {
           // Dodatkowe zabezpieczenie gdyby flaga active spadła nagle
           currentTramState = STOPPED;
        }
        else if(!isStop) {
          // Kontynuuj jazdę (albo powrót do bazy, albo kolejny cykl)
          currentTramState = STOPPED; // Wróć do STOPPED, a tam case STOPPED od razu go odpali ponownie
        }
      }
      break;
  }
}

#endif
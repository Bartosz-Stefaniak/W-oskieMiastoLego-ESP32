#ifndef SEKCJAPWM_H
#define SEKCJAPWM_H
#include "Konfiguracja.h"

unsigned long lastFlicker = 0;
unsigned long nextFlicker = 0;
unsigned long lastStep    = 0;
int currentBrightness     = 0;
int targetBrightness      = 0;
bool pwmActive            = false;

void initPWM() {
  ledcAttach(LED_SECTION_TERRACESPWM, 5000, 8);
}

void enablePWM() {
  pwmActive = true;
  currentBrightness = 0;
  targetBrightness  = 220;
}

void disablePWM() {
  pwmActive = false;
  currentBrightness = 0;
  targetBrightness  = 0;
  ledcWrite(LED_SECTION_TERRACESPWM, 0);
}

void updatePWM() {
  if (!pwmActive) return;

  unsigned long now = millis();

  if (now - lastFlicker >= nextFlicker) {
    lastFlicker = now;
    int flickerType = random(100);

    if (flickerType < 3) {
      targetBrightness = random(5, 25);
      nextFlicker      = random(80, 150);
    } else if (flickerType < 10) {
      targetBrightness = random(40, 80);
      nextFlicker      = random(60, 120);
    } else if (flickerType < 25) {
      targetBrightness = random(80, 130);
      nextFlicker      = random(100, 200);
    } else if (flickerType < 60) {
      targetBrightness = random(180, 255);
      nextFlicker      = random(80, 180);
    } else {
      targetBrightness = random(220, 245);
      nextFlicker      = random(200, 600);
    }
  }

  if (now - lastStep >= 5) {
    lastStep = now;
    if (currentBrightness < targetBrightness)
      currentBrightness = min(currentBrightness + 2, targetBrightness);
    else if (currentBrightness > targetBrightness)
      currentBrightness = max(currentBrightness - 2, targetBrightness);
    ledcWrite(LED_SECTION_TERRACESPWM, currentBrightness);
  }
}

#endif
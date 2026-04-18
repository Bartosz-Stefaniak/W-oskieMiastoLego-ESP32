// config.h
#ifndef KONFIGURACJA_H
#define KONFIGURACJA_H

// --- PINY DLA LED (MOSFET) ---
const int LED_SECTION_STREETLIGHTS = 13;
// ... dodaj kolejne do 10 sekcji

// --- WBUDOWANA DIODA ---
const int BUILTIN_LED =2;

// --- PINY DLA AUDIO (DFPlayer Mini) ---
const int DF_TX = 17; 
const int DF_RX = 16;

// --- PINY DLA SILNIKA (L298N) ---
const int MOTOR_IN1 = 25;
const int MOTOR_IN2 = 26;
const int MOTOR_ENA = 27;

// --- SENSORY I INTERFEJS ---
const int LDR_PIN = 34;    // Fotorezystor
const int BUTTON_SYSTEM_PIN = 36; // Przycisk (VP) z zewnętrznym pull-upem

// --- PARAMETRY ---
const unsigned long DEBOUNCE_DELAY = 50;
const unsigned long LDR_CHECK_DELAY = 2000;

#endif
// config.h
#ifndef KONFIGURACJA_H
#define KONFIGURACJA_H

// --- PINY DLA LED (MOSFET) ---
const int LED_SECTION_STREETLIGHTS = 13;
const int LED_SECTION_TERRACESPWM = 18;
const int LED_SECTION_AMBIENTBUILDINGS = 12;
const int LED_SECTION_1 = 32;
const int LED_SECTION_2 = 33;
const int LED_SECTION_3 = 4;
// ... dodaj kolejne do 10 sekcji

// --- WBUDOWANA DIODA ---
const int BUILTIN_LED =2;

// --- PINY DLA AUDIO (DFPlayer Mini) ---
const int DF_TX = 17; 
const int DF_RX = 16;

// --- PINY DLA SILNIKA (L298N) ---
const int MOTOR_IN3 = 25;
const int MOTOR_IN4 = 26;
const int MOTOR_ENB = 27;

// --- SENSORY I INTERFEJS ---
const int BUTTON_TRAM_PIN = 39;
const int LDR_PIN = 34;    // Fotorezystor
const int BUTTON_SYSTEM_PIN = 36; // Przycisk (VP) z zewnętrznym pull-upem

// --- PARAMETRY ---
const unsigned long DEBOUNCE_DELAY = 50;
const unsigned long LDR_CHECK_DELAY = 2000;
const unsigned long TRAM_STOP_DELAY = 6000;

#endif
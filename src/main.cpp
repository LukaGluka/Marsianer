
#include "calibration.hpp"
#include "moisture.hpp"
#include "watering.hpp"
#include <Arduino.h>

/**
 * @file main.cpp
 * @brief Hauptprogramm des Projekts.
 */
// Werte der Kalibrierung setzen
void
configure()
{
  moisture::airValue = 700;
  moisture::waterValue = 329;
  moisture::waterThreshold = 4;
}

/**
 * @brief Initialisiert die serielle Kommunikation.
 */
void
setup()
{
  Serial.begin(9600);
  // Initialisiere die digitalen Pins

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

/**
 * @brief Hauptprogrammschleife des Projekts.
 */
void
loop()
{
  // Kalibrierungsdaten ausgeben
  calibration::printAll();

  // Feuchtigkeitsmessung
  const int numLevels = 5;
  const int* values = moisture::getValues(numLevels);

  // Bewässerung starten
  watering::run(values, numLevels);

  // Warten bevor der nächste Durchlauf startet
  delay(1000);
}

#include <Arduino.h>

const int dacPin = 25;

void setup() {
  Serial.begin(115200);
  Serial.println("=== SIMULADOR DE pH (ESP32 DAC) ===");
  Serial.println("Ingrese un valor de pH (0 - 14):");
}

void loop() {
  if (Serial.available()) {

    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) return;

    float pH = input.toFloat();

    if (pH < 0 || pH > 14) {
      Serial.println("Error: pH fuera de rango (0-14)");
      return;
    }

    float E = -0.05916 * (pH - 7);
    float Vout = 1.65 + (E * 5.0);

    if (Vout < 0) Vout = 0;
    if (Vout > 3.3) Vout = 3.3;

    int dacValue = (Vout / 3.3) * 255;

    dacWrite(dacPin, dacValue);

    Serial.print("pH: ");
    Serial.print(pH, 2);
    Serial.print(" | Voltaje: ");
    Serial.print(Vout, 3);
    Serial.print(" V | DAC: ");
    Serial.println(dacValue);
  }
}
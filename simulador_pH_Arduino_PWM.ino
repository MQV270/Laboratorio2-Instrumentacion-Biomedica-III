const int pinPWM = 3; // Pin D3 del Arduino

void setup() {
  Serial.begin(115200);
  pinMode(pinPWM, OUTPUT);
  Serial.println("Simulador de pH - Laboratorio 2");
  Serial.println("Ingresa un valor de pH (0 a 14):");
}

void loop() {
  if (Serial.available() > 0) {
    float pH = Serial.parseFloat();
    
    // Limpiar buffer
    while (Serial.available() > 0) Serial.read();

    if (pH >= 0.0 && pH <= 14.0) {
      // Ecuación Nernst del laboratorio
      float Vin = 1.65 - 0.05916 * (pH - 7.0); 
      
      // Mapeo para el PWM de 5V de Arduino (0 a 255)
      int pwmValue = round((Vin / 5.0) * 255.0);
      analogWrite(pinPWM, pwmValue);

      // Reporte por Monitor Serie
      Serial.print("pH ingresado: "); Serial.print(pH);
      Serial.print(" | Vin teorico: "); Serial.print(Vin, 4); Serial.println(" V");
    } else {
      Serial.println("Error: Ingrese un valor de pH entre 0 y 14.");
    }
  }
}
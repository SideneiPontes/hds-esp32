#include <Arduino.h>

// Teste da placa sem sensor: pisca o LED azul da placa e escreve no monitor serial.
#define PIN_LED 2

void setup() {
    Serial.begin(115200);
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("Hello World! LED ligado");
    delay(1000);

    digitalWrite(PIN_LED, LOW);
    Serial.println("Hello World! LED desligado");
    delay(1000);
}

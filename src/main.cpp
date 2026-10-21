#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHT4x.h>

// Ligações (I2C padrão da ESP32):
//   SHT40 VCC -> 3V3
//   SHT40 GND -> GND
//   SHT40 SDA -> GPIO 21
//   SHT40 SCL -> GPIO 22
#define PIN_SDA 21
#define PIN_SCL 22

Adafruit_SHT4x sht4;

// Tenta conectar ao SHT40 a cada 1 s até conseguir.
void conectarSensor() {
    while (!sht4.begin(&Wire)) {
        Serial.println("SHT40 nao encontrado! Verifique as ligacoes. Tentando novamente...");
        delay(1000);
    }

    Serial.print("SHT40 encontrado. Serial: 0x");
    Serial.println(sht4.readSerial(), HEX);

    sht4.setPrecision(SHT4X_HIGH_PRECISION);
    sht4.setHeater(SHT4X_NO_HEATER);
}

void setup() {
    Serial.begin(115200);
    delay(500);

    Wire.begin(PIN_SDA, PIN_SCL);
    conectarSensor();
}

void loop() {
    sensors_event_t umidade, temperatura;
    if (!sht4.getEvent(&umidade, &temperatura)) {
        Serial.println("Falha na leitura do SHT40. Reconectando...");
        conectarSensor();
        return;
    }

    Serial.print("Temperatura: ");
    Serial.print(temperatura.temperature, 2);
    Serial.print(" C  |  Umidade: ");
    Serial.print(umidade.relative_humidity, 2);
    Serial.println(" %");

    delay(2000);
}
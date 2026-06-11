#include <SPI.h>
#include <LoRa.h>

#define SS_PIN    10
#define RST_PIN    9
#define DIO0_PIN   2

#define LED        4

void setup() {

  Serial.begin(9600);
  delay(1000);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa");
    while (1);
  }

  // Configuración idéntica en emisor y receptor
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();

  Serial.println("================================");
  Serial.println("     RECEPTOR LORA LISTO");
  Serial.println("================================");
}

void loop() {

  int packetSize = LoRa.parsePacket();

  if (packetSize <= 0) {
    return;
  }

  // Solo aceptar paquetes de 1 byte
  if (packetSize != 1) {

    Serial.print("Paquete invalido. Tamano: ");
    Serial.println(packetSize);

    while (LoRa.available()) {
      LoRa.read();
    }

    return;
  }

  char dato = LoRa.read();

  Serial.print("Dato recibido: ");
  Serial.println(dato);

  Serial.print("RSSI: ");
  Serial.println(LoRa.packetRssi());

  Serial.print("SNR: ");
  Serial.println(LoRa.packetSnr());

  if (dato == '1') {

    digitalWrite(LED, HIGH);
    Serial.println("LED ENCENDIDO");
    delay(2000);
     digitalWrite(LED, LOW);
    Serial.println("LED APAGADO");

  }
  else if (dato == '0') {

    digitalWrite(LED, LOW);
    Serial.println("LED APAGADO");

  }
  else {

    Serial.println("Dato descartado");
  }

  Serial.println("----------------------------");
}
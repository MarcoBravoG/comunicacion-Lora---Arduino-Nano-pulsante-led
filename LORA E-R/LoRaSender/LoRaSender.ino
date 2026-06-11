#include <SPI.h>
#include <LoRa.h>

#define SS_PIN    10
#define RST_PIN    9
#define DIO0_PIN   2

#define BOTON      3

bool estadoAnterior = HIGH;

void setup() {

  Serial.begin(9600);

  pinMode(BOTON, INPUT_PULLUP);

  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

  if (!LoRa.begin(433E6)) {
    Serial.println("Error al iniciar LoRa");
    while (1);
  }

  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.enableCrc();

  Serial.println("Emisor listo");
}

void loop() {

  bool estadoBoton = digitalRead(BOTON);

  if (estadoBoton != estadoAnterior) {

    delay(30);

    if (estadoBoton == LOW) {

      LoRa.beginPacket();
      LoRa.write('1');
      LoRa.endPacket();

      Serial.println("Enviado: 1");
    }
    else {

      LoRa.beginPacket();
      LoRa.write('0');
      LoRa.endPacket();

      Serial.println("Enviado: 0");
    }

    estadoAnterior = estadoBoton;
  }
}
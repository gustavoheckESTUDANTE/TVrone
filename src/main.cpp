#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

float droneX = 64;
float droneY = 32;
float escalaAtual = 8.0;

#define TRIG 5
#define ECHO 18
#define BUZZER 2 // Pino D2 para o buzzer

// Função auxiliar para desenhar o drone
void desenharDrone(int x, int y, int escala) {
  int offsetHeral = escala + (escala / 2);

  // 1. Desenha os braços/corpo (em forma de X)
  display.drawLine(x - offsetHeral, y - offsetHeral, x + offsetHeral, y + offsetHeral, SSD1306_WHITE);
  display.drawLine(x + offsetHeral, y - offsetHeral, x - offsetHeral, y + offsetHeral, SSD1306_WHITE);

  // 2. Desenha o corpo central
  int tamanhoCorpo = escala;
  if (tamanhoCorpo < 3) tamanhoCorpo = 3;
  display.fillRoundRect(x - (tamanhoCorpo / 2), y - (tamanhoCorpo / 2), tamanhoCorpo, tamanhoCorpo, 1, SSD1306_WHITE);

  // 3. Desenha as 4 hélices
  int raioHelice = escala / 2;
  if (raioHelice < 2) raioHelice = 2;

  display.drawCircle(x - offsetHeral, y - offsetHeral, raioHelice, SSD1306_WHITE); // Superior Esq
  display.drawCircle(x + offsetHeral, y - offsetHeral, raioHelice, SSD1306_WHITE); // Superior Dir
  display.drawCircle(x - offsetHeral, y + offsetHeral, raioHelice, SSD1306_WHITE); // Inferior Esq
  display.drawCircle(x + offsetHeral, y + offsetHeral, raioHelice, SSD1306_WHITE); // Inferior Dir
}

void setup() {
  Wire.begin(21, 22);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // MPU-6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission();

  // HC-SR04
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
}

void loop() {

  // =========================
  // MPU-6050
  // =========================

  int16_t acelX, acelY;

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 4, true);

  acelX = Wire.read() << 8 | Wire.read();
  acelY = Wire.read() << 8 | Wire.read();

  if (acelY > 3000) droneX++;
  if (acelY < -3000) droneX--;

  if (acelX > 3000) droneY++;
  if (acelX < -3000) droneY--;

  // =========================
  // HC-SR04
  // =========================

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH);
  int distancia = duracao * 0.034 / 2;

  // =========================
  // BUZZER (Alerta de proximidade)
  // =========================

  // Apita apenas se estiver muito perto (<= 8cm)
  if (distancia <= 8) {
    tone(BUZZER, 1000); // Apita com tom de 1000Hz
  } else {
    noTone(BUZZER);     // Silêncio para qualquer outra distância
  }

  // Restringe para o mapeamento
  distancia = constrain(distancia, 5, 60);

  // Escala do drone
  int escalaAlvo = map(distancia, 5, 60, 10, 2);

  // Filtro de interpolação
  escalaAtual += (escalaAlvo - escalaAtual) * 0.15;
  int escala = (int)escalaAtual;

  // Limites da tela
  int margem = escala * 2.5;
  droneX = constrain(droneX, margem, 128 - margem);
  droneY = constrain(droneY, margem, 64 - margem);

  // =========================
  // OLED
  // =========================

  display.clearDisplay();

  desenharDrone((int)droneX, (int)droneY, escala);

  display.display();

  delay(20);
}
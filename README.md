# Simulador de Drone Interativo 🛸

Simulador visual de drone em 2D desenvolvido para ESP32/Arduino utilizando uma tela OLED SSD1306, um acelerômetro MPU-6050 para movimentação física e um sensor ultrassônico HC-SR04 com alerta sonoro via buzzer.

---

## 📌 Funcionalidades

* **Controle por Inclinação (2D):** A inclinação do sensor MPU-6050 move o drone nos eixos X e Y da tela OLED.
* **Redimensionamento por Proximidade:** O sensor HC-SR04 lê a distância de um objeto; a aproximação/afastamento escala o tamanho do drone (simulando alteração de altitude).
* **Animação Suave (LERP):** Transição fluida de tamanho do drone usando interpolação linear.
* **Alarme de Proximidade:** Emissão de um tom sonoro de 1000 Hz quando um obstáculo estiver a 8 cm ou menos do sensor.
* **Gráfico Vetorial Personalizado:** Desenho geométrico do drone (corpo, braços em X e 4 hélices) feito via software.

---

## 🛠️ Hardware Necessário

| Componente | Quantidade | Descrição / Protocolo |
| :--- | :--- | :--- |
| **ESP32 ou Arduino** | 1 | Microcontrolador principal |
| **Display OLED SSD1306** | 1 | 128x64 pixels, Comunicação I2C (`0x3C`) |
| **Módulo MPU-6050** | 1 | Acelerômetro e Giroscópio I2C (`0x68`) |
| **Sensor HC-SR04** | 1 | Sensor de distância ultrassônico |
| **Buzzer Passivo/Ativo** | 1 | Emissor de alerta sonoro |
| **Protoboard & Jumpers** | - | Conexões do circuito |

---

## 🔌 Esquema de Conexões (Pinout)

### Barramento I2C (Compartilhado)
> **Nota:** Tanto a tela OLED quanto o MPU-6050 compartilham os mesmos pinos de dados I2C.

| Componente | Pino do Componente | Pino do ESP32 |
| :--- | :--- | :--- |
| **OLED / MPU-6050** | `SDA` | GPIO 21 |
| **OLED / MPU-6050** | `SCL` | GPIO 22 |
| **OLED / MPU-6050** | `VCC` | 3.3V / 5V |
| **OLED / MPU-6050** | `GND` | GND |

### Sensores e Atuadores Individuais

| Componente | Pino do Componente | Pino do ESP32 |
| :--- | :--- | :--- |
| **HC-SR04** | `TRIG` | GPIO 5 |
| **HC-SR04** | `ECHO` | GPIO 18 |
| **HC-SR04** | `VCC` / `GND` | 5V / GND |
| **Buzzer** | `(+) / Signal` | GPIO 2 |
| **Buzzer** | `(-)` | GND |

---

## 📚 Bibliotecas Necessárias

Para compilar o código na **Arduino IDE** ou **PlatformIO**, instale as seguintes bibliotecas pelo Gerenciador de Bibliotecas (*Library Manager*):

1. **Adafruit GFX Library** (por Adafruit)
2. **Adafruit SSD1306** (por Adafruit)
3. **Wire** (já embutida na plataforma Arduino)

---

## 🚀 Como Executar o Projeto

1. Monte o circuito conforme a tabela de conexões.
2. Abra a **Arduino IDE**.
3. Selecione a sua placa (ex: `ESP32 Dev Module`) e a porta COM correspondente.
4. Instale as bibliotecas listadas no Gerenciador de Bibliotecas.
5. Copie o código fonte para o arquivo `.ino` ou `main.cpp`.
6. Realize o upload para a placa.
7. Mova e incline a placa para controlar o drone na tela!

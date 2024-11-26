# Proyecto IoT: Página Web con Sensor DHT11 y Arduino

Este proyecto integra el sensor DHT11 (para medir temperatura y humedad) con un Arduino que envía los datos a una página web en tiempo real.

## Requisitos

### Hardware
- Arduino Uno (o compatible).
- Sensor DHT11.
- Resistencia de 10kΩ (si es necesario para el DHT11).
- Módulo Wi-Fi ESP8266 o ESP32 (opcional para IoT).
- Cables y protoboard.

### Software
- IDE de Arduino.
- Librería `DHT` para Arduino.
- Servidor local (p. ej., Node.js, Python Flask o cualquier HTTP server).
- Navegador web para visualizar la interfaz.

---

## Esquema de conexión

1. **DHT11 a Arduino**:
   - **VCC** → 5V (o 3.3V según el módulo).
   - **GND** → GND.
   - **DATA** → Pin digital del Arduino (ej.: Pin 2).

2. **Módulo Wi-Fi** (opcional):
   - **TX/RX** → Conexión UART al Arduino.
   - **VCC** → Alimentación adecuada (normalmente 3.3V).
   - **GND** → GND.

---

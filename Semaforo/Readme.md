# Práctica : Semáforo Vehicular y Peatonal con FSM

Sistema de control no bloqueante para un semáforo vehicular y peatonal interactivo utilizando una **Máquina de Estados Finitos (FSM)** en Arduino.

---

## 📌 Descripción
Este proyecto implementa la lógica de tránsito vehicular y peatonal prioritaria. La secuencia gestiona el paso de vehículos y atiende las solicitudes de paso peatonal activadas por un pulsador, empleando un filtro antirrebote (*debounce*) por software.

Toda la temporización del sistema utiliza la función nativa `millis()` en lugar de `delay()`, garantizando un flujo no bloqueante y multitarea reactiva.

---

## 🛠️ Materiales
* 1x Placa Arduino UNO (R3 / R4)
* 1x Protoboard
* 5x LEDs (Rojo, Amarillo, Verde Vehicular; Rojo, Verde Peatonal)
* 5x Resistencias de 220 Ω
* 1x Pulsador (*Pushbutton*)
* Cables de conexión (*jumpers*)

---

## 🔌 Mapeo de Pines y Conexiones

| Componente | Pin Arduino | Configuración / Topología |
| :--- | :--- | :--- |
| **Pulsador Peatonal** | Pin 2 | Entrada con `INPUT_PULLUP` interno (Conectado a GND) |
| **LED Peatonal Rojo** | Pin 6 | Salida Digital (Cátodo con Resistencia 220 Ω a GND) |
| **LED Peatonal Verde** | Pin 7 | Salida Digital (Cátodo con Resistencia 220 Ω a GND) |
| **LED Vehicular Rojo** | Pin 8 | Salida Digital (Cátodo con Resistencia 220 Ω a GND) |
| **LED Vehicular Amarillo** | Pin 9 | Salida Digital (Cátodo con Resistencia 220 Ω a GND) |
| **LED Vehicular Verde** | Pin 10 | Salida Digital (Cátodo con Resistencia 220 Ω a GND) |

---

## 🚦 Máquina de Estados (FSM)

El sistema utiliza la estructura `enum class EstadoSemaforo` con 4 estados principales:

1. **`VERDE_VEHICULO`**: Flujo vehicular encendido (Pin 10) y paso peatonal bloqueado (Pin 6). Permanece activo un mínimo de 5000 ms y hasta detectar una solicitud peatonal.
2. **`AMARILLO_VEHICULO`**: Transición de advertencia vehicular (Pin 9) con duración de 2000 ms.
3. **`VERDE_PEATON`**: Detención vehicular (Pin 8) y habilitación de paso peatonal (Pin 7) durante 4000 ms.
4. **`PARPADEO_PEATON`**: Cierre de paso peatonal mediante intermitencia del LED verde a intervalos de 250 ms durante 2000 ms, antes de regresar al flujo vehicular.

---

## ⚙️ Tiempos de Configuración
* **Verde Vehicular Mínimo:** 5000 ms
* **Amarillo Vehicular:** 2000 ms
* **Verde Peatonal:** 4000 ms
* **Parpadeo Peatonal:** 2000 ms (250 ms por conmutación)
* **Antirrebote (Debounce):** 50 ms

---

## 🚀 Ejecución en Arduino IDE
1. Abre el archivo `.ino` en Arduino IDE o Tinkercad.
2. Selecciona la placa **Arduino Uno** y el puerto COM correspondiente.
3. Configura el **Monitor Serie** a `115200 baudios` para observar las trazas de estado y registros de pulsación en tiempo real.
4. Compila y carga el programa en la placa.

# Práctica 2.2 — Paradigmas de Ejecución: delay() vs millis()

**Materia:** Sistemas Programables  
**Alumno:** Morales Ramirez Jonathan Alexis  
**Fecha:** Septiembre 2026

---

## 📋 Descripción del Proyecto

Esta práctica compara dos paradigmas de ejecución en Arduino para el control simultáneo de múltiples LEDs:

- **Parte 1 — Antipatrón con `delay()`:** Parpadeo de tres LEDs con retardos bloqueantes.
- **Parte 2 — Temporización no bloqueante con `millis()`:** Cada LED parpadea de forma independiente y simultánea.

---

## 🎯 Objetivos

- Identificar el comportamiento bloqueante de `delay()` en sistemas con múltiples tareas.
- Implementar temporización no bloqueante con `millis()` para tres LEDs con distintos intervalos.
- Comparar ambos enfoques en términos de concurrencia, escalabilidad y respuesta del sistema.

---

## 🛠️ Herramientas y Componentes

| Elemento | Descripción |
|---|---|
| Microcontrolador | Arduino UNO R4 WiFi |
| IDE | Arduino IDE 2.x |
| Lenguaje | C++ (Arduino) |
| Componentes | 3 LEDs, 3 resistencias 220Ω, protoboard, cables |

---

## 📁 Estructura del Repositorio



---

## ⚙️ Parte 1 — delay()

Cada LED se enciende y apaga con `delay()`, lo que bloquea el microcontrolador. Los LEDs corren de forma **secuencial**, acumulando un ciclo total de **6000 ms**.

### Diagrama del circuito

![Diagrama del circuito](Diagrama/Diagrama%20Leds.png)

### Circuito físico

![Circuito con delay](Diagrama/Leds%20Delay.jpeg)

### 🎬 Video de evidencia
https://youtube.com/shorts/LCgG4536u_I

---

## ⚙️ Parte 2 — millis()

Cada LED gestiona su propio intervalo con `millis()`. Los tres parpadean **simultáneamente e independiente**, y además se imprime "Hola Mundo" al Monitor Serial cada 3000 ms como cuarta tarea concurrente.

### Circuito físico

![Circuito con millis](Diagrama/Leds%20Milic.png)

### 🎬 Video de evidencia
https://youtube.com/shorts/VZnIhfNHM9s

---

## 📊 Comparación de resultados

| Aspecto | `delay()` | `millis()` |
|---|---|---|
| Ejecución | Secuencial (bloqueante) | Concurrente (no bloqueante) |
| Ciclo real de LED1 | 6000 ms | 500 ms |
| Ciclo real de LED2 | 6000 ms | 1000 ms |
| Ciclo real de LED3 | 6000 ms | 1500 ms |
| Escalabilidad | Baja | Alta |
| Respuesta a entradas | Bloqueada | Siempre activa |

---

## ✅ Conclusión

`millis()` es superior para manejar múltiples temporizaciones en Arduino. Mantiene el sistema siempre activo y receptivo, indispensable en proyectos reales con varios componentes simultáneos.

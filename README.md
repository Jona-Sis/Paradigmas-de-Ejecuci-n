# Luces LEDs: Delay vs. Millis

Comparación práctica entre el uso bloqueante de `delay()` y la temporización no bloqueante con `millis()` para controlar tres LEDs con distintos intervalos de parpadeo.

## Descripción

Este proyecto se divide en dos partes que utilizan exactamente el mismo circuito físico (tres LEDs conectados a los pines 2, 3 y 4 del Arduino), pero con dos enfoques de código diferentes:

* **Parte 1 — Delay:** cada LED se controla con `delay()`, evidenciando el comportamiento bloqueante y secuencial de esta función.
* **Parte 2 — Millis:** los mismos LEDs se controlan con `millis()`, logrando que cada uno parpadee de forma verdaderamente independiente, además de una tarea extra que imprime un mensaje por el Monitor Serial cada 3 segundos.

## Objetivos de aprendizaje

Comprender la diferencia entre temporización bloqueante y no bloqueante en Arduino, identificando por qué `delay()` es un antipatrón cuando se necesita controlar múltiples tareas con distintos intervalos, y cómo `millis()` resuelve ese problema.

## Material utilizado

* Arduino UNO R4 WiFi
* Protoboard
* 3 LEDs de colores distintos
* 3 resistencias limitadoras de corriente
* Cables de conexión (jumpers)
* Cable USB para alimentación y programación

## Diagrama del circuito

El mismo circuito se utiliza para ambas partes del proyecto:

![Diagrama del circuito](Diagrama/Diagrama%20Leds.jpeg)

---

## Parte 1 — Delay (antipatrón bloqueante)

### Código
[Led Delay.ino](Codigo/Led%20Delay.ino)

### Diagrama / Montaje físico
![Diagrama del circuito](Diagrama/Diagrama%20Leds.jpeg)

<img src="Diagrama/LEDS%20Delay.jpeg" width="600">

### Reporte
[LEDs_Reporte.pdf](Reporte/LEDs_Reporte.pdf)

### Resultado
[LEDs_Resultado.pdf](Resultados/LEDs_Resultado.pdf)

### Video del funcionamiento
[Ver video en YouTube](https://youtu.be/vMpkRXAOzlQ)

---

## Parte 2 — Millis (temporización no bloqueante)

### Código
[Led Milis.ino](Codigo/Led%20Milis.ino)

### Diagrama / Terminal
![Diagrama del circuito](Diagrama/Diagrama%20Leds.jpeg)

<img src="Diagrama/LEds%20Milic.png" width="600">

### Reporte
[Reporte_Parte2.pdf](Reporte/Reporte_Parte2.pdf)

### Resultado
[Resultado_Parte2.pdf](Resultados/Resultado_Parte2.pdf)

### Video del funcionamiento
[Ver video en YouTube](https://youtu.be/kqTjK1f68YY)

---

## Conclusiones

Esta práctica permitió comparar de forma directa dos estrategias de temporización en Arduino usando el mismo circuito. Mientras que `delay()` obliga a ejecutar las tareas de forma secuencial (sumando todos los tiempos de espera), `millis()` permite que cada tarea se ejecute de manera independiente y concurrente, sin bloquear la ejecución del resto del programa. Este segundo enfoque es la base para proyectos más complejos que necesitan responder a sensores, comunicación en red o múltiples actuadores en tiempo real

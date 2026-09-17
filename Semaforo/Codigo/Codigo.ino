/*
  Práctica 3: Semáforo Vehicular y Peatonal (FSM)
  Mapeo de Pines:
  - Vehicular: Rojo (Pin 8), Amarillo (Pin 9), Verde (Pin 10)
  - Peatonal:  Rojo (Pin 6), Verde (Pin 7)
  - Botón:     Pin 2 (Usa INPUT_PULLUP interno)
*/

// Asignación de Pines
const uint8_t LED_VEH_ROJO     = 8;
const uint8_t LED_VEH_AMARILLO = 9;
const uint8_t LED_VEH_VERDE    = 10;

const uint8_t LED_PEAT_ROJO    = 6;
const uint8_t LED_PEAT_VERDE   = 7;

const uint8_t BOTON_PEATON     = 2;

// Definición de la Máquina de Estados Finita
enum class EstadoSemaforo {
  VERDE_VEHICULO,
  AMARILLO_VEHICULO,
  VERDE_PEATON,
  PARPADEO_PEATON
};

EstadoSemaforo estadoActual = EstadoSemaforo::VERDE_VEHICULO;

// Intervalos de tiempo (milisegundos)
const unsigned long TIEMPO_VERDE_VEH   = 5000;
const unsigned long TIEMPO_AMARILLO    = 2000;
const unsigned long TIEMPO_VERDE_PEAT  = 4000;
const unsigned long TIEMPO_PARPADEO    = 2000;
const unsigned long INTERVALO_PARPADEO = 250;

// Variables de temporización y banderas
unsigned long tiempoInicioEstado = 0;
unsigned long ultimoParpadeo = 0;
bool solicitudPeaton = false;

// Variables para el filtro anti-rebote (Debounce)
unsigned long ultimoDebounce = 0;
const unsigned long TIEMPO_DEBOUNCE = 50;
bool ultimoEstadoBoton = HIGH;

void setup() {
  pinMode(LED_VEH_ROJO, OUTPUT);
  pinMode(LED_VEH_AMARILLO, OUTPUT);
  pinMode(LED_VEH_VERDE, OUTPUT);
  
  pinMode(LED_PEAT_ROJO, OUTPUT);
  pinMode(LED_PEAT_VERDE, OUTPUT);
  
  pinMode(BOTON_PEATON, INPUT_PULLUP);
  
  Serial.begin(115200);
  Serial.println("--- Sistema FSM Iniciado ---");
  
  tiempoInicioEstado = millis();
}

void loop() {
  unsigned long ahora = millis();
  
  // 1. Lectura del botón con Debounce
  bool lecturaBoton = digitalRead(BOTON_PEATON);
  if (lecturaBoton != ultimoEstadoBoton) {
    ultimoDebounce = ahora;
  }
  if ((ahora - ultimoDebounce) > TIEMPO_DEBOUNCE) {
    if (lecturaBoton == LOW) {
      if (!solicitudPeaton) {
        solicitudPeaton = true;
        Serial.println("-> Solicitud peatonal registrada.");
      }
    }
  }
  ultimoEstadoBoton = lecturaBoton;

  // 2. Control de Estados (FSM)
  switch (estadoActual) {
    
    case EstadoSemaforo::VERDE_VEHICULO:
      digitalWrite(LED_VEH_ROJO, LOW);
      digitalWrite(LED_VEH_AMARILLO, LOW);
      digitalWrite(LED_VEH_VERDE, HIGH);
      
      digitalWrite(LED_PEAT_ROJO, HIGH);
      digitalWrite(LED_PEAT_VERDE, LOW);
      
      if ((ahora - tiempoInicioEstado >= TIEMPO_VERDE_VEH) && solicitudPeaton) {
        estadoActual = EstadoSemaforo::AMARILLO_VEHICULO;
        tiempoInicioEstado = ahora;
        Serial.println("Estado: Amarillo Vehicular");
      }
      break;

    case EstadoSemaforo::AMARILLO_VEHICULO:
      digitalWrite(LED_VEH_VERDE, LOW);
      digitalWrite(LED_VEH_AMARILLO, HIGH);
      
      if (ahora - tiempoInicioEstado >= TIEMPO_AMARILLO) {
        estadoActual = EstadoSemaforo::VERDE_PEATON;
        tiempoInicioEstado = ahora;
        solicitudPeaton = false;
        Serial.println("Estado: Verde Peatonal");
      }
      break;

    case EstadoSemaforo::VERDE_PEATON:
      digitalWrite(LED_VEH_AMARILLO, LOW);
      digitalWrite(LED_VEH_ROJO, HIGH);
      
      digitalWrite(LED_PEAT_ROJO, LOW);
      digitalWrite(LED_PEAT_VERDE, HIGH);
      
      if (ahora - tiempoInicioEstado >= TIEMPO_VERDE_PEAT) {
        estadoActual = EstadoSemaforo::PARPADEO_PEATON;
        tiempoInicioEstado = ahora;
        ultimoParpadeo = ahora;
        Serial.println("Estado: Parpadeo Peatonal");
      }
      break;

    case EstadoSemaforo::PARPADEO_PEATON:
      if (ahora - ultimoParpadeo >= INTERVALO_PARPADEO) {
        ultimoParpadeo = ahora;
        digitalWrite(LED_PEAT_VERDE, !digitalRead(LED_PEAT_VERDE));
      }
      
      if (ahora - tiempoInicioEstado >= TIEMPO_PARPADEO) {
        estadoActual = EstadoSemaforo::VERDE_VEHICULO;
        tiempoInicioEstado = ahora;
        Serial.println("Estado: Verde Vehicular");
      }
      break;
  }
}

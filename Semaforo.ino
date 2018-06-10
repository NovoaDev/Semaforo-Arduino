#include <SR04.h>

// Nombre de colores asociados con la salidas digitales correspondiente.
#define PEATON_LED_ROJO 2
#define PEATON_LED_vERDE 3
#define PEATON_BUZZER 4
#define COCHE_LED_ROJO 5
#define COCHE_LED_AMARILLO 6
#define COCHE_LED_VERDE 7
#define BOTTON_PEATON 8
#define ECHO_PIN 9
#define TRIG_PIN 10

bool bPasoPeatonesActivo = true; 
int iTiempoCambioLed = 5000; 
int iTiempoEntreSemaforo = 1500;
int iTiempoCambioSemaforo = 5000;  
int iPulsadorPeatones;
int iPulsadorCoches;  
int iIteradorCoches;
int iBottonEmergencia;
long a;
  
//SENSOR SR04
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void setup() {
  Serial.begin(9600);
 
  // Definir funcionamiento de cada PIN
  pinMode(PEATON_LED_ROJO, OUTPUT);
  pinMode(PEATON_LED_vERDE, OUTPUT);
  pinMode(PEATON_BUZZER, OUTPUT);
  pinMode(COCHE_LED_ROJO, OUTPUT);
  pinMode(COCHE_LED_AMARILLO, OUTPUT);
  pinMode(COCHE_LED_VERDE, OUTPUT);
  pinMode(BOTTON_PEATON, INPUT);
  
  // Estado inicial: semaforo de peatones en verde y coches en rojo
  digitalWrite(PEATON_LED_ROJO, LOW);
  digitalWrite(PEATON_LED_vERDE, HIGH);
  digitalWrite(COCHE_LED_ROJO, HIGH);
  digitalWrite(COCHE_LED_AMARILLO, LOW);
  digitalWrite(COCHE_LED_VERDE, LOW);
  bPasoPeatonesActivo = true;
}
 
void loop() {   
  if (bPasoPeatonesActivo){
    sensorProximidad();
    semaforoPeatones(); 
  } else {
    iPulsadorPeatones = digitalRead(BOTTON_PEATON);
    if (iPulsadorPeatones == HIGH) {
      semaforoCoches();
      bPasoPeatonesActivo = true;
    }
  }
}

void semaforoPeatones() {
  delay(iTiempoCambioSemaforo-3000);
  for (int i = 0; i <= 6; i++) {
    digitalWrite(PEATON_LED_vERDE, LOW);
    delay(250);
    digitalWrite(PEATON_LED_vERDE, HIGH);               
    delay(250); 
    sonarBuzzer("CORTO");
  }

  digitalWrite(PEATON_LED_vERDE, LOW);
  digitalWrite(PEATON_LED_ROJO, HIGH);
 
  delay(iTiempoEntreSemaforo);

  digitalWrite(COCHE_LED_ROJO, LOW);
  digitalWrite(COCHE_LED_VERDE, HIGH);
  bPasoPeatonesActivo = false;    
}
 
void semaforoCoches() {
  delay(iTiempoCambioSemaforo);
  digitalWrite(COCHE_LED_VERDE, LOW);
  digitalWrite(COCHE_LED_AMARILLO, HIGH);

  delay(iTiempoCambioLed);
 
  digitalWrite(COCHE_LED_AMARILLO, LOW);
  digitalWrite(COCHE_LED_ROJO, HIGH);
 
  delay(iTiempoEntreSemaforo);
 
  digitalWrite(PEATON_LED_ROJO, LOW);
  digitalWrite(PEATON_LED_vERDE, HIGH);
  bPasoPeatonesActivo = true;
  sonarBuzzer("LARGO");
}
 
void sonarBuzzer(String sVelocidad) {  
  if (sVelocidad == "CORTO") {
    for (int i = 0; i <= 8; i++) { 
      tone(PEATON_BUZZER, 500); 
      delay(50);               
      noTone(PEATON_BUZZER); 
      delay(50); 
    }
  } else { sensorProximidad(); }
}

void sensorProximidad() {
  int iX = 1;
  while (iX==1){ 
    a=sr04.Distance();
    delay(400);
    
    tone(PEATON_BUZZER, 500); 
    delay(150);               
    noTone(PEATON_BUZZER); 
    delay(150);
        
    if ((a <= 100) and (a > 0 )) {
      iIteradorCoches++;
    } else { iIteradorCoches = 0; }
  
    if (iIteradorCoches >= 6) {
      iIteradorCoches = 0;
      iX=2;
      
    }
  }  
}



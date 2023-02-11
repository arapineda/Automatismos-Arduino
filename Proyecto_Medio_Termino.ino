int Altura = 23; // Distancia Sensor al piso en cm
int Vaso = 14; // Altura del vaso en cm
int R, G, B; // Variables para R, G y B
float Frio = 20 ; float Caliente = 100; // En centigrados

float n=1;

// Dip Switch

int DSU = 2;
int DSD = 3;
int DST = 4;

int P1, P2, P3;

// Temperatura

int tempPin = A0;
int tval;

// Nivel

int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
long duration, cm, Nivel;

// LEDS

#include <Adafruit_NeoPixel.h>

int PIN =6;
int NumLEDS= 24;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NumLEDS, PIN, NEO_GRB + NEO_KHZ800);



void setup() {

// DIP Switch

  pinMode(DSU, INPUT);
  pinMode(DSD, INPUT);
  pinMode(DST, INPUT);
  
// Nivel

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

// LEDS
  pixels.begin();
  pixels.show();
  
}

void loop() {
  
  float NivelxLED = .6; // 1 Led equivale a x nivel de agua
  
// Calculo de Temperatura (Temp)
  tval = analogRead(tempPin);
  float volt = ( tval/1024.0)*5000;
  float Temp = volt/10 - 10;
 // Temp = 1.905*Temp - 23.373; // ? regresión lineal
  Serial.println(Temp);



// Calculo de Nivel (Nivel: en cm) (NivelLEDS: leds equivalentes al nivel)
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1; 
  Nivel = Altura - cm;
  int NivelLEDS = (Nivel / NivelxLED);

  
  //


// Seleción de Modo
  P1 = digitalRead(DSU);
  P2 = digitalRead(DSD);
  P3 = digitalRead(DST);

// Modo 1
  if (P1 == 1 & P2 == 0 & P3 == 0) {

    // Se definen los colores a partir de la temperatura
    
    if (Temp <= Frio) {
      R=0 ; G=0 ; B=225 ;
    }
    else if (Temp >= Caliente) {
      R=225 ; G=0 ; B=0 ; 
    }
    else {
       R=225 ; G=0 ; B=225 ; 
    }

    // Se iluminan los leds dependiendo del nivel, si no hay liquido no se ilumina nada
    if (Nivel > n ){
        for (int i = 0; i<= NivelLEDS; i++){
          pixels.setPixelColor(i,R,G,B);
          pixels.show();
        }
    // Se apagan el resto de los LEDS

        for (int i = NivelLEDS + 1; i<= NumLEDS; i++){
          pixels.setPixelColor(i,0,0,0);
          pixels.show();
        }
    }

    // Se apagan los LEDS si no hay liquido
    else {
      for (int i = 0; i<= NumLEDS; i++) {
          pixels.setPixelColor(i,0,0,0);
          pixels.show();
      }
    }
  }
  

// Modo 2

 else if (P2 == 1 & P1 == 0 & P3 == 0) {

      // Se iluminan los leds dependiendo del nivel, si no hay liquido no se ilumina nada
    if (Nivel > n ){
            if (NivelLEDS<=8){
              R=225; G=0; B=0;
            }
            else if (NivelLEDS>=17){
              R=0; G=225; B=0;
            }
            else {
             R=225; G=225; B=0;
            }
          for (int i = 0; i<= NumLEDS; i++){
            pixels.setPixelColor(i,R,G,B);
            pixels.show();
          }
    }

    // Se apagan los LEDS si no hay liquido
    else {
      for (int i = 0; i<= NumLEDS; i++) {
          pixels.setPixelColor(i,0,0,0);
          pixels.show();
      }
    }
    
 }


// Modo 3

 else if (P2 == 0 & P1 == 0 & P3 == 1) {
      // Se iluminan los leds dependiendo del nivel, si no hay liquido no se ilumina nada
    if (Nivel > n ){
           if (Temp<=Frio){
              R=0; G=0; B=225;
            }
            else if (Temp>=Caliente){
              R=225; G=0; B=0;
            }
            else {
             R=255; G=0; B=225;
            }
          for (int i = 0; i<= NumLEDS; i++){
            pixels.setPixelColor(i,R,G,B);
            pixels.show();
          }
    }

    // Se apagan los LEDS si no hay liquido
    else {
      for (int i = 0; i<= NumLEDS; i++) {
          pixels.setPixelColor(i,0,0,0);
          pixels.show();
      }
    }
 }


// Si es otro caso, no se prende ningún LED
 else{
  for (int i = 0; i<= NumLEDS; i++) {
          pixels.setPixelColor(i,0,0,0);
          pixels.show();
      }
 }

}

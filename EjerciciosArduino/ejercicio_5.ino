/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/

//Ejercicio 5
int sensorPinAnalogic = A2; 
int sensorPin = 3;    // select the input pin for the potentiometer
int i=0;



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(sensorPin, OUTPUT);

}

void loop() {

  int sensorValue = 0;
  
  for (i=0;i<=255;i++){
    analogWrite(sensorPin,i+analogRead(sensorPinAnalogic));
    delay(10);
  }

   for (i=255;i>=0;i--){
    analogWrite(sensorPin,i+analogRead(sensorPinAnalogic));
    delay(10);
  }

 
  
}

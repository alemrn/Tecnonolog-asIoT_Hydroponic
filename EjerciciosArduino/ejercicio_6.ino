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

const unsigned char cie[256] = {
  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 
  2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 
  3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 
  5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 
  7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 
  10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 
  13, 14, 14, 15, 15, 15, 16, 16, 17, 17, 
  17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 
  22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 
  28, 28, 29, 29, 30, 31, 31, 32, 32, 33, 
  34, 34, 35, 36, 37, 37, 38, 39, 39, 40, 
  41, 42, 43, 43, 44, 45, 46, 47, 47, 48, 
  49, 50, 51, 52, 53, 54, 54, 55, 56, 57, 
  58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 
  68, 70, 71, 72, 73, 74, 75, 76, 77, 79, 
  80, 81, 82, 83, 85, 86, 87, 88, 90, 91, 
  92, 94, 95, 96, 98, 99, 100, 102, 103, 105, 
  106, 108, 109, 110, 112, 113, 115, 116, 118, 120, 
  121, 123, 124, 126, 128, 129, 131, 132, 134, 136, 
  138, 139, 141, 143, 145, 146, 148, 150, 152, 154, 
  155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 
  175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 
  196, 198, 200, 202, 204, 207, 209, 211, 214, 216, 
  218, 220, 223, 225, 228, 230, 232, 235, 237, 240, 
  242, 245, 247, 250, 252, 255, 
};



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(sensorPin, OUTPUT);
  Serial.begin(9600); 

}

void loop() {

  int sensorValue = 0;
  
  for (i=0;i<=255;i++){
    sensorValue=analogRead(sensorPinAnalogic);
    analogWrite(sensorPin,cie[i]+sensorValue);
    delay(sensorValue);
    Serial.println(cie[i]);
  }

   for (i=255;i>=0;i--){
    sensorValue=analogRead(sensorPinAnalogic);
    analogWrite(sensorPin,cie[i]+sensorValue);
    delay(sensorValue);
     Serial.println(cie[i]);
  }

 
  
}

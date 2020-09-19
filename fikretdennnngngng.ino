
#include <SoftwareSerial.h>
SoftwareSerial BTserial(8, 9); // RX | TX
const long baudRate = 9600;
const int analogInPin = A0;
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int sensorValue = 0;
float Vsens = 0.0;
float Press;
float Vs = 5;


void setup() {
  Serial.begin(9600);
  BTserial.begin(baudRate);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  sensorValue = analogRead(analogInPin);
  
  /*total = total - readings[readIndex];
  readings[readIndex] = float(sensorValue);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  
  Vsens = average*Vs/1023.0;*/
  Vsens = sensorValue*Vs/1023.0;
  Press = (Vsens-(0.04*Vs))/(Vs*0.000901);
  Press = Press*0.145037;
  if(Press < 0){Press = Press*(-1);}
  //Serial.print("Vsensor = ");
  //Serial.print(Vsens);
  //Serial.print("V");
  //Serial.print("\t\tPressure = ");
  Serial.println(Press);
  //Serial.print("Kpa");
  //Serial.println();
  //BTserial.print("    ");                     
  BTserial.print(Press);
  BTserial.print(" Psi");
  //BTserial.print(sensorValue);
  BTserial.println();
  delay(500);
}

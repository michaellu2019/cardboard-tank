#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// radio
RF24 radio(9, 10);
const byte address[6] = "00001";
int data[3];
int interval = 10;

// potentiometer
int potPin = A0;
int potVal = -1;

// joystick one
int joy1Pin = A1;
int joy1Val = -1;
int joy1Tol = 12;

// joystick two
int joy2Pin = A2;
int joy2Val = -1;
int joy2Tol = 4;

int minPWM = 70;
int maxPWM = 245;

void setup() {
  // serial
  Serial.begin(9600);
  Serial.println("INIT");

  // radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
  
  // potentiometer and joysticks
  pinMode(potPin, INPUT);
  pinMode(joy1Pin, INPUT);
  pinMode(joy2Pin, INPUT);
}

void loop() {
  // store sensor values
  potVal = map(analogRead(potPin), 0, 1023, 180, 0);
  joy1Val = map(analogRead(joy1Pin), 0, 1023, -255, 255);
  joy2Val = map(analogRead(joy2Pin), 0, 1023, -255, 255);

  // rounds off joystick values
  if (abs(joy1Val) < joy1Tol) {
    joy1Val = 0;
  }

  if (abs(joy2Val) < joy2Tol) {
    joy2Val = 0;
  }

  // maps joystick values
  if (joy1Val < 0) {
//    joy1Val = expMap(abs(joy1Val), 0, 255, 0, 255, 2);
    joy1Val = map(abs(joy1Val), 0, 255, minPWM, maxPWM);
    joy1Val *= -1;
  } else {
//    joy1Val = expMap(joy1Val, 0, 255, 0, 255, 2);
    joy1Val = map(joy1Val, 0, 255, minPWM, maxPWM);
  }

  if (joy2Val < 0) {
//    joy2Val = expMap(abs(joy2Val), 0, 255, 0, 255, 2);
    joy2Val = map(abs(joy2Val), 0, 255, minPWM, maxPWM);
    joy2Val *= -1;
  } else {
//    joy2Val = expMap(joy2Val, 0, 255, 0, 255, 2);
    joy2Val = map(joy2Val, 0, 255, minPWM, maxPWM);
  }

  // rounds off joystick values
  if (abs(joy1Val) - minPWM < joy1Tol) {
    joy1Val = 0;
  }

  if (abs(joy2Val) - minPWM < joy2Tol) {
    joy2Val = 0;
  }
    
  
  // store data and send it
  data[0] = potVal;
  data[1] = joy1Val;
  data[2] = joy2Val;
  
  radio.write(data, sizeof(data));

  // print data
  Serial.print(data[0]);
  Serial.print(", ");
  Serial.print(data[1]);
  Serial.print(", ");
  Serial.print(data[2]);
  Serial.println();

  delay(interval);
}

// logarithmic mapping
long logMap(long x, long in_min, long in_max, long out_min, long out_max, int b) {
  double a = (out_max - out_min)/log(b, in_max + 1 - in_min);

  return a * log(b, x + 1 - in_min) + out_min;
}

// logarithm function with base parameter for convenience
double log(int b, long x) {
  return log(x)/log(b);
}

// exponential mapping
long expMap(long x, long in_min, long in_max, long out_min, long out_max, int b) {
  double a = log(b, out_max + 2 - out_min)/(in_max - in_min);

  return pow(b, a * (x - in_min)) - 1 + out_min;
}


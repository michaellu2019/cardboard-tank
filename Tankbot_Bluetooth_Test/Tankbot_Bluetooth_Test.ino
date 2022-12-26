#include <ArduinoMotorShieldR3.h>
#include <Servo.h>

// servo
Servo servo;
int servoData = 0;

// motors
ArduinoMotorShieldR3 motorShield;
int motorAData = 0;
int motorBData = 0;

// leds
int ledPin = 2;

uint8_t data[50];

String readString;

// motor functions
void aRun(int speed) {
  motorShield.setM1Speed(speed);
}

void bRun(int speed) {
  motorShield.setM2Speed(-speed);
}
 
void setup() {
  // setup bluetooth
  Serial.begin(9600);
  
  // setup motor shield
  motorShield.init();

  // setup servo
  servo.attach(6);
  servo.write(90);

  // setup leds
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  Serial.println("Ready");
}
 
void loop() {
  aRun(100);
  bRun(100);
  delay(1000);

  aRun(-100);
  bRun(-100);
  delay(1000);
  
  aRun(-100);
  bRun(100);
  delay(1000);
  
  aRun(100);
  bRun(-100);
  delay(1000);
}

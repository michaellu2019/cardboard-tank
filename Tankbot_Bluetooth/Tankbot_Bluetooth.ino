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
  motorShield.setM1Speed(-speed);
}

void bRun(int speed) {
  motorShield.setM2Speed(speed);
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
    // code source: http://forum.arduino.cc/index.php?topic=287596.0
    if (Serial.available())  {
      char c = Serial.read();
      if (c == ',') {
        if (readString.length() > 1) {
          int n = readString.toInt();

          if (readString.indexOf('t') > 0) servo.write(n);
          if (readString.indexOf('a') > 0) aRun(n);
          if (readString.indexOf('b') > 0) bRun(n);

          readString = "";
        }
      } else {     
        readString += c;
      }
    }
}

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// radio
RF24 radio(9, 10);
const byte address[6] = "00001";
int data[3];

// motor one
int enA = 3;
int in1 = 2;
int in2 = 4;
int motor1Val = -1;
double spdF1 = 1.0;

// motor two
int enB = 5;
int in3 = 7;
int in4 = 8;
int motor2Val = -1;
double spdF2 = 0.9;

// servo
Servo servo;
int servoPin = 14;
int servoVal = -1;

void setup() {
  // serial
  Serial.begin(9600);
  Serial.println("INIT");

  // radio
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  
  // motors
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // servo
  servo.attach(servoPin);
  servo.write(90);
}

void loop() {
  if (radio.available()) {
    // receive data and store it
    radio.read(data, sizeof(data));
    
    servoVal = data[0];
    motor1Val = data[1];
    motor2Val = data[2];

    // print data
    Serial.print(servoVal);
    Serial.print(", ");
    Serial.print(motor1Val);
    Serial.print(", ");
    Serial.print(motor2Val);
    Serial.println();

    // servo value
    servo.write(servoVal);
    runMotorOne(motor1Val);
    runMotorTwo(motor2Val);
  } else {
    Serial.println("NO COMMUNICATION");
  }
}

// motor control methods
void runMotorOne(int speed) {
  // adjust speed based on speed adjustment factor
  int newSpeed = spdF1 * speed;

  // control motor direction
  if (speed < 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (speed > 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }

  // set motor speed
  analogWrite(enA, abs(newSpeed));
}

void runMotorTwo(int speed) {
  // adjust speed based on speed adjustment factor
  int newSpeed = spdF2 * speed;

  // control motor direction
  if (speed < 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (speed > 0) {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else {
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  // set motor speed
  analogWrite(enB, abs(newSpeed));
}


#include <ArduinoMotorShieldR3.h>
#include <VirtualWire.h>
//#include <ServoTimer2.h>

// servo
//ServoTimer2 servo;

// motors
ArduinoMotorShieldR3 motorShield;

// leds
int ledPin = 4;

// receiver
int rxPin = 5;
int rxTurretPotData = 0;
int rxMotorAJoyData = 0;
int rxMotorBJoyData = 0;

void setup() {
  // setup motor shield
  motorShield.init();

  // setup servo
  //servo.attach(2);
  //servo.write(1500);

  // setup leds
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  // setup receiver
  vw_set_rx_pin(rxPin);
  vw_setup(4000);
  vw_rx_start();
  
  Serial.begin(9600);
}

void loop() {
  // receiver
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // use data
  if (vw_have_message()) {
    vw_get_message(buf, &buflen);
    rxTurretPotData = atoi(strtok((char *) buf, ", "));
    rxMotorAJoyData = atoi(strtok(NULL, ", "));
    rxMotorBJoyData = atoi(strtok(NULL, ", "));
    
    //servo.write(rxTurretPotData);
    aRun(rxMotorAJoyData);
    bRun(rxMotorBJoyData);
    Serial.print(rxMotorAJoyData);
    Serial.print(" - ");
    Serial.print(rxMotorBJoyData);
    Serial.println();
  } else {
    //servo.write(1500);
    //aBrake();
    //bBrake();
  }
}

// motor functions
void aRun(int speed) {
  motorShield.setM1Speed(speed);
}

void bRun(int speed) {
  motorShield.setM2Speed(-speed);
}

#include <VirtualWire.h>

// potentiometers
//int turretPotPin = A0;
int turretPotData = 0;

int motorAJoyPin = A2;
int motorAJoyData = 0;
int motorBJoyPin = A1;
int motorBJoyData = 0;

char dataArray[20];

// transmitter
int txPin = 2;

void setup() {
  // setup transmitter
  vw_set_tx_pin(txPin);
  vw_setup(4000);
  
  Serial.begin(9600);
}

void loop() {
  // read potentiometers
  //turretPotData = (int) ((double) analogRead(turretPotPin) * (1000.0/1023.0)) + 1000;
  motorAJoyData = mapMotorJoyData(analogRead(motorAJoyPin));
  motorBJoyData = mapMotorJoyData(analogRead(motorBJoyPin));
  
  sprintf(dataArray, "%d, %d, %d.", turretPotData, motorAJoyData, motorBJoyData);
  Serial.println(motorBJoyData);

  // send data
  vw_send((uint8_t *) dataArray, sizeof(dataArray));
  vw_wait_tx();
}

int mapMotorJoyData(int data) {
  // shifts potentiometer values to values motor shield can use -200 to 200
  if (data <= 480) {
    return ((int) ((double) data * (200.0/480.0))) - 200;
  } else if (data > 544) {
    return (int) ((double) (data - 543) * (200.0/480.0));
  } else {
    return 0;  
  }
}

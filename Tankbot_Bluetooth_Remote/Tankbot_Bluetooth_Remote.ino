0000// potentiometers
int turretPotPin = A0;
int turretPotData = 0;

int motorAJoyPin = A2;
int motorAJoyData = 0;
int motorBJoyPin = A1;
int motorBJoyData = 0;

char data[20];

void setup() {
  // setup bluetooth
  Serial.begin(9600);
}
 
 
void loop() {
  // read potentiometers and joysticks
  turretPotData = map(analogRead(turretPotPin), 0, 1023, 0, 180);
  motorAJoyData = mapMotorJoyData(analogRead(motorAJoyPin));
  motorBJoyData = mapMotorJoyData(analogRead(motorBJoyPin));

  //sprintf(data, "%d, %d, %d.", turretPotData, motorAJoyData, motorBJoyData);
  //Serial.write(data, sizeof(data));
  Serial.print(String(turretPotData) + "t," + String(motorAJoyData) + "a," + String(motorBJoyData) + "b,");
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

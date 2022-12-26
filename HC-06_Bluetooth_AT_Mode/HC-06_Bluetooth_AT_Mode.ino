// Basic Bluetooth sketch HC-05_AT_MODE_02b
// Connect the HC-05 module and communicate using the serial monitor
// Arduino automates entering AT mode
//
// The default baud rate for AT mode when pin 34 is HIGH on power on is 38400
// See www.martyncurrey.com for details
//
//
//  Pins
//  Arduino D2 to HC-05 TX
//  Arduino D3 to HC-05 RX via a voltage divider
//  Arduino D4 to HX-05 pin 34 via a voltage divider
//  Arduino D5 to PNP Base via a 2.2k resistor
//  BT VCC to PNP Collector
//  BT GND to GND
//  PNP Emitter to vcc
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the Bluetooth module and display the result.
//
 
const byte BT_POWERPIN = 5;
const byte BT_PIN34_PIN = 4;
 
const boolean ON = LOW;
const boolean OFF = HIGH;
 
boolean BT_POWER = HIGH;  
boolean PIN34_STATE = LOW;
 
boolean NL = true;
char c = ' ';
 
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
 
void setup() 
{
    pinMode(BT_POWERPIN, OUTPUT);
    pinMode(BT_PIN34_PIN, OUTPUT);
 
 
    digitalWrite(BT_POWERPIN, OFF);  
    digitalWrite(BT_PIN34_PIN, LOW);
 
 
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
 
    Serial.println("Arduino Started");
    Serial.println("Basic Bluetooth sketch HC-05_AT_MODE_02b");
 
 
    Serial.println("Serial started at 9600");
    Serial.println(" ");
 
    // Start the software serial - baud rate for AT mode is 38400 
    BTserial.begin(38400);  
    Serial.println("BTserial started at 38400");
    Serial.println(" ");
 
    Serial.println("Enter # to toggle pin34 HIGH/LOW.");
    Serial.println("Enter * to toggle power to the HC-05");
    Serial.println("Remember to bring pin 34 HIGH before powering the HC-05");
    Serial.println("Set Both NL & CR in the serial monitor.");
    Serial.println(" ");    
    Serial.println("Pin 34 is LOW");
    Serial.println("Power is OFF");
    Serial.println(" ");
 
}
 
 
 
void loop()
{
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
          c =  Serial.read();
 
          // Echo the user input to the main window. The ">" character indicates the user entered text.
          if (NL) { Serial.print(">");  NL = false; }
          Serial.write(c);
          if (c==10) { NL = true; }        
 
 
          if (c=='*')
          {    
                 Serial.println(""); Serial.print("BT power is ");
                 if (BT_POWER == ON)         { BT_POWER = OFF;  digitalWrite(BT_POWERPIN, OFF);   Serial.println("OFF");    }   
                 else if  (BT_POWER == OFF)  { BT_POWER = ON;   digitalWrite(BT_POWERPIN, ON);    Serial.println("ON");   }     
 
                 if (  (PIN34_STATE == HIGH) && (BT_POWER == ON)  ) { Serial.println("AT mode");  }  
          }
 
          else if (c=='#') 
          {  
                 Serial.println(""); Serial.print("BT pin 34 is ");
                 if (PIN34_STATE == LOW)           { PIN34_STATE = HIGH;  digitalWrite(BT_PIN34_PIN, HIGH);  Serial.println("HIGH");   }   
                 else  if (PIN34_STATE == HIGH)    { PIN34_STATE = LOW;   digitalWrite(BT_PIN34_PIN, LOW);   Serial.println("LOW");    }  
          }
 
          else { BTserial.write(c);  }
 
    }
 
 
 
 
  // Keep reading from the HC-05 and send to the Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
 
}

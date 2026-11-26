#include <SoftwareSerial.h>

int PLOAD_PIN        = 8;  // Connects to Parallel load pin the 165
int SS_PIN  = 9;  // Connects to Clock Enable pin the 165
int MISO_PIN         = 11; // Connects to the Q7 pin the 165
int SCK_PIN        = 12; // Connects to the Clock pin the 165

#define PULSE_WIDTH_USEC 5

// Attach the serial display's RX line to digital pin 2
SoftwareSerial mySerial(3,2); // pin 2 = TX, pin 3 = RX (unused)
  
void setup() {
  //Serial.begin(115200);
  mySerial.begin(9600);
  delay(1000);

  mySerial.write(0x7C); // Command
  mySerial.write(0x9D); // Turn backlight completely on
  
  pinMode(PLOAD_PIN, OUTPUT);
  digitalWrite(PLOAD_PIN, HIGH);
  pinMode(SS_PIN, OUTPUT);
  digitalWrite(SS_PIN, HIGH);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);

}

void loop() {
  
  /*
  byte sensorValue = readSensors();
  delay(1000);

  //Serial.println(incoming);
  String sensorLineValues = String(sensorValue, BIN);
  int strLength = sensorLineValues.length();
  String padString = String("");
  for (int i=8-strLength;i>0;i--) {
    padString+="0";
  }
  String resultString = String(padString+sensorLineValues);
  //Serial.println(resultString);
  //char buffer[9];
  //resultString.toCharArray(buffer,8);
*/
  delay(1000);
  //mySerial.write(254); // control character
  //mySerial.write(1); // clear display
  mySerial.write(254); // move cursor to beginning of first line
  mySerial.write(128);

  mySerial.write("                "); // clear display
  mySerial.write("                ");
  mySerial.write("hello");
  delay(2000);
} 

byte readSensors() {
  // Load the register
  digitalWrite(PLOAD_PIN,LOW);
  delayMicroseconds(5);
  digitalWrite(PLOAD_PIN,HIGH);
  delayMicroseconds(5);
 
  // Shift in the data

  // data is clocked on rising edge so I thought the following digitalWrite should be LOW
  // to start according to the Arduino ShiftIn documentation. If it's HIGH, the resulting
  // byte value is off by one (LSB is missing).
  digitalWrite(SCK_PIN,HIGH); 
  digitalWrite(SS_PIN,LOW);
  byte incoming=shiftIn(MISO_PIN,SCK_PIN,LSBFIRST);
  digitalWrite(SS_PIN,HIGH);
  return incoming;
}


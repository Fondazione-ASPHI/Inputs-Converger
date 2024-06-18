#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

// Set up a new SoftwareSerial object
SoftwareSerial swSerial (rxPin, txPin);

char receivedChar;
char swReceivedChar;
boolean newData = false;
boolean swNewData = false;


void setup() {
  // put your setup code here, to run once:
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  swSerial.begin(9600);
  Serial.begin(9600);
}

void loop() {


  recvOneChar();
  swRecvOneChar();

  showNewData();
  swShowNewData();

  swSerial.flush();
  Serial.flush();
}


void recvOneChar() {
    if (Serial.available() > 0) {
      receivedChar = Serial.read();
      newData = true;
    }
}

void swRecvOneChar() {
    if (swSerial.available() > 0) {
      swReceivedChar = swSerial.read();
      swNewData = true;
    }
}

void showNewData() {
  if (newData == true) {
    Serial.write(receivedChar);
    swSerial.write(receivedChar);
    newData = false;
  }
}

void swShowNewData() {
  if (swNewData == true) {
    Serial.write(swReceivedChar);
    swNewData = false;
  }
}


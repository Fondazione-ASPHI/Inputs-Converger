#include <SoftwareSerial.h>
#include <XInput.h>

#define rxPin 10
#define txPin 11
#define LED_PIN 12

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);


void setup() {
  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);


  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  XInput.begin();
}


void loop() {
  if (mySerial.available() > 0) {
    String str = mySerial.readString();
    str.trim();
    digitalWrite(LED_PIN, HIGH);
    XInput.press(BUTTON_A);
    mySerial.println("ciao\n");
  }
}
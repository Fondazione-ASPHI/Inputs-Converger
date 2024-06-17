#include <SoftwareSerial.h>
#include <XInput.h>

#define rxPin 10
#define txPin 11

#define CMD_SIZE 6

// Set up a new SoftwareSerial object
SoftwareSerial mySerial (rxPin, txPin);
String str = "";

// Button Setup
const int NumButtons = 10;
const int Buttons[NumButtons] = {
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LB,
	BUTTON_RB,
	BUTTON_BACK,
	BUTTON_START,
	BUTTON_L3,
	BUTTON_R3,
};

// Triggers
const int TriggerMax = 255;  // uint8_t max
unsigned long triggerTimeLast = 0;
uint8_t triggerVal = 0;
boolean triggerDirection = 0;

// Joystick Setup
const int JoyMax = 32767;  // int16_t max
double angle = 0.0;

String commands[CMD_SIZE];


String readData(String data, char separator)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for (int j=0; j<CMD_SIZE; j++){
    for(int i=0; i<=maxIndex; i++){
      if(data.charAt(i)==separator || i==maxIndex){
          found++;
          strIndex[0] = strIndex[1]+1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
    }
    commands[j] = data.substring(strIndex[0], strIndex[1]);// : "";
  }
}


void setup() {  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

	XInput.setAutoSend(false);  // Wait for all controls before sending
	XInput.begin();
}


void loop() {
  if (mySerial.available() > 0) {
    str = mySerial.readString();
    str.trim();
    digitalWrite(LED_BUILTIN, HIGH);

    if (str == "test"){
      XInput.press(BUTTON_A);      
      XInput.send();
      delay(1000);
      XInput.release(BUTTON_A);	    
      XInput.send();
      delay(1000);
    }

    // FILL UP COMMANDS ARRAY
    readData(str, ",");

    // DPad
    //XInput.setDpad(dpadPosition == 0, dpadPosition == 1, dpadPosition == 2, dpadPosition == 3);

    // Buttons
    if (commands[0] == "true") {
      XInput.press(BUTTON_A);
    }
    else{
      XInput.release(BUTTON_A);
    }

    // Triggers
    //XInput.setTrigger(TRIGGER_LEFT, 0);
    //XInput.setTrigger(TRIGGER_RIGHT, 0);

    //XInput.setJoystick(JOY_LEFT, 0, 0);
    //XInput.setJoystick(JOY_RIGHT, 0, 0);


    // Send values
    XInput.send();

    //mySerial.println("done");
  }

}
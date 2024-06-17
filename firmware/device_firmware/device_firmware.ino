#include <SoftwareSerial.h>
#include <XInput.h>

#define rxPin 10
#define txPin 11

#define CMD_SIZE 6

// Set up a new SoftwareSerial object
SoftwareSerial swSerial (rxPin, txPin);

// String commands[CMD_SIZE];


// String readData(String data, char separator)
// {
//   int found = 0;
//   int strIndex[] = {0, -1};
//   int maxIndex = data.length();

//   for (int j=0; j<CMD_SIZE; j++){
//     for(int i=0; i<maxIndex; i++){
//       if(data.charAt(i)==separator || i==maxIndex){
//           found++;
//           strIndex[0] = strIndex[1]+1;
//           strIndex[1] = (i == maxIndex) ? i+1 : i;
//       }
//     }
//     commands[j] = data.substring(strIndex[0], strIndex[1]);// : "";
//   }
// }

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;


void setup() {  
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  swSerial.begin(9600);
  swSerial.println("<Device is ready>");

	XInput.setAutoSend(false);  // Wait for all controls before sending
	XInput.begin();
}


void loop() {


  recvWithStartEndMarkers();
  showNewData();



  // if (mySerial.available() > 0) {
  //   String str = mySerial.readString();
  //   str.trim();
  //   mySerial.println(str);

  //   if (str == "hello") {
  //     digitalWrite(LED_BUILTIN, HIGH);
  //   }

  //   if (str ==  "test") {
  //     XInput.press(BUTTON_A);      
  //     XInput.send();
  //     delay(500);
  //     XInput.release(BUTTON_A);	    
  //     XInput.send();
  //   }

    // FILL UP COMMANDS ARRAY
    //readData(str, ",");

    // DPad
    //XInput.setDpad(dpadPosition == 0, dpadPosition == 1, dpadPosition == 2, dpadPosition == 3);

    // Buttons
    // if (commands[0] == "true") {
    //   XInput.press(BUTTON_A);
    // }
    // else{
    //   XInput.release(BUTTON_A);
    // }

    // Triggers
    //XInput.setTrigger(TRIGGER_LEFT, 0);
    //XInput.setTrigger(TRIGGER_RIGHT, 0);

    //XInput.setJoystick(JOY_LEFT, 0, 0);
    //XInput.setJoystick(JOY_RIGHT, 0, 0);


    // Send values
    //XInput.send();

    //mySerial.println("done");

}



void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (swSerial.available() > 0 && newData == false) {
        rc = swSerial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
  if (newData == true) {
    swSerial.println(receivedChars);
      
    XInput.press(BUTTON_A);      
    XInput.send();
    delay(500);
    XInput.release(BUTTON_A);	    
    XInput.send();
      
    newData = false;
  }
}
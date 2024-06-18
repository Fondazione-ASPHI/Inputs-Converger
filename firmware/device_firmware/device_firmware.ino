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
  swSerial.write("<Device is ready>");

	XInput.setAutoSend(false);  // Wait for all controls before sending
	XInput.begin();

  // First input to awake console
  XInput.press(BUTTON_A);
  delay(500);
  XInput.release(BUTTON_A);
  delay(500);
  XInput.send();
}


void loop() {


  receiveData();
  processData();

  //XInput.setJoystick(JOY_LEFT, 32767, 0);
  XInput.send();

  swSerial.flush();
}



void receiveData() {
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

void processData() {
  if (newData == true) {
    swSerial.write(receivedChars);

    //int x =receivedChars - '0';
    XInput.setJoystick(JOY_LEFT, 32767, 0);

    digitalWrite(LED_BUILTIN, HIGH);
      
    newData = false;
  }
}
#include <XInput.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
	XInput.begin();
}

void loop() {
	XInput.press(BUTTON_A);
	delay(1000);

	XInput.release(BUTTON_A);
	delay(1000);
}
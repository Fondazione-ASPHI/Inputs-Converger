#include <XInput.h>

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
	XInput.begin();
}

void loop() {
  XInput.setJoystick(JOY_LEFT, 32767, 0);
	// XInput.press(BUTTON_A);
	// delay(1000);

	// XInput.release(BUTTON_A);
	// delay(1000);
}
import time
import serial
import keyboard

ser = serial.Serial("COM11", 9600)
print("opened")



class Gamepad():
    def __init__(self, port):
        super().__init__()
        self.port = port
        self.reset_state()
        self.update()

    def reset_state(self):
        self.state = {
            "A": False,
            "B": False,
            "LeftTrigger": 0,
            "RightTrigger": 0,
            "LeftAnalog": (0, 0),
            "RightAnalog": (0, 0)
        }

    def press_button(self, button):
        self.state[button] = True

    def release_button(self, button):
        self.state[button] = False

    def left_trigger(self, value): # value is between 0 and 1
        self.state["LeftTrigger"] = value

    def right_trigger(self, value): # value is between 0 and 1
        self.state["RightTrigger"] = value

    def left_joystick(self, x_value, y_value):
        self.state["LeftAnalog"] = (x_value, y_value)

    def right_joystick(self, x_value, y_value):
        self.state["RightAnalog"] = (x_value, y_value)

    def update(self):
        pass

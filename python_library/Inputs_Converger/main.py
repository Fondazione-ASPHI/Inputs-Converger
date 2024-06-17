import serial


class Gamepad():
    def __init__(self, port, baud=9600):
        super().__init__()
        self.serial = serial.Serial(port, baud)
        self.serial.write(b"hello")
        print("Opened serial on port {port}, baud {baud}")
        self.reset_state()
        self.update()

    def reset_state(self):
        self.state = {
            "A": "0",
            "B": "0",
            "LeftTrigger": "0",
            "RightTrigger": "0",
            "LeftAnalog": "0-0",
            "RightAnalog": "0-0"
        }
    
    def state_output(self):
        so = (self.state["A"] + "," +
                self.state["B"] + "," +
                self.state["LeftTrigger"] + "," +
                self.state["RightTrigger"] + "," +
                self.state["LeftAnalog"] + "," +
                self.state["RightAnalog"]).encode('ASCII')
        print(so)
        return so

    def press_button(self, button):
        self.state[button] = "true"

    def release_button(self, button):
        self.state[button] = "false"

    def left_trigger(self, value): # value is between 0 and 1
        self.state["LeftTrigger"] = str(value)

    def right_trigger(self, value): # value is between 0 and 1
        self.state["RightTrigger"] = str(value)

    def left_joystick(self, x_value, y_value):
        self.state["LeftAnalog"] = str(x_value) + "-" + str(y_value)

    def right_joystick(self, x_value, y_value):
        self.state["RightAnalog"] = str(x_value) + "-" + str(y_value)

    def update(self):
        self.serial.write(self.state_output())

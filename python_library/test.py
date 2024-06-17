import Inputs_Converger as ic
import time


gamepad = ic.Gamepad("COM11")

while True:
    gamepad.press_button("A")
    gamepad.update()
    time.sleep(1)
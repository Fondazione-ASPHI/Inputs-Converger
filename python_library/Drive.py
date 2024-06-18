import sys
options_file_name = sys.argv[1]

import json
from Nose_Tracker import track_face

# import Inputs_Converger as ic
# gamepad = ic.Gamepad("COM4")

import serial
ser = serial.Serial("COM4", 9600)
print("opened")


#################
# NOSE #
#################
def logic(nose_x, nose_y, mouth_x, head_tilt, trigger_eyebrows, trigger_mouth_open):
  # gamepad.left_joystick(-nose_x*255, nose_y*255)
  x = nose_x * 10
  if x > 9:
    x = 9
  # y = nose_y * 10
  # if y > 9:
  #   y = 9
  cmd = "<" + str(x) + ">"
  ser.write(cmd.encode('ASCII'))


  # if nose_y > 0:

  # elif nose_y < 0:
 
  # gamepad.update()



#################
# IMPORT OPTIONS #
#################
options_file = open(options_file_name) # Opening JSON file
options = json.load(options_file) # returns JSON object as a dictionary
options_file.close() # Closing file


#################
# START TRACKING #
#################
track_face(logic, options)
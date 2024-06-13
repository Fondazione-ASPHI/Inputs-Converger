import time
# run this file on a unix-like server
import serial
# edit your /etc/bluetooth/rfcomm.conf file
bluetooth_device = 'COM11'

ser = serial.Serial(bluetooth_device, 9600)
print("opened")
ser.write(b"ciao")
print("sent string")
time.sleep(5)
# print("Reading")
# ser.readline()
print("closing")
ser.close()
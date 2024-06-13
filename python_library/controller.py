import time
import serial
import keyboard

ser = serial.Serial("COM11", 9600)
print("opened")

running = True
while running:    
    if keyboard.is_pressed("a"):
        print("A")
        ser.write(b"a")
        time.sleep(1)

    if keyboard.is_pressed("q"):
        running = False

print("closing")
ser.close()
quit()
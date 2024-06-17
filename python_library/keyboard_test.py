import time
import serial
import keyboard

ser = serial.Serial("COM4", 9600)
print("opened")


# ser.write(b"test")
# time.sleep(3)
# print(ser.read())
# time.sleep(5)

running = True
while running:    
    if keyboard.is_pressed("a"):
        print("A")
        ser.write(b"test")
        time.sleep(1)
        #ser.flushInput()

    if keyboard.is_pressed("q"):
        running = False

    

print("closing")
ser.close()
quit()
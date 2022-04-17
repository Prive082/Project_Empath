import serial
import time

arduino = serial.Serial
ser = serial.Serial("COM5", 9800, timeout=1)
i = 0
while i < 1000:
    fromarduino = ser.readline()
    decoded = fromarduino.decode('UTF-8')
    print(decoded)
    if decoded == "brian\r\n":
        print("FUCK YU")
        time.sleep(1)
    time.sleep(0.1)
ser.write()
ser.close()
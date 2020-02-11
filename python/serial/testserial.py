import time
import serial

ser = serial.Serial(port='COM4', baudrate=115200)

data = ''

while True:
    data = ser.readline()
    data = data.decode()[:len(data)-2]
    print(data)

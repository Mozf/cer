import time
import serial

ser = serial.Serial(port='COM4', baudrate=115200)

data = ''
datafromuart = 'ggg'
print(data)
print(datafromuart)

while True:
    data = ser.readline()
    t = time.time()
    ct = time.ctime(t)
    print(ct, ':')
    print(data)
    data = data.decode()
    data1 = data[0:3]
    print(data1)

    if (data[0:3] == datafromuart):
         print(1)
         ser.write('g\r\n'.encode())
         print("send successful!")

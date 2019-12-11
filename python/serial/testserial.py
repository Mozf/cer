import time
import serial

ser = serial.Serial(
    port='COM4',
     baudrate=115200
)

data = ''
datafromuart = '1111'

while True:
    data = ser.readline()
    t = time.time()
    ct = time.ctime(t)
    print(ct, ':')
    print(data)

    while (data == datafromuart):
      ser.write('g\r\n'.encode())
      print("send success!")

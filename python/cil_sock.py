import socket
import sys
import serial

ser = serial.Serial(port='COM4', baudrate=115200)
data = ''

while True:

  data = ser.readline()
  data = data.decode()[:len(data)-2]
  print(data, flush = True)
  s = socket.socket(socket.AF_INET6,socket.SOCK_STREAM)

  host = "2001:da8:270:2018:f816:3eff:fe40:d788"

  port = 5670
  s.connect((host,port))
  s.send(data.encode("utf-8"))

  msg = s.recv(1024)

  s.close()

  print(msg.decode("utf-8"))


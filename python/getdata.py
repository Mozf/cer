import socket
import sys
import random
from time import ctime
from model import app
import time
import os

ServerSocket = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
print("Done.....1")

host = "2001:da8:270:2018:f816:3eff:fe40:d788"
print('my host : {}'.format(host))

port = 8088

ServerSocket.bind((host, port))#2001:da8:270:2018:f816:3eff:fe40:d788

ServerSocket.listen(1)


while True:
  clientsocket, addr = ServerSocket.accept()
  # print("addr is :%s" % str(addr))

  name = clientsocket.recv(1024)
  file = open(r'data.txt', 'w')
  if name.decode("utf-8").isdigit():
    file.write(name.decode("utf-8") + '\n')
    print(name)

  clientsocket.close()
  print(1)
  
ServerSocket.close()
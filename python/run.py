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

port = 5670

ServerSocket.bind((host, port))#2001:da8:270:2018:f816:3eff:fe40:d788

ServerSocket.listen(1)
msg = 'awaite'
flag = 0

while True:
  clientsocket, addr = ServerSocket.accept()
  # print("addr is :%s" % str(addr))

  name = clientsocket.recv(1024)

  #send back============================================================================================================

  if name.decode("utf-8") == 'get\n':
    if flag == 0:
      clientsocket.send(msg.encode())
    else:
      app()
      clientsocket.send(msg)
      print('the odour is '+ msg.decode()[1:])
    print('Send successfully')

  elif name.decode("utf-8") == 'get':
    if flag == 0:
      clientsocket.send(msg.encode())
    else:
      file = open(r"data.txt", "r")
      data1 = file.readlines()
      for i in range(60):
        time.sleep(1)
        
        print(data1[i*8 : i*8+8])
        print('getting the data...', i)
      app()
      clientsocket.send(msg)
      print('the odour is '+ msg.decode()[1:])
    print('Send successfully')
    flag = 0
    msg = 'awaite'

  else:
    clientsocket.send(name)
    flag = 1
    msg = name

  clientsocket.close()
  
ServerSocket.close()

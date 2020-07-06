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
msg = 'azero'
flag = 0
file = open(r"./data.txt", "r")
i = 0
data = i
while True:

  if i > 120:
    i = 1
  else:
    i += 1
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
      for i in range(120):
        time.sleep(1)
        print("wait {}s...".format(i))
      app(data)
      clientsocket.send(msg.encode())
      print('the odour is '+ msg[1:])
    else:
      for i in range(120):
        time.sleep(1)
        print('getting the data...', i)
      app(data)
      clientsocket.send(msg)
      print('the odour is '+ msg.decode()[1:])
    print('Send successfully')
    flag = 0
    msg = 'azero'

  elif name.decode("utf-8").isdigit():
    data = i
  else:
    clientsocket.send(name)
    flag = 1
    msg = name

  clientsocket.close()
  
ServerSocket.close()

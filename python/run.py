import socket
import sys
import random
from time import ctime
from model import app
import time

ServerSocket = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
ServerSocket1 = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
print("Done.....1")

host = "2001:da8:270:2018:f816:3eff:fe40:d788"
print('my host : {}'.format(host))

port = 5670
port1 = 8088

ServerSocket.bind((host, port))#2001:da8:270:2018:f816:3eff:fe40:d788
ServerSocket1.bind((host, port1))

ServerSocket.listen(1)
ServerSocket1.listen(1)
msg = 'awaite'
flag = 0

while True:
  clientsocket, addr = ServerSocket.accept()
  # print("addr is :%s" % str(addr))
  clientsocket1, addr1 = ServerSocket1.accept()

  name = clientsocket.recv(1024)
  data = clientsocket1.recv(1024)

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
      for i in range(60):
        time.sleep(1)
        print('getting the data...', i)
      app()
      clientsocket.send(msg)
      print('the odour is '+ msg.decode()[1:])
    print('Send successfully')
    flag = 0
    msg = 'awaite'

  elif name.decode("utf-8").isdigit():
    pass

  else:
    clientsocket.send(name)
    flag = 1
    msg = name

  clientsocket.close()

  if data.decode("utf-8").isdigit():
    print(data)
  
ServerSocket.close()

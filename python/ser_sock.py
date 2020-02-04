import socket
import sys
import random
from time import ctime

def app():
  print('input data...')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv2d_1...')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  print('activation function_1...') 

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = random.randint(0,100)
    if(f > g):
      k = f
    else:
      k = g
    if(f > h):
      k = f
    else:
      k = h
    if(g > h):
      k = g
    else:
      k = h

  print('pool_1...')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv2d_2...')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  print('activation function_2...') 

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = random.randint(0,100)
    if(f > g):
      k = f
    else:
      k = g
    if(f > h):
      k = f
    else:
      k = h
    if(g > h):
      k = g
    else:
      k = h

  print('pool_2...')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv2d_3...')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  print('activation function_3...') 

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = random.randint(0,100)
    if(f > g):
      k = f
    else:
      k = g
    if(f > h):
      k = f
    else:
      k = h
    if(g > h):
      k = g
    else:
      k = h

  print('pool_3...')

  for i in range(118):
    a = random.randint(1,100)
    b = random.randint(1,100)
    for j in range(9):
      c = a*b
      d = a+b

  print('conv2d_4...')
      
  for i in range(118*9):
    e = random.randint(-100,100)
    if(e < 0):
      e = 0

  print('activation function_4...') 

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = random.randint(0,100)
    if(f > g):
      k = f
    else:
      k = g
    if(f > h):
      k = f
    else:
      k = h
    if(g > h):
      k = g
    else:
      k = h

  print('pool_4...')

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = f*g
    r = f+g+h
    for i in range(118*9):
      w = random.randint(0,100)
      w = r * w

  print('linear_1...')

  for i in range(118*9):
    f = random.randint(0,100)
    g = random.randint(1,100)
    h = f*g
    r = f+g+h
    for i in range(10):
      w = random.randint(0,100)
      w = r * w

  print('linear_2...')

ServerSocket = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
print("Done.....1")

host = "2001:da8:270:2018:f816:3eff:fe40:d788"
print('my host : {}'.format(host))

port = 5670

ServerSocket.bind((host, port))#2001:da8:270:2018:f816:3eff:fe40:d788

ServerSocket.listen(1)
msg = 'running'
flag = 0

while True:
  clientsocket, addr = ServerSocket.accept()
  # print("addr is :%s" % str(addr))

  name = clientsocket.recv(1024)

  #send back============================================================================================================

  if name.decode("utf-8") == 'get\n':
    app()
    if flag == 0:
      clientsocket.send(msg)
      print(msg.decode())
    else:
      clientsocket.send(msg)
      print('the odour is '+ msg)
    print('yes')
  elif name.decode("utf-8") == 'get':
    app()
    if flag == 0:
      clientsocket.send(msg)
      print(msg.decode())
    else:
      clientsocket.send(msg)
      print('the odour is '+ msg)
    print('yes')
  else:
    clientsocket.send(name)
    print('no')
    flag = 1
    msg = name

  print('Send successfully')

  clientsocket.close()
  
ServerSocket.close()

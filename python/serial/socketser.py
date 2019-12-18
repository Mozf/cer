import socket
import sys
from time import ctime

ServerSocket = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
print("Done.....1")

host = "2001:da8:270:2018:f816:3eff:fe40:d788"
print('my host : {}'.format(host))

port = 5670

ServerSocket.bind((host, port))#2001:da8:270:2018:f816:3eff:fe40:d788

ServerSocket.listen(1)

while True:
  clientsocket, addr = ServerSocket.accept()
  print("addr is :%s" % str(addr))
  msg = "welcomt to my demo"
  clientsocket.send(msg.encode("utf-8"))
  data = clientsocket.recv(1024)
  data1 = ('[%s] %s' % (ctime(),data.decode())).encode("utf-8")
  clientsocket.send(data1)
  clientsocket.close()
  
ServerSocket.close()

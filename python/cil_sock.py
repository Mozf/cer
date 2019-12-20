import socket
import sys

s = socket.socket(socket.AF_INET6,socket.SOCK_STREAM)

host = "2001:da8:270:2018:f816:3eff:fe40:d788"

port = 5670

s.connect((host,port))

msg = s.recv(1024)
msg2 = "apple"
s.send(msg2.encode("utf-8"))
msg3 = s.recv(1024)

s.close()

print(msg.decode("utf-8"))
print(msg3.decode("utf-8"))

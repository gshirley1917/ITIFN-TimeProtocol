import socket
import datetime, time

mysocket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mysocket.connect(("127.0.0.1", 37))
data = mysocket.recv(2048)
data= int.from_bytes(data, byteorder="big")

print (data)

mysocket.send(b"Connected to the client")
mysocket.close()

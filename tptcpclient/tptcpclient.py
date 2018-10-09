import socket
mysocket=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mysocket.connect(("127.0.0.1", 37))
data = mysocket.recv(2048)

print (data)
mysocket.send(b"Connected to the client")
mysocket.close()

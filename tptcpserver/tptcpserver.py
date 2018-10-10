import socket
import datetime, time

dts = datetime.datetime.utcnow()
epochtime1 = round(time.mktime(dts.timetuple()) + dts.microsecond/1e6)
epochtime= epochtime1 + 2208988800

print("Server started")
print("Listening")

mysocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mysocket.bind(("127.0.0.1", 37))
mysocket.listen(5)
(client, (ip,port))=mysocket.accept() 
time=(epochtime).to_bytes(4, byteorder='big')

client.send(time)
data = client.recv(2048)
print (data)
mysocket.close()


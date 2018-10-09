import socket
import datetime, time
import struct

dts = datetime.datetime.utcnow()
epochtime = round(time.mktime(dts.timetuple()) + dts.microsecond/1e6)


mysocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
mysocket.bind(("127.0.0.1", 37))
mysocket.listen(5)
(client, (ip,port))=mysocket.accept()
thetimenow = time.time()
ba = bytearray(struct.pack("f", thetimenow))  

print(thetimenow)
#print ("To Local Time: ", time.ctime(thetimenow))

client.send(ba)
data = client.recv(2048)
print (data)
mysocket.close()

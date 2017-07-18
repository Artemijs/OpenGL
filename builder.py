''' socket server using threads? '''

import socket
import sys
from thread import *
HOST =""
PORT = 8889
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print "Socket Created"

#bind socket

try:
    s.bind((HOST, PORT))
except socket.error as msg:
    print "Bind failed, error code "+str(msg[0])+" message "+msg[1]
    sys.exit()
print "Bind Complete"

#start listening on socket
s.listen(10)
print "Socket now listening"

#keep talking to client
while 1:
    #wait to accept a connection - blocking call
    conn, addr = s.accept()
    print "Connected with "+addr[0]+" : "+str(addr[1])
    data = conn.recv(1024)
    if not data:
        break
    print data
    reply = "got it"
    conn.sendall(reply)
    conn.close()
s.close()


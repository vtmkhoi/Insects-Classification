import socket
import requests

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostbyname(socket.gethostname()), 2555))
s.listen(5)

while True:
    clientsocket, address = s.accept()
    print(f"Connection from {address} has been established")
    data = clientsocket.recv(1024)
    print(data)
    clientsocket.send(bytes("Welcome from server", "utf-8"))  #Send data to client

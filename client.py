import socket

HOST = '192.168.0.195'    # Cấu hình address server
PORT = 1999                    # Cấu hình Port sử dụng

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Cấu hình socket
s.connect((HOST, PORT)) # tiến hành kết nối đến server
s.sendall(b'From Client: Hello server!') # Gửi dữ liệu lên server 
data = s.recv(8000) # Đọc dữ liệu server trả về
print('Server Respone: ', repr(data))

 
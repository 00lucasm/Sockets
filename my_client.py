import socket

server_addr = '127.0.0.1'
server_port = 8080

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((server_addr, server_port))

# request feita no CLIENT para ser enviada ao SERVER
request = b'GET / HTTP/1.1'

# ENVIO da request através do SOCKET
client_socket.send(request)

# recebendo RESPONSE do SERVIDOR
response = client_socket.recv(1024)

# apenas mostra o que o SERVER enviou como response
print('From Server:', response)

# fechamento da conexão
client_socket.close()
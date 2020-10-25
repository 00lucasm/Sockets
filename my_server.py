# lib que manipula socket e conexões
import socket

# criação do socket para o lado do SERVIDOR
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# definição do endereço IP do SERVIDOR
server_address = '127.0.0.1'

# definição da PORTA em que o SERVIDOR vai conectar o SOCKET
server_port = 8080

# BIND (ou ligação/conexão) sendo estabelecida no endereço do SERVIDOR e na sua PORTA
server_socket.bind((server_address, server_port))

# SERVIDOR na escuta
server_socket.listen()


# parte principal principal da comunicação entre CLIENT e SERVER (linhas 20 até 30 do código)

connection, addr = server_socket.accept() # aceitando conexão do CLIENT
request = connection.recv(1024) # recebendo a requisição vinda do CLIENT

if request == b'GET / HTTP/1.1': # se REQUEST for um GET
	connection.sendall(b'200 OK') # então a response é um 200 OK
else:
	connection.sendall(b'404 not found!') # ELSE: a response é um 404 not found

connection.close() # FECHAMENTO DA CONEXÃO
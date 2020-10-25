// server side
#include <sys/socket.h> // for socket functions
#include <netinet/in.h> // for sockaddr_in
#include <cstdlib> // for exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <errno.h> // dealing with errors

using namespace std;

#define PORT 8080
#define BLENGTH 2048

int main(){

	// cria um socket que recebe endereços IPv4 e conexão TCP
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd == 0){
		cout << "Failed to create a socket. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	// LISTEN na porta 8080 ou qualquer endereço especificado
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(PORT);

	// a função bind() atribui um endereço IP e a porta ao socket
	if(bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
		cout << "Failed to bind to port 8080. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	// começa o LISTENING. Mantém até 10 conexões na fila
	if(listen(sockfd, 10) < 0){
		cout << "Failed to listen on socket. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	// puxa uma conexão da fila
	int addrlen = sizeof(sockaddr);
	int connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if(connection < 0){
		cout << "Failed to grab connection. errno: " << errno << endl;
		exit(EXIT_FAILURE);
	}

	// leitura da conexão
	char buffer[BLENGTH];
	int stream = read(connection, buffer, BLENGTH);
	cout << "The message was: " << buffer << endl;

	if(buffer == "GET / HTTP/1.1"){
		string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length:12\n\nHello world!\n";
		send(connection, response.c_str(), response.size(), 0);
	}else{
		string response = "HTTP/1.1 404 not found\nContent-Type: text/plain\nContent-Length:12\n\n404 NOT_FOUND\n";
		send(connection, response.c_str(), response.size(), 0);
	}

	// fechando conexão
	close(connection);
	close(sockfd);
}
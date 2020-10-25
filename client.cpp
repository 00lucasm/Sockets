#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cstring>
#include <string>

using namespace std;

#define PORT 8080

int main(){
	int obj_socket = 0, reader;
	struct sockaddr_in serv_addr;
	string message = "GET / HTTP/1.1";
	char buffer[2048] = {0};

	if (( obj_socket = socket (AF_INET, SOCK_STREAM, 0 )) < 0){
		cout << "Socket creation error !" << endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Converting IPv4 and IPv6 addresses from text to binary form
	if(inet_pton ( AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
		cout << "\nInvalid address ! This IP Address is not supported" << endl;
		return -1;
	}

	if ( connect( obj_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		cout << "Connection Failed : Can't establish a connection over this socket !" << endl;
		return -1;
	}

	// my_socket, request.c_str(), request.size(), 0
	send(obj_socket, message.c_str(), message.size(), 0 );
	cout << "\nClient : Message has been sent !\n";
	reader = read(obj_socket, buffer, 2048);
	cout << buffer << endl;
	return 0;
}
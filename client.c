//Lisha Yao
// client.c to test server without hardware

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 4444

void error(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){

	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;
	char buffer[1024] = {0};
	char *test = "hello im from the client1 on mac";


	int sock = socket(AF_INET,SOCK_STREAM, 0);
	if(sock == -1){
		error("sock error");
	}
	memset(&server_addr, '0', sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	// need to add memset and convert IP addresses to binary
	
	if(inet_pton(AF_INET, "169.233.211.140", &server_addr.sin_addr) == -1) {
		printf("invalid addresses\n");
	}
	//connect
	int connecting = connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if(connecting == -1){
		error("cannot connect");
	}
	// send
	int sending = send(sock, test, strlen(test), 0);
	if(sending == -1){
		error("message could not send");
	}
	printf("sent message\n");
	//close
	int closing = close(sock);
	if(closing == -1){
		error("cannot close socket");
	}












}
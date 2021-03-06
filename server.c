// Lisha Yao
//server.c file


#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 4444
#define queueLimit 1

typedef struct sockaddr_in sock_addr;

void error(char *msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
	char buffer [1024] = {0};

	sock_addr server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; 
	server_addr.sin_port = htons(PORT); //port number shall be in network byte order
	
	sock_addr client_addr;
	int client_addr_len = sizeof(client_addr);
	
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1){
		error("socket not created");	
	}
	
	int binding = bind(sock, (struct sockaddr*) &server_addr, sizeof(sock_addr) );
	if(binding == -1){
		error("bind did not work");	
	}

	int listening = listen(sock, queueLimit);
	if(listening == -1){
		error("did not listen");	
	}
	int count = 0;
	for(;;){
		int client_new = -1;

		while(client_new == -1) {
			client_new = accept(sock, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len);
			if(client_new == -1 ){
				printf("waiting...\n");
			}
	
		}
		
		
		printf("accepted new client\n");
		
	
	

		int whattheysend = read(client_new,buffer,1024);
		printf("%s\n",buffer);
		int close_client = close(client_new);
		if (close_client == -1){
			printf("closing client error\n");
		}
	
		count += 1;
		if(count == 10){
			break;
		}
	}
	int closing = close(sock);
	if (closing == -1){
		error("cannot close socket");	
	}
}
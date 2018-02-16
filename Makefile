CC=gcc


all:
	$(CC) server.c -o server
	$(CC) client.c -o client

server:
	$(CC) server.c -o server

client:
	$(CC) client.c -o client

	
runc:
	./client

runs:
	./server

clean:
	rm server
	rm client
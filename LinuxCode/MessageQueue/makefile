.PHONY:all
all:Client Server

Client:Client.c Common.h
	gcc -o $@ $^ -lpthread
Server:Server.c Common.h
	gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f Client Server

.PHONY:all
all:server client pipe
server:server.c
	gcc -o $@ $^
client:client.c
	gcc -o $@ $^
pipe:pipe.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f server client myfifo pipe

.PHONY:all
all:test1 test2

test1:test.c
	gcc -o $@ $^ -g
test2:test2.c
	gcc -o $@ $^ -g -lpthread
.PHONY:clean
clean:
	rm -f test1 test2

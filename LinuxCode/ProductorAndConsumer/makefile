.PHONY:all
all:test1 test2
test2:test2.c
	gcc -o $@ $^ -lpthread
test1:test1.c LinkList.h
	gcc -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f test1 test2

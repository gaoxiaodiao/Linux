.PHONY:all
all:ArpSpoof Common

Common:Common.c
	gcc -o $@ $^ -g
ArpSpoof:ArpSpoof.c
	gcc -o $@ $^ -g
.PHONY:clean
clean:
	rm -f ArpSpoof Common

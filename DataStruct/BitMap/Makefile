BitMap:BitMap.o Test.o
	g++ BitMap.o Test.o -o BitMap
Test.o:Test.cpp
	g++ -c Test.cpp
BitMap.o:BitMap.h BitMap.cpp
	g++ -c BitMap.h BitMap.cpp


.PHONY:clean
clean:
	rm -f *.h.gch *.o BitMap

all: compaq

compaq: compaq.o huff.o heap.o
	g++ compaq.o huff.o heap.o -o main
	rm -f *.o 
compaq.o: huff.hpp heap.hpp
	g++ -c compaq.cpp
huff.o: huff.hpp heap.hpp
	g++ -c huff.cpp
heap.o: heap.hpp
	g++ -c heap.cpp

clear:
	rm -f compaq


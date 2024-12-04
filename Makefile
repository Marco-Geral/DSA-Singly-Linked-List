CXXFLAGS = -std=c++98
ZIP_FILE = u23584565.zip
SRC_FILES = $(wildcard *.cpp)

task1: main.o Node.o List.o SinglyLinked.o
	g++ $(CXXFLAGS) main.o Node.o List.o SinglyLinked.o -o task1

main.o: main.cpp Node.h List.h SinglyLinked.h
	g++ $(CXXFLAGS) -c main.cpp

Node.o: Node.cpp Node.h
	g++ $(CXXFLAGS) -c Node.cpp

List.o: List.cpp List.h 
	g++ $(CXXFLAGS) -c List.cpp

SinglyLinked.o: SinglyLinked.cpp SinglyLinked.h List.h
	g++ $(CXXFLAGS) -c SinglyLinked.cpp

main: main.o Node.o List.o SinglyLinked.o 
	g++ $(CXXFLAGS) main.o Node.o List.o SinglyLinked.o -o main

run: main
	./main

clean:
	rm -f *.o task1 main.exe

zip:
	zip -u $(ZIP_FILE) $(SRC_FILES) *.h Makefile

debugcpp: debugo
	g++ -ggdb3 -o main *.o

debugo: *.cpp
	g++ -ggdb3 -c -w *.cpp

v:
	make debugcpp
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=valg.txt ./main
	make clean



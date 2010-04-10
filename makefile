
all: CFC clean exec

CFC: main.o
	g++ -o TER main.o

main.o: main.cpp
	g++ -o main.o -c main.cpp

clean:
	rm -rf *.o

exec:
	./CFC
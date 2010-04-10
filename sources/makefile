
all: CFC clean exec

CFC: main.o
	g++ -o ../CFC main.o

main.o: main.cpp
	g++ -o main.o -c cpp/main.cpp

clean:
	rm -rf *.o

exec:
	./CFC
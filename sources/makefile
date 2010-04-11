#Compilateur utilisé
CC	?= g++

#Options du compilateur
CXXFLAGS	?= -ANSI

#Nom de l'executable
PROG	?= CFC

all: $(PROG) clean exec

$(PROG): main.o
	$(CC) $(CXXFLAGS) -o ../CFC main.o

main.o: ./cpp/main.cpp
	$(CC) $(CXXFLAGS) -c ./cpp/main.cpp

clean:
	rm -rf *.o

exec:
	../CFC
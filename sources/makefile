# Compilateur utilisé
CC	?= g++

# Options du compilateur
CXXFLAGS	?= -ANSI

# Nom de l'executable
PROG	= CFC

# Liste des fichiers objets nécessaures
OBJS	= main.o

all: $(PROG) clean exec

$(PROG): $(OBJS)
	$(CC) $(CXXFLAGS) -o ../$(PROG) $(OBJS)

.c.o:
	$(CC) $(CXXFLAGS) -c ./cpp/$*.cpp

clean:
	rm -rf *.o

exec:
	../CFC
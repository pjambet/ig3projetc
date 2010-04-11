# Compilateur utilisé
CXX	?= g++

# Options du compilateur
CXXFLAGS	?= -Wall -ANSI

# Reconnaître les Extension de nom de fichier *.cpp et *.o comme suffixe
SUFFIXES ?= .cpp .o 
.SUFFIXES: $(SUFFIXES) .

# Nom de l'executable
PROG	= CFC

# Liste des fichiers objets nécessaures
OBJS	= main.o

all: $(PROG) clean exec

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o ../$(PROG) $(OBJS)

main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) -c ./cpp/main.cpp

clean:
	rm -rf $(OBJS)

exec:
	../$(PROG)
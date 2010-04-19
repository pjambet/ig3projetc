# Compilateur utilisé
CXX	?= g++

# Options du compilateur
CXXFLAGS	?= -Wall -ansi

# Reconnaître les Extension de nom de fichier *.cpp et *.o comme suffixe
SUFFIXES ?= .cpp .o 
.SUFFIXES: $(SUFFIXES) .

# Nom de l'executable
PROG	= CFC

# Liste des fichiers objets nécessaures
OBJS	= main.o sommet.o matAdj.o lscAdj.o

all: $(PROG) clean exec

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o ../$(PROG) $(OBJS)

%.o : ./cpp/%.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(OBJS)

exec:
	../$(PROG)

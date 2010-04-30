# Compilateur utilise
CXX	?= g++
#
# Options du compilateur
CXXFLAGS	?= -Wall -ansi
#
# Definition du repertoire des headers
HDIR = -I $(CURDIR)/h
#
#$(PROG) clean exec$(PROG): $(OBJS)
	#$(CXX) $(CXXFLAGS) -o ../$(PROG) $(OBJS)
#
all: CFC
#
CFC: Generator.o UserData.o Graphe.o Person.o Friends.o sommet.o ListeVoisins.o matAdj.o struct_sommet.o main.o
	$(CXX) $(CXXFLAGS) -o CFC main.o Generator.o UserData.o Graphe.o Person.o Friends.o sommet.o ListeVoisins.o matAdj.o struct_sommet.o
#
Person.o: $(CURDIR)/cpp/Person.cpp
	$(CXX) $(CXXFLAGS) -o Person.o -c $(CURDIR)/cpp/Person.cpp
#
Friends.o: $(CURDIR)/cpp/Friends.cpp
	$(CXX) $(CXXFLAGS) -o Friends.o -c $(CURDIR)/cpp/Friends.cpp
#
struct_sommet.o: $(CURDIR)/cpp/struct_sommet.cpp
	$(CXX) $(CXXFLAGS) -o struct_sommet.o -c $(CURDIR)/cpp/struct_sommet.cpp
#
UserData.o: $(CURDIR)/cpp/UserData.cpp $(CURDIR)/h/Person.h $(CURDIR)/h/Friends.h
	$(CXX) $(CXXFLAGS) -o UserData.o -c $(CURDIR)/cpp/UserData.cpp
#
sommet.o: $(CURDIR)/cpp/sommet.cpp $(CURDIR)/h/struct_sommet.h $(CURDIR)/h/UserData.h
	$(CXX) $(CXXFLAGS) -o sommet.o -c $(CURDIR)/cpp/sommet.cpp
#
ListeVoisins.o: $(CURDIR)/cpp/ListeVoisins.cpp $(CURDIR)/h/sommet.h $(CURDIR)/h/UserData.h $(CURDIR)/h/Friends.h
	$(CXX) $(CXXFLAGS) -o ListeVoisins.o -c $(CURDIR)/cpp/ListeVoisins.cpp
#
matAdj.o: $(CURDIR)/cpp/matAdj.cpp $(CURDIR)/h/sommet.h $(CURDIR)/h/UserData.h
	$(CXX) $(CXXFLAGS) -o matAdj.o -c $(CURDIR)/cpp/matAdj.cpp
#
Generator.o: $(CURDIR)/cpp/Generator.cpp
	$(CXX) $(CXXFLAGS) -o Generator.o -c $(CURDIR)/cpp/Generator.cpp
#
Graphe.o: $(CURDIR)/cpp/Graphe.cpp $(CURDIR)/h/UserData.h $(CURDIR)/h/sommet.h $(CURDIR)/h/ListeVoisins.h $(CURDIR)/h/matAdj.h
	$(CXX) $(CXXFLAGS) -o Graphe.o -c $(CURDIR)/cpp/Graphe.cpp
#
main.o: $(CURDIR)/cpp/main.cpp $(CURDIR)/h/Generator.h $(CURDIR)/h/UserData.h $(CURDIR)/h/Graphe.h
	$(CXX) $(CXXFLAGS) -o main.o -c $(CURDIR)/cpp/main.cpp
#
clean:
	rm -rf *.o


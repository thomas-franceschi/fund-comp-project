all: main

main: main.o pokemon.o potion.o firetype.o flyingtype.o watertype.o
	g++ main.o pokemon.o potion.o firetype.o flyingtype.o watertype.o -o main
	
main.o: main.cpp
	g++ -c main.cpp
	
pokemon.o: pokemon.cpp
	g++ -c pokemon.cpp
	
potion.o: potion.cpp
	g++ -c potion.cpp
	
firetype.o: firetype.cpp
	g++ -c firetype.cpp
	
flyingtype.o: flyingtype.cpp
	g++ -c flyingtype.cpp
	
watertype.o: watertype.cpp
	g++ -c watertype.cpp
	
clean:
	rm -f *.o main
	

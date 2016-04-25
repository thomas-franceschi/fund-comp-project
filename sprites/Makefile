all: walking

walking: walking.o trainer.o pokemon.o potion.o moves.o firetype.o flyingtype.o watertype.o
	g++ walking.o trainer.o pokemon.o potion.o moves.o firetype.o flyingtype.o watertype.o -lSDL2 -lSDL2_image -o walking
		
walking.o: walking.cpp
	g++ -c walking.cpp -o walking.o

trainer.o: trainer.cpp
	g++ -c trainer.cpp -o trainer.o

pokemon.o: pokemon.cpp
	g++ -c pokemon.cpp
	
potion.o: potion.cpp
	g++ -c potion.cpp
	
moves.o: moves.cpp
	g++ -c moves.cpp
	
firetype.o: firetype.cpp
	g++ -c firetype.cpp
	
flyingtype.o: flyingtype.cpp
	g++ -c flyingtype.cpp
	
watertype.o: watertype.cpp
	g++ -c watertype.cpp
																		
clean:
	rm -f *.o walking
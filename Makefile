main : SDL_Engine.o Board.o Player.o Game.o main.o
	g++ SDL_Engine.o Board.o Player.o Game.o main.o -I /usr/include/SDL2/ -lSDL2 -lSDL2_ttf -o omok

Board.o : Board.hpp Board.cpp
	g++ -c Board.cpp -I /usr/include/SDL2/ -lSDL2 -lSDL2_ttf

Player.o : Player.hpp Board.hpp Player.cpp
	g++ -c Player.cpp -I /usr/include/SDL2/ -lSDL2 -lSDL2_ttf

Game.o : Player.hpp Board.hpp Game.hpp Game.cpp
	g++ -c Game.cpp -I /usr/include/SDL2/ -lSDL2 -lSDL2_ttf

SDL_Engine.o : Game.hpp SDL_Engine.hpp SDL_Engine.cpp
	g++ -c SDL_Engine.cpp -I /usr/include/SDL2/ -lSDL2 -lSDL2_ttf

main.o : Player.hpp Board.hpp SDL_Engine.hpp main.cpp
	g++ -c main.cpp -I /usr/include/SDL2/ -lSDL2 -lSDL2_ttf

clean :
	rm *.o
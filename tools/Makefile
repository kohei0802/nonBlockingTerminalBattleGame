#---------------
# 	Execute the following command in src directory:
# 	make -f ../tools/Makefile
#------------------------------
CFLGAS = -pedantic-errors -std=c++11 -lncurses
OBJ = main.o dreamwalk.o fight.o mapgame.o
COMP = g++
all: 	main

main: 	$(OBJ)
	$(COMP) $(CFLAGS) $(OBJ) -o main

main.o : 	main.cpp dreamwalk.h fight.h mapgame.h
	g++ $(CFLAGS) -c main.cpp

dreamwalk.o : 	dreamwalk.cpp dreamwalk.h fight.h mapgame.h
	g++ $(CFLAGS) -c dreamwalk.cpp

fight.o : 	fight.cpp fight.h
	g++ $(CFLAGS) -c fight.cpp

mapgame.o : 	mapgame.cpp mapgame.h
	g++ $(CFLAGS) -c mapgame.cpp

clean:
	rm -rf *.o main

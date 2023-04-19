#---------------
# 	Execute the following command in src directory:
# 	make -f ../tools/Makefile
#------------------------------
CFLAGS=-pedantic-errors -std=c++11 -lncurses
PATH_MOB = ./gameutil/movingobject
PATH_COL = ./gameutil/collision
OBJ = main.o dreamwalk.o fight.o mapgame.o mobj.o collision.o support.o
COMP = g++

all: 	main

main: 	$(OBJ)
	$(COMP) $(OBJ) $(CFLAGS) -o main

main.o : 	main.cpp dreamwalk.h fight.h mapgame.h $(PATH_MOB)/mobj.h $(PATH_COL)/collision.h support.o
	g++ $(CFLAGS) -c main.cpp

dreamwalk.o : 	dreamwalk.cpp dreamwalk.h fight.h mapgame.h $(PATH_MOB)/mobj.h $(PATH_COL)/collision.h
	g++ $(CFLAGS) -c dreamwalk.cpp

fight.o : 	fight.cpp fight.h $(PATH_MOB)/mobj.h $(PATH_COL)/collision.h
	g++ $(CFLAGS) -c fight.cpp

mapgame.o : 	mapgame.cpp mapgame.h
	g++ $(CFLAGS) -c mapgame.cpp

mobj.o : 	$(PATH_MOB)/mobj.cpp $(PATH_MOB)/mobj.h $(PATH_COL)/collision.h
	g++ $(CFLAGS) -c $(PATH_MOB)/mobj.cpp

collision.o : 	$(PATH_COL)/collision.cpp $(PATH_COL)/collision.h $(PATH_MOB)/mobj.h
	g++ $(CFLAGS) -c $(PATH_COL)/collision.cpp

support.o : 	support.cpp support.h	
	g++ $(CFLAGS) -c support.cpp 

clean:
	rm -rf *.o main

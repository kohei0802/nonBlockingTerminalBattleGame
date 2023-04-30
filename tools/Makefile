#---------------
# 	Execute the following command in src directory:
# 	make -f ../build/Makefile
#------------------------------
CFLGAS = -pedantic-errors -std=c++11
OBJ = test.o test2.o gameutil.o menu.o diy.o
COMP = g++

all: 	StuckinTheDream	

StuckinTheDream: 	$(OBJ)
	$(COMP) $(CFLAGS) $(OBJ) -o StuckinTheDream -lncurses

test.o : 	test.cpp
	g++ $(CFLAGS) -c test.cpp -lncurses

test2.o : 	test2.cpp
	g++ $(CFLAGS) -c test2.cpp -lncurses

gameutil.o : 	gameutil.cpp
	g++ $(CFLAGS) -c gameutil.cpp -lncurses

menu.o : 	menu.cpp
	g++ $(CFLAGS) -c menu.cpp -lncurses

diy.o : 	diy.cpp
	g++ $(CFLAGS) -c diy.cpp -lncurses

clean:
	rm -rf *.o StuckinTheDream

.PHONY: clean

#g++ test.cpp test2.cpp  gameutil.cpp -lncurses

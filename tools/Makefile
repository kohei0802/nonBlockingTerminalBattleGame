#---------------
# 	Execute the following command in src directory:
# 	make -f ../build/Makefile
#------------------------------
CFLGAS = -pedantic-errors -std=c++11 -lncurses
OBJ = main.o
COMP = g++
all: 	main

main: 	$(OBJ)
	$(COMP) $(CFLAGS) $(OBJ) -o main

main.o : 	main.cpp
	g++ $(CFLAGS) -c main.cpp

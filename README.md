# 1340Group7
1340Group Project Game-name: stuck_in_dream


----------Identification of team members------------
1) kohei0802
 - Ko Hei, LEUNG
 - UID: 3035928237

2) XXXX
 - XXX
 - XXXX

3) XXXX
 - XXX
 - XXX

4) XXXX
 - XXX
 - XX


Requirement of the game-----------
Make sure you zoom out enough so that every component of the game is displayed properly

Make sure you read the comment in /tools/Makefile to learn how to compile the game


Description of the game-----------------
Game Name:  "Stuck in dream"
Why?
"It's about a man who is stuck in his dream every night unless he beats the monster in it"

What's in this game?
1) Map Stage
In this stage, player needs to explore around to reach the boss stage

2) Monster stage
In this stage, player needs to kill the monster in order to proceed to the next day of his life. 

How to play? 
1) When player is in the title page
 - He can choose to start the game from scratch. Press space to do that.
 - He can quit the game by pressing 'q'
 - He can resume the game by pressing 'R' from the previous game status he saved. 

2) When he is in map stage
 - Press arrow keys to move
 - move the player so that '*' is on the right side of player's mouth in order to interact with the NPCs and treasures
 - When dialogs are displayed. Type y/n to make decision

3) When he is in monster stage
 - press 'y' to start the fight
 - press arrow keys to move
 - use 'awsd' keys to stab the boss

4) To pause the game (currently only available in map stage)
 - Press space key

How to save the game status (HP, Coins) etc?
Do step 4) mentioned above

Specific components? 
a) Day 1:
 - Business man => if lucky, player gets boost in HP
 - treasure => player gets the sword
 - master/shifu => player gets the skill to move quick (press 'f' before using it)

b) Day 2:
 - Witch: give you suspicious apple
 - treasure => pass the challenge to upgrade the sword!! (attack point increased from 10 to 50)
 - hospital => heals you if you pay them

Features in this game----------------------
1) Random generation of game sets
Stage 1, the npc1 on top left of the screen. Randomly gives you toxic/healing drink
InitRand() in gameutil.cpp is highlight of our project. Using time information makes sure seed value for random numbers
are different everytime
Used by rand() in test.cpp:74

2) Data Structures for storing game status
We used structures to store all the characters and displays' information
Mostly defined in test.cpp and test2.cpp

3) Dynamic memory management 
At the first few lines of test2.cpp:main2(), memory is allocated to text[]


4) File input/output
Player can enter pause menu to save all the game status
Next time he plays, he can choose to start from those status

5) Multifile Program
test.cpp => contains main(), first stage of the game
test2.cpp => contains main2(), second stage of the game
gameutil.h, gameutil.cpp => define functions for generating random values, getting time information, etc.
menu.h, menu.cpp => Provides API for a pausing menu

6) Additional: Multitasking
I first tried using threading to achieve the multitasking. However, ncurses.h probably doesn't support it well. 
Therefore, I solved it by using <chrono>.
I built a function to get time as double. 
Inside some specfic routine codes, I declared "static double" variables to store the time information of the 
last time the specific code is executed. Everytime this code is run through, the condition statement checks if 
time has passed enough since the last exeucution. Only if it's enough, it's executed again.
This is important, because if we used sleep(), it'll stop the program and user won't be able to enter input, 
and move the player, while the boss is moving around. 


Special library used ---------------------------------
This game is powered by <ncurses.h>
It comes with UNIX, LINUX, etc.
compile with -lncurses flag
It introduces GUI like features to our game


Compilation instruction ------------------------------
make -f ../build/Makefile

execute the above command INSIDE SRC DIRECTORY!!! 

Then, execute by 

./StuckinTheDream


(OPTIONAL) to clean the binaries, and object files, do this

make -f ../build/Makefile clean









26/4/2023 Commit (kohei0802)

 - added "srand((unsigned int) getime())" to get real random values
 - added fix to jamming of players around the conversation points by measuring time
 - added sword's power upgrade
 - added characters 
 - added a mini-challenge to the treasure
 - added a Title display
 - added connection between Stage 1 (Day 1) and Stage 2 (Day 2)
 - added fix to printing problem. Properly added attroff() after attron()

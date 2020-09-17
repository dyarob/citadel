all:
	gcc src/*.c -o Citadel -l ncurses -I inc
clean:
	rm Citadel #-rf

all:
	gcc main.c -o Citadel -l ncurses #-I inc
clean:
	rm Citadel #-rf

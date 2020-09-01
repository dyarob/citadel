all:
	gcc main.c maps.c -o Citadel -l ncurses #-I inc
clean:
	rm Citadel #-rf

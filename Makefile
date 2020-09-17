all:
	gcc main.c save.c maps.c raven.c -o Citadel -l ncurses #-I inc
clean:
	rm Citadel #-rf

#include <ncurses.h>
#include <locale.h>

#include "Game.hpp"

int	main(int ac, char **av) {

	// ncurses init
	setlocale(LC_ALL, "");
	initscr(); cbreak(); noecho();
	nodelay(stdscr, TRUE);
	refresh();

	// variables
	Game game;

	// hello world
	printw("HELLO WORLD\n");
	printw("Room: ");
	printw(game.room.c_str());
	refresh();
	while(1);

	// ncurses end
	endwin();
}

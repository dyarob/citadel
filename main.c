#include <ncurses.h>
#include <locale.h>

#include "maps.h"

int	main(int ac, char **av) {

// ncurses init
setlocale(LC_ALL, "");
initscr(); cbreak(); noecho();
nodelay(stdscr, TRUE);
refresh();

// variables here
WINDOW	*window = newwin(40, 100, LINES/2-20, COLS/2-50);
char	c = 0;
Map	*map1 = loadmap();

box(window, 0, 0);
mvwaddstr(window, 2, 2, "Press a key");

mvwaddstr(window, 4, 0, map1->s);
wrefresh(window);

while((c=getch())==ERR);

// ending
delwin(window);
endwin();
return 0;}

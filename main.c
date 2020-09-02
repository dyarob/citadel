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
char	c = 0;
Map	*map1 = loadmap();
WINDOW	*mapw = newwin(map1->siz[0], map1->siz[1]+1,
		LINES/2-map1->siz[0]/2, COLS/2-map1->siz[1]/2);

// display
mvwaddstr(mapw, 0, 0, map1->s);
wrefresh(mapw);

while((c=getch())==ERR);

// ending
delwin(mapw);
endwin();
return 0;}

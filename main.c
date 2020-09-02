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
//current map
Map	*map1 = loadmap();
WINDOW	*mapw = newwin(LINES, COLS, 0, 0);
int	mapoffset[2] = {0, 0};
//character
int	cpos[2] = {map1->mid[0]-1, map1->mid[1]-1};
//UI
WINDOW	*mtitl = newwin(5, 25, 1, 2);

while(1) {
	// display
	//map
	werase(mapw);
	for(int i=0; i<map1->siz[0]; i++)
		mvwaddnstr(mapw, LINES/2-map1->mid[0] + i + mapoffset[0],
			COLS/2-map1->mid[1] + mapoffset[1],
			map1->s + i*(map1->siz[1]+1), map1->siz[1]);
	//character
	mvaddch(LINES/2-1, COLS/2-1, 'C');
	wrefresh(mapw);
	//UI
	box(mtitl, 0, 0);
	mvwaddstr(mtitl, 2, 3, "Citadel Hall");
	wrefresh(mtitl);

	// game
	while((c=getch())==ERR);
	if(c == 'q') break;
	//movement
	else if(c == 'e' && !map1->collision[(cpos[0]-1)*map1->siz[1]+cpos[1]])
		{ mapoffset[0]++; cpos[0]--; }
	else if(c == 'd' && !map1->collision[(cpos[0]+1)*map1->siz[1]+cpos[1]])
		{ mapoffset[0]--; cpos[0]++; }
	else if(c == 's' && !map1->collision[(cpos[0])*map1->siz[1]+cpos[1]-1])
		{ mapoffset[1]++; cpos[1]--; }
	else if(c == 'f' && !map1->collision[(cpos[0])*map1->siz[1]+cpos[1]+1])
		{ mapoffset[1]--; cpos[1]++; }
}

// ending
delwin(mapw);
endwin();
return 0;}

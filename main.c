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
WINDOW	*mapw = newwin(LINES, COLS, 0, 0);
Map	*map = loadmap("maps/1");
//character
int	cpos[2] = {10, 18};
//UI
WINDOW	*mtitl = newwin(5, strlen(map->title)+6, 1, 2);

while(1) {
	// display
	//map
	werase(mapw);
	for(int i=0; i<map->siz[0]; i++)
		mvwaddnstr(mapw, LINES/2-cpos[0] + i, (COLS/2-cpos[1]>=0?COLS/2-cpos[1]:0),
			map->s + i*(map->siz[1]+1) -(COLS/2-cpos[1]<0?COLS/2-cpos[1]:0),
			(COLS/2-cpos[1]+map->siz[1]<COLS?map->siz[1]:map->siz[1]+(COLS-(COLS/2-cpos[1]+map->siz[1]))));
	//character
	mvaddch(LINES/2, COLS/2, 'C');
	wrefresh(mapw);
	//UI
	box(mtitl, 0, 0);
	mvwaddstr(mtitl, 2, 3, map->title);
	wrefresh(mtitl);

	// game
	while((c=getch())==ERR);
	if(c == 'q') break;
	//movement
	else if(c == 'e' && !map->collision[(cpos[0]-1)*map->siz[1]+cpos[1]]) cpos[0]--;
	else if(c == 'd' && !map->collision[(cpos[0]+1)*map->siz[1]+cpos[1]]) cpos[0]++;
	else if(c == 's' && !map->collision[(cpos[0])*map->siz[1]+cpos[1]-1]) cpos[1]--;
	else if(c == 'f' && !map->collision[(cpos[0])*map->siz[1]+cpos[1]+1]) cpos[1]++;
	//going through doors
	if(map->s[cpos[0]*(map->siz[1]+1)+cpos[1]] == 'D') {
		int i;
		for(i=0; map->doors[i]->pos[0]!=cpos[0] || map->doors[i]->pos[1]!=cpos[1]; i++);
		cpos[0] = map->doors[i]->dstpos[0]; cpos[1] = map->doors[i]->dstpos[1];
		map = loadmap(map->doors[i]->dstpath);
		delwin(mtitl); mtitl = newwin(5, strlen(map->title)+6, 1, 2);
	}
}

// ending
delwin(mapw);
endwin();
return 0;}

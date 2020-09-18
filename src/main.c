#include <ncurses.h>
#include <locale.h>

#include "timer.h"
#include "save.h"
#include "maps.h"
#include "npc.h"

int	main(int ac, char **av) {

// ncurses init
setlocale(LC_ALL, "");
initscr(); cbreak(); noecho();
nodelay(stdscr, TRUE);
refresh();

// variables here
char	c = 'y';
//current map
char	*curmap;
Map	*map;
WINDOW	*mapw = newwin(LINES, COLS, 0, 0);
//character
int	cpos[2];
//npcs
Npc	**npc = loadnpc();

// loading save
load(&curmap, cpos);
if(curmap) {
	map = (loadmap(curmap));
} else {
	map = (loadmap("maps/1"));
	cpos[0] = 10; cpos[1] = 18;}

//UI
WINDOW	*mtitl = newwin(5, strlen(map->title)+6, 1, 2);
WINDOW	*mcontt = newwin(LINES-10, 25, 5, 2);
bool	quit = false;
WINDOW	*exit = newwin(5, 50, LINES/2-3, COLS/2-25);

Npc	*talk = NULL;
FILE	*f;
char	*s = malloc(100);
WINDOW	*dialog = newwin(5, COLS-54, LINES-6, COLS/2-(COLS-54)/2);

// MAIN LOOP
struct timeval	t; gettimeofday(&t, NULL);
while(1) {

	// display
	if(c!=ERR) {
		//map
		werase(mapw);
		for(int i=0; i<map->siz[0]; i++)
			mvwaddnstr(mapw, LINES/2-cpos[0] + i, (COLS/2-cpos[1]>=0?COLS/2-cpos[1]:0),
				map->s + i*(map->siz[1]+1) -(COLS/2-cpos[1]<0?COLS/2-cpos[1]:0),
				(COLS/2-cpos[1]+map->siz[1]<COLS?map->siz[1]:map->siz[1]+(COLS-(COLS/2-cpos[1]+map->siz[1]))));
		//character
		mvwaddch(mapw, LINES/2, COLS/2, 'C');
		//npcs
		for(int i=0; npc[i]; i++)
			if(!strcmp(map->path, npc[i]->map))
				mvwaddch(mapw, LINES/2-cpos[0]+npc[i]->pos[0],
					COLS/2-cpos[1]+npc[i]->pos[1], npc[i]->name[0]);

		wrefresh(mapw);
		//UI
		mvwaddstr(mtitl, 2, 3, map->title);
		box(mtitl, 0, 0); wrefresh(mtitl);

		wmove(mcontt, 1, 2);
		for(int i=0; npc[i]; i++) {
			if(!strcmp(map->path, npc[i]->map)) {
				waddch(mcontt, npc[i]->name[0]);
				waddstr(mcontt, "- ");
				waddstr(mcontt, npc[i]->name);
				waddstr(mcontt, "\n  ");}}
		box(mcontt, 0, 0); wrefresh(mcontt);

		if(quit) {
			mvwaddstr(exit, 2, 3, "Save before exiting? (y/n/space)");
			box(exit, 0, 0); wrefresh(exit);}

		if(talk) {
			mvwaddstr(dialog, 2, 3, s);
			box(dialog, 0, 0); wrefresh(dialog);}
	}

	// GAME
	if((c = getch())!=ERR) {
		//basics & UI
		if(quit && c == 'y') {
			save(map->path, cpos);
			break;}
		else if(quit && c == 'n') break;
		else if(quit && c == ' ') quit = false;
		else if(c == 'q') quit = true;
		//actions
		else if(c == 't') {
			for(int i=0; npc[i]; i++)
				if(!strcmp(map->path, npc[i]->map)
					&& abs(cpos[0]-npc[i]->pos[0])+abs(cpos[1]-npc[i]->pos[1] < 3))
					talk = npc[i];
					strcpy(s, "talk/"); strcat(s, talk->name);
					f = fopen(s, "r"); fgets(s, 100, f); fclose(f);}
		//movement
		else if(c == 'e' || c == 'd' || c == 's' || c == 'f') {
			talk = NULL;
			if(c == 'e' && !map->collision[(cpos[0]-1)*map->siz[1]+cpos[1]]) cpos[0]--;
			else if(c == 'd' && !map->collision[(cpos[0]+1)*map->siz[1]+cpos[1]]) cpos[0]++;
			else if(c == 's' && !map->collision[(cpos[0])*map->siz[1]+cpos[1]-1]) cpos[1]--;
			else if(c == 'f' && !map->collision[(cpos[0])*map->siz[1]+cpos[1]+1]) cpos[1]++;
			//going through doors
			if(map->s[cpos[0]*(map->siz[1]+1)+cpos[1]] == 'D') {
				int	i;
				void	*buf;
				for(i=0; map->doors[i]->pos[0]!=cpos[0] || map->doors[i]->pos[1]!=cpos[1]; i++);
				cpos[0] = map->doors[i]->dstpos[0]; cpos[1] = map->doors[i]->dstpos[1];
				buf = map;
				map = loadmap(map->doors[i]->dstpath);
				delmap(buf);
				delwin(mtitl); mtitl = newwin(5, strlen(map->title)+6, 1, 2);
				werase(mcontt);
			}
		}
	}
	twait(&t);
}

// ending
free(s);
freenpc(npc);
free(curmap);
delwin(mtitl);
delwin(mcontt);
delmap(map);
delwin(mapw);
endwin();
return 0;}

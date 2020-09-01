#include <ncurses.h>
#include <locale.h>

int	main(int ac, char **av) {

setlocale(LC_ALL, "");
initscr(); cbreak(); noecho();
nodelay(stdscr, TRUE);
refresh();

WINDOW	*window = newwin(40, 100, LINES/2-20, COLS/2-50);
char	c = 0;

box(window, 0, 0);
mvwaddstr(window, 2, 2, "Press a key");
wrefresh(window);

while((c=getch())==ERR);

delwin(window);
endwin();
return 0;}

#include "maps.h"

Map	*loadmap() {

FILE	*f = fopen("maps/1", "r");
Map	*m = malloc(sizeof(Map));

fseek(f, 4, 0);
m->siz[0] = (fgetc(f)-'0')*100;
m->siz[0] += (fgetc(f)-'0')*10;
m->siz[0] += fgetc(f)-'0';
fgetc(f);
m->siz[1] = (fgetc(f)-'0')*100;
m->siz[1] += (fgetc(f)-'0')*10;
m->siz[1] += fgetc(f)-'0';

fseek(f, 16, 0);
m->mid[0] = (fgetc(f)-'0')*100;
m->mid[0] += (fgetc(f)-'0')*10;
m->mid[0] += fgetc(f)-'0';
fgetc(f);
m->mid[1] = (fgetc(f)-'0')*100;
m->mid[1] += (fgetc(f)-'0')*10;
m->mid[1] += fgetc(f)-'0';

fgetc(f);
m->s = malloc(m->siz[0]*m->siz[1] +m->siz[0]);
fread(m->s, 1, m->siz[0]*m->siz[1] +m->siz[0], f);

fclose(f);
return m;}

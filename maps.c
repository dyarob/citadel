#include "maps.h"

Map	*loadmap() {

FILE	*f = fopen("maps/1", "r");
Map	*m = malloc(sizeof(Map));

fseek(f, 5, 0);
m->siz[0] = fgetc(f)*100 + fgetc(f)*10 + fgetc(f);
fgetc(f);
m->siz[1] = fgetc(f)*100 + fgetc(f)*10 + fgetc(f);

fseek(f, 17, 0);
m->mid[0] = fgetc(f)*100 + fgetc(f)*10 + fgetc(f);
fgetc(f);
m->mid[1] = fgetc(f)*100 + fgetc(f)*10 + fgetc(f);

fgetc(f);
m->s = malloc(m->siz[0]*m->siz[1] +m->siz[0]);
fread(m->s, 1, m->siz[0]*m->siz[1] +m->siz[0], f);

fclose(f);
return m;}

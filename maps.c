#include "maps.h"

Map	*loadmap(const char *map) {

FILE	*f = fopen(map, "r");
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
m->s = malloc(m->siz[0]*(m->siz[1]+1));
fread(m->s, 1, m->siz[0]*(m->siz[1]+1), f);

fclose(f);

// collision map
m->collision = malloc(m->siz[0]*m->siz[1]);
for(int j=0; j<m->siz[0]; j++)
for(int i=0; i<m->siz[1]; i++)
	if(m->s[j*(m->siz[1]+1)+i] == ' ' || m->s[j*(m->siz[1]+1)+i] == 'o')
		m->collision[j*m->siz[1]+i] = true;
	else m->collision[j*m->siz[1]+i] = false;

return m;}

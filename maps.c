#include "maps.h"

Map	*loadmap(const char *map) {

Map	*m = malloc(sizeof(Map));
int	i = 0;
FILE	*f = fopen(map, "r");

m->path = malloc(7); m->path[7]='\0';
strcpy(m->path, map);

// info
fseek(f, 4, 0);
m->siz[0] = (fgetc(f)-'0')*100;
m->siz[0] += (fgetc(f)-'0')*10;
m->siz[0] += fgetc(f)-'0';
fgetc(f);
m->siz[1] = (fgetc(f)-'0')*100;
m->siz[1] += (fgetc(f)-'0')*10;
m->siz[1] += fgetc(f)-'0';

// doors
fseek(f, 19, 0);
while(fgetc(f)!='\n') {
	i++;
	fseek(f, 19+26*i, 0);
}
m->doors = malloc(sizeof(void*)*(i+1));
for(int j=0; j<i; j++) {
	fseek(f, 22+26*j, 0);
	m->doors[j] = malloc(sizeof(Door));
	m->doors[j]->dstpath = malloc(7);
	fread(m->doors[j]->dstpath, 1, 6, f);
	m->doors[j]->dstpath[6] = '\0';
	fgetc(f);
	m->doors[j]->pos[0] = (fgetc(f)-'0')*100;
	m->doors[j]->pos[0] += (fgetc(f)-'0')*10;
	m->doors[j]->pos[0] += fgetc(f)-'0';
	fgetc(f);
	m->doors[j]->pos[1] = (fgetc(f)-'0')*100;
	m->doors[j]->pos[1] += (fgetc(f)-'0')*10;
	m->doors[j]->pos[1] += fgetc(f)-'0';
	fgetc(f);
	m->doors[j]->dstpos[0] = (fgetc(f)-'0')*100;
	m->doors[j]->dstpos[0] += (fgetc(f)-'0')*10;
	m->doors[j]->dstpos[0] += fgetc(f)-'0';
	fgetc(f);
	m->doors[j]->dstpos[1] = (fgetc(f)-'0')*100;
	m->doors[j]->dstpos[1] += (fgetc(f)-'0')*10;
	m->doors[j]->dstpos[1] += fgetc(f)-'0';
}
m->doors[i] = NULL;
fseek(f, 20+26*i, 0);

// title
i = 0;
while(fgetc(f)!='\n') i++;
m->title = malloc(i+1);
fseek(f, -i-1, SEEK_CUR);
i = 0;
while((m->title[i] = fgetc(f))!='\n') i++;
m->title[i] = '\0';

while(fgetc(f)!='\n');
while(fgetc(f)!='\n');

// actual map
m->s = malloc(m->siz[0]*(m->siz[1]+1));
fread(m->s, 1, m->siz[0]*(m->siz[1]+1), f);

fclose(f);


// collision map generation
m->collision = malloc(m->siz[0]*m->siz[1]);
for(int j=0; j<m->siz[0]; j++)
for(int i=0; i<m->siz[1]; i++)
	if(m->s[j*(m->siz[1]+1)+i] == ' ' || m->s[j*(m->siz[1]+1)+i] == 'o')
		m->collision[j*m->siz[1]+i] = true;
	else m->collision[j*m->siz[1]+i] = false;

return m;}


void	delmap(Map *map) {
free(map->title);
free(map->s);
free(map->collision);
for(int i=0; map->doors[i]!=NULL; i++) {
	free(map->doors[i]->dstpath);
	free(map->doors[i]);
}
free(map->doors);
free(map);
}

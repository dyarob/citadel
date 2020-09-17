#include "npc.h"

Npc	**loadnpc() {

Npc	**r;
int	n = 0, j;
FILE	*f = fopen("npc", "r");

char	*s = malloc(100);
while(fgets(s, 100, f)) n++;
free(s);
r = malloc(sizeof(void*)*(n+1)); r[n] = NULL;

fseek(f, 0, SEEK_SET);
for(int i=0; i<n; i++) {
	r[i] = malloc(sizeof(Npc));

	r[i]->map = malloc(7); r[i]->map[6]='\0';
	fread(r[i]->map, 1, 6, f);
	fgetc(f);

	r[i]->pos[0] = (fgetc(f)-'0')*100;
	r[i]->pos[0] += (fgetc(f)-'0')*10;
	r[i]->pos[0] += fgetc(f)-'0';
	fgetc(f);
	r[i]->pos[1] = (fgetc(f)-'0')*100;
	r[i]->pos[1] += (fgetc(f)-'0')*10;
	r[i]->pos[1] += fgetc(f)-'0';
	fgetc(f);

	fgetc(f);
	j = 0; while(fgetc(f)!='"') j++;
	r[i]->name = malloc(j+1); r[i]->name[j]='\0';
	fseek(f, -j-1, SEEK_CUR);
	fread(r[i]->name, 1, j, f);
	fgetc(f);
	fgetc(f);
}

fclose(f);
return r;
}

void	freenpc(Npc **p) {

int	i = 0;

while(p[i]) {
	free(p[i]->map);
	free(p[i]->name);
	free(p[i]);
	i++;}
free(p);
return;}

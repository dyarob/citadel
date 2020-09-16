#include "raven.h"

int	**loadraven(const char *path) {

int	**r = NULL;
int	n = 0;
FILE	*f = fopen(path, "r");

while(fgetc(f)!=EOF) {
	while(fgetc(f)!='\n');
	n++;
}
r = malloc(sizeof(void*)*(n+1));
r[n] = NULL;

fseek(f, 0, SEEK_SET);

for(int i=0; i<n; i++) {
	r[i] = malloc(sizeof(int)*2);
	r[i][0] = (fgetc(f)-'0')*100;
	r[i][0] += (fgetc(f)-'0')*10;
	r[i][0] += fgetc(f)-'0';
	fgetc(f);
	r[i][1] = (fgetc(f)-'0')*100;
	r[i][1] += (fgetc(f)-'0')*10;
	r[i][1] += fgetc(f)-'0';
	fgetc(f);
}

fclose(f);
return r;
}

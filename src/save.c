#include "save.h"

void	load(char **curmap, int cpos[2]) {

int	i = 0;
FILE	*f = fopen("save", "r");

if(!f) { *curmap = NULL; return; }

while(fgetc(f)!='\n') i++;
*curmap = malloc(i+1); *curmap[i] = '\0';
fseek(f, 0, SEEK_SET);
fread(*curmap, 1, i, f);
fgetc(f);

cpos[0] = (fgetc(f)-'0')*100;
cpos[0] += (fgetc(f)-'0')*10;
cpos[0] += fgetc(f)-'0';
fgetc(f);
cpos[1] = (fgetc(f)-'0')*100;
cpos[1] += (fgetc(f)-'0')*10;
cpos[1] += fgetc(f)-'0';

fclose(f);
return;}

void	save(char *curmap, int cpos[2]) {

int	h, t, u;
FILE	*f = fopen("save", "w");

fseek(f, 0, SEEK_SET);
fputs(curmap, f);
fputc('\n', f);

h = cpos[0]/100;
t = (cpos[0]-h*100)/10;
u = cpos[0]-h*100-t*10;
fputc(h+'0', f);
fputc(t+'0', f);
fputc(u+'0', f);
fputc(';', f);
h = cpos[1]/100;
t = (cpos[1]-h*100)/10;
u = cpos[1]-h*100-t*10;
fputc(h+'0', f);
fputc(t+'0', f);
fputc(u+'0', f);
fputc('\n', f);

fclose(f);
return;}

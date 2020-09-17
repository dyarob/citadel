#include "save.h"

char	*load() {

int	i = 0;
char	*s = NULL;
FILE	*f = fopen("save", "r");

if(!f) return NULL;

while(fgetc(f)!='\n') i++;
s = malloc(i+1); s[i] = '\0';
fseek(f, 0, SEEK_SET);
fread(s, 1, i, f);

fclose(f);
return s;}

void	save(char *s) {

int	i;
FILE	*f = fopen("save", "w");

fseek(f, 0, SEEK_SET);
fputs(s, f);
fputc('\n', f);

fclose(f);
return;}

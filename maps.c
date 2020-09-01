#include "maps.h"

char	*loadmap() {

FILE	*f = fopen("maps/1", "r");
int	size = 0;
char	*s = NULL;

fseek(f, 0, SEEK_END);
size = ftell(f);
rewind(f);
s = malloc(size);
fread(s, sizeof(char), size/sizeof(char), f);

return s;}

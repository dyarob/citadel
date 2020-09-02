#ifndef MAPS_H
#define MAPS_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	{
	int	siz[2];
	int	mid[2];
	char	*s;
} Map;

Map	*loadmap();

#endif

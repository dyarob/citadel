#ifndef MAPS_H
#define MAPS_H
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	{
	int	siz[2];
	int	mid[2];
	char	*s;
	bool	*collision;
} Map;

Map	*loadmap(const char *map);

#endif

#ifndef MAPS_H
#define MAPS_H
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	char	*dstpath;
	int	pos[2];
	int	dstpos[2];
} Door;

typedef struct	{
	char	*title;
	int	siz[2];
	char	*s;
	bool	*collision;
	Door	**doors;
} Map;

Map	*loadmap(const char *map);
void	delmap(Map *map);

#endif

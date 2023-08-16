#include "../inc/cub3d.h"

/* Cant be first or last row & first or last char!
   x and y position stands for a '0' in map.
	- check all directions - should be safe from borders!
	- !!!! make sure to only check if line below / above is long enough!! */	
int	check_neighbors(t_map *map, int x, int y)
{
	if ((int)ft_strlen(map->cmap[y - 1]) >= x)
	{
		if (map->cmap[y - 1][x] != '1' && map->cmap[y - 1][x] != '0')
			return (0);
	}
	else if ((int)ft_strlen(map->cmap[y - 1]) < x)
		return (0);
	if (map->cmap[y][x - 1] != '1' && map->cmap[y][x - 1] != '0' )
		return (0);
	if (map->cmap[y][x + 1] != '1' && map->cmap[y][x + 1] != '0' )
		return (0);
	if ((int)ft_strlen(map->cmap[y + 1]) >= x)
	{
		if (map->cmap[y + 1][x] != '1' && map->cmap[y + 1][x] != '0' )
			return (0);
	}
	else if ((int)ft_strlen(map->cmap[y + 1]) < x)
		return (0);
	return (1);
}

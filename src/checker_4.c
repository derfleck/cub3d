#include "../inc/cub3d.h"

//make sure to only check if line below / above is long enough!!
int	special_rows(t_map *map, int x, int y)
{
	size_t	row_len;

	if (y == 0)
	{
		row_len = ft_strlen(map->cmap[y + 1]);
		if ((int)row_len < x)
			return (1);
		else
		{
			if (map->cmap[y + 1][x] != '1' && map->cmap[y + 1][x] != ' ')
				return (0);
		}
	}
	else if (y == (map->max[Y] - 1))
	{
		row_len = ft_strlen(map->cmap[y - 1]);
		if ((int)row_len < x)
			return (1);
		else
		{
			if (map->cmap[y - 1][x] != '1' && map->cmap[y - 1][x] != ' ')
				return (0);
		}
	}
	return (1);
}

/* Can't be first or last row!
	- make sure to only check up, right and down */
int	beginning_is_space(t_map *map, int x, int y)
{
	if (map->cmap[y - 1][x] != '1' && map->cmap[y - 1][x] != ' ' )
		return (0);
	if (map->cmap[y][x + 1] != '1' && map->cmap[y][x + 1] != ' ' )
		return (0);
	if (map->cmap[y + 1][x] != '1' && map->cmap[y + 1][x] != ' ' )
		return (0);
	return (1);
}

/* Can't be first or last row!
	- make sure to only check up, left and down
	- make sure to only check if line below / above is long enough!! */
int	ending_is_space(t_map *map, int x, int y)
{
	if (ft_strlen(map->cmap[y - 1]) >= ft_strlen(map->cmap[y]))
	{
		if (map->cmap[y - 1][x] != '1' && map->cmap[y - 1][x] != ' ' )
			return (0);
	}
	if (map->cmap[y][x - 1] != '1' && map->cmap[y][x - 1] != ' ' )
		return (0);
	if (ft_strlen(map->cmap[y + 1]) >= ft_strlen(map->cmap[y]))
	{
		if (map->cmap[y + 1][x] != '1' && map->cmap[y + 1][x] != ' ' )
			return (0);
	}
	return (1);
}

/* Cant be first or last row & first or last char.
	- check all directions!
	- make sure to only check if line below / above is long enough!! */
int	check_all_directions(t_map *map, int x, int y)
{
	if ((int)ft_strlen(map->cmap[y - 1]) >= y)
	{
		if (map->cmap[y - 1][x] != '1' && map->cmap[y - 1][x] != ' ' )
			return (0);
	}
	if (map->cmap[y][x - 1] != '1' && map->cmap[y][x - 1] != ' ' )
		return (0);
	if (map->cmap[y][x + 1] != '1' && map->cmap[y][x + 1] != ' ' )
		return (0);
	if ((int)ft_strlen(map->cmap[y + 1]) >= y)
	{
		if (map->cmap[y + 1][x] != '1' && map->cmap[y + 1][x] != ' ' )
			return (0);
	}
	return (1);
}

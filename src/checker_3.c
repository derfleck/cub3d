#include "../inc/cub3d.h"

/* Checks first and last row of map - can be only ones or spaces! */
static int	check_first_n_last(char **map, int last)
{
	int	i;
	int	first;

	first = 0;
	i = -1;
	while (map[first][++i])
	{
		if (map[first][i] != '1' && map[last][i] != ' ')
			return (0);
	}
	i = -1;
	while (map[last][++i])
	{
		if (map[last][i] != '1' && map[last][i] != ' ')
			return (0);
	}
	return (1);
}

// check only second till second to last rows!!!! 
static int	check_middle_lines(t_map *map)
{
	int	y;
	int	end;

	y = 0;
	while (map->cmap[++y] && ((y + 1) < map->max[Y]))
	{
		if (map->cmap[y][0] != '1')
			return (0);
		end = (ft_strlen(map->cmap[y]) - 1);
		if (map->cmap[y][end] != '1')
			return (0);
	}
	return (1);
}

/* watch for outside of map! 
	- First and last row to be checked only vertically!
	- Endofline spaces?
	-	  */
static int	check_neighbors(t_map *map, int x, int y)
{
	if (y == 0 || y == (map->max[Y] - 1))
	{
		if (!special_rows(map, x, y))
			return (0);
	}
	else if (x == 0) //first element is a space
	{
		if (!beginning_is_space(map, x, y))
			return (0);
	}
	else if (x == ((int)ft_strlen(map->cmap[y]) - 1)) //last element
	{
		if (!ending_is_space(map, x, y))
			return (0);
	}
	else
	{
		if (!check_all_directions(map, x, y))
			return (0);
	}
	return (1);
}

/* Around spaces there can be only 1s or other spaces. */
static int	check_around_spaces(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (map->cmap[++y] && y < map->max[Y])
	{
		x = -1;
		while (map->cmap[y][++x])
		{
			if (map->cmap[y][x] == ' ')
			{
				if (!check_neighbors(map, x, y))
					return (0);
			}
		}
	}
	return (1);
}

int	check_walls(t_map *map)
{
	if (!check_first_n_last(map->cmap, (map->max[Y] - 1)) || \
	!check_middle_lines(map) || !check_around_spaces(map))
	{
		ft_putendl_fd("Error\nWalls are invalid in map!", 2);
		return (0);
	}
	return (1);
}

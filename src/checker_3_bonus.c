/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:20:32 by rmocsai           #+#    #+#             */
/*   Updated: 2023/08/21 10:20:34 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

/* Checks first and last row of map - can be only ones or spaces! */
static int	check_first_n_last(char **map, int last)
{
	int	i;
	int	first;

	first = 0;
	i = -1;
	while (map[first][++i])
	{
		if (map[first][i] != '1' && map[first][i] != ' ')
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
		if (map->cmap[y][0] != '1' && map->cmap[y][0] != ' ')
			return (0);
		end = (ft_strlen(map->cmap[y]) - 1);
		if (map->cmap[y][end] != '1' && map->cmap[y][end] != ' ')
			return (0);
	}
	return (1);
}

/* Cant be first or last row & first or last char!
   x and y position stands for a '0' in map.
	- check all directions - should be safe from borders!
	- !!!! make sure to only check if line below / above is long enough!! */	
static int	check_neighbors(t_map *map, int x, int y)
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

/* Around spaces there can be only 1s or other spaces. */
static int	check_around_zeros(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->cmap[++y] && y < map->max[Y])
	{
		x = 0;
		while (map->cmap[y][++x] && x < ((int)ft_strlen(map->cmap[y]) - 1))
		{
			if (map->cmap[y][x] == '0')
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
	!check_middle_lines(map) || !get_start_position(map) || \
	!check_around_zeros(map))
	{
		ft_putendl_fd("Error\nWalls are invalid in map!", 2);
		return (0);
	}
	return (1);
}

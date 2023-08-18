/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:13:13 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:13:13 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* It also modifies player direction!! */
static int	count_stuff(t_map *map, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	count;

	count = 0;
	i = -1;
	j = -1;
	while (map->cmap[++i])
	{
		while (map->cmap[i][++j])
		{
			if (map->cmap[i][j] == c)
			{
				map->dir = c;
				count++;
			}
		}
		j = -1;
	}
	return (count);
}

static int	check_valid_chars(char **map)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'W' && \
			map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'N' && \
			map[y][x] != ' ')
				return (0);
		}
	}
	return (1);
}

static int	check_for_spaces_on_nl(char **map)
{
	int	x;
	int	y;
	int	flag;

	y = -1;
	while (map[++y])
	{
		x = -1;
		flag = 1;
		while (map[y][++x])
		{
			if (flag && map[y][x] == ' ')
				flag++;
			else
				flag = 0;
		}
		if (flag != 0)
			break ;
	}
	if (flag)
		return (0);
	return (1);
}

static int	check_chars(t_map *map)
{
	int	player_count;

	player_count = 0;
	if (!check_valid_chars(map->cmap) || !check_for_spaces_on_nl(map->cmap))
	{
		ft_putendl_fd("Error\nInvalid character in map!", 2);
		return (0);
	}
	player_count += count_stuff(map, 'S');
	player_count += count_stuff(map, 'W');
	player_count += count_stuff(map, 'E');
	player_count += count_stuff(map, 'N');
	if (player_count != 1)
	{
		ft_putendl_fd("Error\nPlayer count is invalid!", 2);
		return (0);
	}
	return (1);
}

int	check_map_validity(t_map *map)
{
	if (!check_chars(map) || !check_walls(map))
		return (0);
	return (1);
}

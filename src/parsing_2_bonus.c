/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:17:05 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:17:09 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

/* trims newlines from map content only! */
int	trim_newlines(t_map *map)
{
	char	*tmp;
	int		i;

	i = -1;
	while (++i < map->max[Y])
	{
		tmp = ft_strtrim((const char *)map->cmap[i], "\n");
		if (!tmp)
		{
			safe_free_fd_params_cmap(map, 0);
			return (0);
		}
		safe_free(map->cmap[i]);
		map->cmap[i] = ft_strdup(tmp);
		free(tmp);
		if (!map->cmap[i])
			safe_free_fd_params_cmap(map, 0);
	}
	return (1);
}

/* Checks number of map strings,
can doublecheck max[Y] */
int	count_rows(t_map *map)
{
	int	count;

	if (!map->cmap || !map->cmap[0])
		return (0);
	count = 0;
	while (map->cmap[count])
		count++;
	if (map->max[Y] != count)
	{
		ft_putendl_fd("Wrong max[Y] calculations", 2); 
		return (0);
	}
	return (count);
}

// Map check: multiple line length, count the longest!!!
int	count_columns(t_map *map)
{
	int	max;
	int	j;
	int	i;

	if (!map->cmap || !map->cmap[0])
		return (0);
	i = -1;
	max = 0;
	while (map->cmap[++i])
	{
		j = ft_strlen(map->cmap[i]);
		if (j > max)
			max = j;
	}
	if (max < 3)
		return (0);
	map->max[X] = max;
	return (1);
}

/* Returns the null terminated (easier to free) int map */
void	cmap_to_imap(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	map->map = malloc (sizeof(int *) * (map->max[Y]));
	if (!map->map)
		systemfail(map, 0, NULL, "Malloc failed!");
	while (++i < map->max[Y])
	{
		map->map[i] = ft_calloc (map->max[X], sizeof(int));
		if (!map->map[i])
			free_all_previous(map, i);
		j = -1;
		while (++j < map->max[X] && map->cmap[i][j])
		{
			if (map->cmap[i][j] == '0')
				map->map[i][j] = 0;
			else if (map->cmap[i][j] == '1')
				map->map[i][j] = 1;
			else
				map->map[i][j] = 0;
		}
	}
}

/*
void	print_imap(t_map *map)
{
	int	y;
	int	x;

	printf("\n");
	y = -1;
	while (++y < map->max[Y])
	{
		x = -1;
		while (++x < map->max[X])
		{
			printf("%d", map->map[y][x]);
		}
		printf("\n");
	}
}

void	print_cmap(char **map)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			printf("%c", map[y][x]);
			x++;
		}
		y++;
		printf("\n");
	}
}
*/
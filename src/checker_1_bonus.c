/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:19:44 by rmocsai           #+#    #+#             */
/*   Updated: 2023/08/21 10:19:50 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (close(fd) < 0)
		return (0);
	return (1);
}

int	ends_with(char *str, char *key)
{
	int	start;
	int	i;

	start = (int)(ft_strlen(str) - ft_strlen(key));
	if (start <= 0)
		return (0);
	i = 0;
	while (start && str[start] && key[i] && (str[start] == key[i]))
	{
		start++;
		i++;
	}
	if (i == (int)ft_strlen(key))
		return (1);
	return (0);
}

static int	check_filepaths(t_map *map)
{
	if (!check_file(map->path[SOUTH]) || !check_file(map->path[WEST]) || \
	!check_file(map->path[EAST]) || !check_file(map->path[NORTH]))
		return (0);
	return (1);
}

t_map	*check_input(int argc, char **argv, t_map *map)
{
	if (argc <= 1 || argc > 2 || (argc == 2 && !ends_with(argv[1], ".cub")))
		err_before_mall("Only .cub file required as parameter");
	if (argc == 2 && !check_file(argv[1]))
		err_before_mall("Map file cannot be accessed");
	get_lines(map, argv[1]);
	if (!check_filepaths(map))
	{
		safe_free_params(map);
		err_before_mall("Tiles have to be .xpm files and accessible!");
	}
	return (map);
}

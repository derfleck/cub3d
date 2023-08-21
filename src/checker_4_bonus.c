/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_4_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmocsai <rmocsai@student.42.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:12:07 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/21 10:21:16 by rmocsai          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	get_start_position(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (map->cmap[++y])
	{
		x = -1;
		while (map->cmap[y][++x])
		{
			if (map->cmap[y][x] == 'S' || map->cmap[y][x] == 'W' || \
			map->cmap[y][x] == 'E' || map->cmap[y][x] == 'N')
				break ;
		}
		if (map->cmap[y][x] == 'S' || map->cmap[y][x] == 'W' || \
		map->cmap[y][x] == 'E' || map->cmap[y][x] == 'N')
			break ;
	}
	map->cmap[y][x] = '0';
	map->play.player[Y] = (double)y + 0.5;
	map->play.player[X] = (double)x + 0.5;
	return (1);
}

//use GNL to read first line, open close, first line has to be "/* XPM */"
static int	check_xpmcontent(char *path)
{
	int		fd;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	tmp = get_next_line(fd);
	if (!tmp)
	{
		buffer_cleaner(fd, tmp);
		return (0);
	}
	if (ft_strncmp(tmp, "/* XPM */", 9))
	{
		free(tmp);
		buffer_cleaner(fd, tmp);
		return (0);
	}
	free(tmp);
	buffer_cleaner(fd, tmp);
	return (1);
}

/* trims extra spaces from paths and checks them
	- .xpm extension
	- accessible
	- first line has to be specific  */ 
char	*fill_params(char *line, t_map *map, int fd)
{
	char	*tmp;

	tmp = NULL;
	if (line)
	{
		tmp = ft_strtrim(line + 2, " ");
		if (tmp == NULL)
			systemfail(map, fd, line, "Malloc failed!");
		safe_free(line);
	}
	else
		systemfail(map, fd, line, "System failure!");
	if (!ends_with(tmp, ".xpm"))
		systemfail(map, fd, tmp, "Texture must be .xpm file!");
	if (!check_file(tmp))
		systemfail(map, fd, tmp, "Texture file cannot be accessed!");
	if (!check_xpmcontent(tmp))
		systemfail(map, fd, tmp, "Texture file is corrupt!");
	return (tmp);
}

int	check_colorcode_proper(char *s)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(s);
	if (!s || !len || !ft_isdigit((int)s[++i]))
		return (0);
	while (s[++i])
	{
		while (s[i] && (s[i] == ' ' || ft_isdigit((int)s[i])))
			i++;
		if (s[i] == ',' && s[i + 1])
		{
			while (s[++i] && s[i] == ' ' && s[i + 1])
				continue ;
			if (s[i + 1] && (!ft_isdigit((int)s[i + 1]) && s[i] != ' '))
				return (0);
		}
	}
	if (!ft_isdigit(s[len - 1]))
		return (0);
	return (1);
}

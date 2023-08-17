#include "../inc/cub3d.h"

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

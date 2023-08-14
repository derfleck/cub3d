#include "../inc/cub3d.h"

/*  */ 
static char	*fill_params(char *line, t_map *map, int fd)
{
	char	*tmp;

	tmp = NULL;
	if (line)
	{
		tmp = ft_strtrim(line, "NOASWE \n");
		if (tmp == NULL)
			systemfail(map, fd, line, "Malloc failed!");
		safe_free(line);
	}
	else
		systemfail(map, fd, line, "System failure!");
	if (!ends_with(tmp, ".xpm"))
		systemfail(map, fd, line, "Texture must be .xpm file!");
	if (!check_file(tmp))
		systemfail(map, fd, line, "Texture file cannot be accessed!");
	return (tmp);
}

static void	check_param_lines(char *line, t_map *map, int fd)
{
	int		i;

	i = 0;
	if (line && (line[0] == '\0' || line[0] == '\n'))
		return (free(line));
	else if (!ft_strncmp("SO ", line, 3))
		map->so = fill_params(line, map, fd);
	else if (!ft_strncmp("WE ", line, 3))
		map->we = fill_params(line, map, fd);
	else if (!ft_strncmp("EA ", line, 3))
		map->ea = fill_params(line, map, fd);
	else if (!ft_strncmp("NO ", line, 3))
		map->no = fill_params(line, map, fd);
	else if (!ft_strncmp("F ", line, 2))
		map->floor = rgb_to_hex(line, map, fd);
	else if (!ft_strncmp("C ", line, 2))
		map->ceiling = rgb_to_hex(line, map, fd);
	else
	{
		//safe_free
		err_before_mall("Unknown identifier!");
	}
}

static int	get_params(int fd, t_map *map)
{
	char	*line;

	while (1)
	{
		errno = 0;
		line = get_next_line(fd);
		if (!line)
		{
			if (errno)
				systemfail(map, fd, NULL, "System failure");
			else
				break ;
		}
		check_param_lines(line, map, fd);
		if (map->so && map->we && map->ea && map->no && \
		map->ceiling && map->floor)
			break ;
	}
	return (1);
}

int	get_lines(t_map *map, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (0);
	if (!get_params(fd, map))
		return (0);
	if (map->ceiling == -1 || map->floor == -1)
	{
		safe_free_params(map);
		return (0);
	}
	line = NULL; //jump_over_newlines(fd, map);
	// save_map(fd, map, line);
	// check_map_validity(map);
	return (1);
}
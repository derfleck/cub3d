#include "../inc/cub3d.h"

/* Trims spaces and newline from identifiers */
static char	*trim_spaces(char *line, t_map *map, int fd)
{
	char	*tmp;

	tmp = NULL;
	if (line)
	{
		tmp = ft_strtrim(line, " \n");
		if (!tmp)
			systemfail(map, fd, line, "Malloc failed!");
		safe_free(line);
	}
	return (tmp);
}

static void	check_param_lines(char *line, t_map *map, int fd)
{
	int		i;

	i = 0;
	if (line && (line[0] == '\0' || line[0] == '\n'))
		return (free(line));
	else if (!ft_strncmp("SO ", line, 3))
		linecheck_helper1(map, line, fd, SOUTH);
	else if (!ft_strncmp("WE ", line, 3))
		linecheck_helper1(map, line, fd, WEST);
	else if (!ft_strncmp("EA ", line, 3))
		linecheck_helper1(map, line, fd, EAST);
	else if (!ft_strncmp("NO ", line, 3))
		linecheck_helper1(map, line, fd, NORTH);
	else if (!ft_strncmp("F ", line, 2))
		linecheck_helper2(map, line, fd, 'F');
	else if (!ft_strncmp("C ", line, 2))
		linecheck_helper2(map, line, fd, 'C');
	else
		systemfail(map, fd, line, "Unknown identifier!");
}

static void	init_dirs(t_map *map)
{
	map->path = malloc (4 * sizeof (char *));
	if (!map->path)
		err_before_mall("Malloc failed!");
	map->path[SOUTH] = NULL;
	map->path[WEST] = NULL;
	map->path[EAST] = NULL;
	map->path[NORTH] = NULL;
}

static void	get_params(int fd, t_map *map)
{
	char	*line;

	init_dirs(map);
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
		map->index++;
		line = trim_spaces(line, map, fd);
		check_param_lines(line, map, fd);
		if (map->path[SOUTH] && map->path[WEST] && map->path[EAST] && \
		map->path[NORTH] && map->ceiling && map->floor)
			break ;
	}
	if (!map->path[SOUTH] || !map->path[WEST] || !map->path[EAST] || \
	!map->path[NORTH])
		systemfail(map, fd, NULL, "File is empty!");
}

int	get_lines(t_map *map, char *file)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		err_before_mall("Opening map file failed");
	get_params(fd, map);
	if (map->ceiling == -1 || map->floor == -1)
		systemfail(map, fd, NULL, "Map format is not accepted");
	get_map(map, fd, line, file);
	safe_free_cmap(map);
	return (1);
}

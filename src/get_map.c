#include "../inc/cub3d.h"

static int	save_map(int fd, char *line, t_map *map)
{
	int	i;

	i = 0;
	map->cmap = malloc ((map->max[Y] + 1) * sizeof (char *));
	if (!map->cmap)
		systemfail(map, fd, line, "Malloc failed!");
	map->cmap[i] = ft_strdup(line);
	if (!map->cmap[i])
		systemfail(map, fd, line, "Malloc failed!");
	safe_free(line);
	while (++i < map->max[Y])
	{
		map->cmap[i] = get_next_line(fd);
		if (!map->cmap[i])
			return (0);
	}
	i--;
	if (map->cmap[i][0] == '\n' || map->cmap[i][0] == '\0')
		safe_free(map->cmap[i]);
	else
		map->cmap[i + 1] = NULL; //is this correct for null terminating?
	if (close(fd) == -1)
		safe_free_fd_params_cmap(map, 0);
	return (1);
}

static char	*return_to_mapline(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (--map->index)
	{
		safe_free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static int	get_map_dimension_y(t_map *map, int fd, char *line)
{
	int		count;

	count = 1;
	if (!line)
		return (0);
	while (line)
	{
		safe_free(line);
		line = get_next_line(fd);
		if (line && (line[0] == '\n' || line[0] == '\0'))
			break ;
		if (line)
			count++;
	}
	while (line)
	{
		safe_free(line);
		line = get_next_line(fd);
		if (line && line[0] != '\n')
			systemfail(map, fd, line, "Map content is invalid: empty line.");
	}
	if (close(fd) == -1)
		systemfail(map, fd, NULL, "Failed to close map file.");
	if (count < 3)
		systemfail(map, fd, NULL, "Map content is invalid: too small.");
	return (count);
}

static char	*jump_over_newlines(t_map *map, int fd)
{
	char	*tmp;

	errno = 0;
	tmp = get_next_line(fd);
	map->index++;
	if (tmp == NULL)
	{
		if (errno != 0)
			systemfail(map, fd, NULL, "System error!");
	}
	while (tmp && *tmp == '\n')
	{
		free(tmp);
		tmp = get_next_line(fd);
		map->index++;
	}
	if (tmp == NULL)
		systemfail(map, fd, NULL, "Map content is missing from file.");
	return (tmp);
}

int	get_map(t_map *map, int fd, char *line, char *file)
{
	int	fd2;

	line = jump_over_newlines(map, fd);
	map->max[Y] = get_map_dimension_y(map, fd, line);
	if (!map->max[Y])
		systemfail(map, fd, NULL, "Map content is missing from file.");
	fd2 = open(file, O_RDONLY);
	if (fd <= 0)
		systemfail(map, fd, NULL, "Opening map file failed");
	line = return_to_mapline(map, fd2);
	if (!save_map(fd, line, map))
		safe_free_fd_params_cmap(map, fd);
	if (!trim_newlines(map) || !check_map_validity(map))
		safe_free_fd_params_cmap(map, 0);
	return (1);
}


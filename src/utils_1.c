#include "../inc/cub3d.h"

void	close_fd(int fd, t_map *map)
{
	if (close(fd) == -1)
		systemfail(map, fd, NULL, "Failed to close map file.");
}

char	*trim_spaces(char *line, t_map *map, int fd)
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

void	linecheck_helper1(t_map *map, char *line, int fd, int dir)
{
	if (map->path[dir] != NULL && map->path[dir][0])
		systemfail(map, fd, line, "Invalid instruction count");
	map->path[dir] = fill_params(line, map, fd);
}

void	linecheck_helper2(t_map *map, char *line, int fd, char c)
{
	if (c == 'F')
	{
		if (map->floor)
			systemfail(map, fd, line, "Invalid instruction count");
		map->floor = rgb_to_hex(line, map, fd);
	}
	else if (c == 'C')
	{
		if (map->ceiling)
			systemfail(map, fd, line, "Invalid instruction count");
		map->ceiling = rgb_to_hex(line, map, fd);
	}
}

//frees int array up to a certain specified size
void	free_int_arr(int **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	if (arr)
		free(arr);
}

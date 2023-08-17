#include "../inc/cub3d.h"

void	close_fd(int fd, t_map *map)
{
	if (close(fd) == -1)
		systemfail(map, fd, NULL, "Failed to close map file.");
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
		map->floor = rgb_to_hex(line, map, fd, 'F');
	}
	else if (c == 'C')
	{
		if (map->ceiling)
			systemfail(map, fd, line, "Invalid instruction count");
		map->ceiling = rgb_to_hex(line, map, fd, 'C');
	}
}

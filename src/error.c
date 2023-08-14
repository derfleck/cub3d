#include "../inc/cub3d.h"

void	err_before_mall(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	systemfail(t_map *map, int fd, char *str, char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd(message, 2);
	}
	safe_free(str);
	if (fd > 2)
	{
		while (1)
		{
			str = get_next_line(fd);
			if (!str)
				break ;
			safe_free(str);
		}
	}
	safe_free_params(map);
	exit (1);
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void	safe_free_params(t_map *map)
{
	safe_free(map->dir[SOUTH]);
	safe_free(map->dir[WEST]);
	safe_free(map->dir[EAST]);
	safe_free(map->dir[NORTH]);
	safe_free(map->dir);
}

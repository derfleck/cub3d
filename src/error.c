#include "../inc/cub3d.h"

void	err_before_mall(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(str, 2);
	exit (1);
}

void	buffer_cleaner(int fd, char *str)
{
	if (fd > 2)
	{
		while (1)
		{
			str = get_next_line(fd);
			if (!str)
				break ;
			safe_free(str);
		}
		if (close(fd) == -1)
			ft_putendl_fd("Closing a file descriptor has failed!", 2);
	}
}

void	systemfail(t_map *map, int fd, char *str, char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd(message, 2);
	}
	safe_free(str);
	buffer_cleaner(fd, str);
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
	int	i;

	i = -1;
	while (!map->path[++i])
		safe_free(map->path[i]);
	safe_free(map->path);
}

void	safe_free_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->cmap[++i])
		safe_free(map->cmap[i]);
	safe_free(map->cmap);
}

void	safe_free_fd_params_cmap(t_map *map, int fd)
{
	char	*str;

	str = NULL;
	buffer_cleaner(fd, str);
	safe_free_params(map);
	safe_free_map(map);
	exit (1);
}

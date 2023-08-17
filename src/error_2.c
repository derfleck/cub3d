#include "../inc/cub3d.h"

void	safe_free_cmap(t_map *map)
{
	int	i;

	i = -1;
	while (map->cmap[++i])
		safe_free(map->cmap[i]);
	safe_free(map->cmap);
}

void	safe_free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->max[Y])
		safe_free(map->map[i]);
	safe_free(map->map);
}

void	safe_free_fd_params_cmap(t_map *map, int fd)
{
	char	*str;

	str = NULL;
	buffer_cleaner(fd, str);
	safe_free_params(map);
	safe_free_cmap(map);
	exit (1);
}

/* frees params, cmap and imap till i*/
void	free_all_previous(t_map *map, int i)
{
	int	j;

	safe_free_params(map);
	safe_free_cmap(map);
	j = -1;
	while (++j < i)
		safe_free(map->map[j]);
	safe_free(map->map);
	exit (1);
}

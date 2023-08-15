#include "../inc/cub3d.h"

int	trim_newlines(t_map *map)
{
	char	*tmp;
	int		i;

	i = -1;
	while (++i < map->max[Y])
	{
		tmp = ft_strtrim((const char *)map->cmap[i], "\n");
		if (!tmp)
		{
			safe_free_fd_params_cmap(map, 0);
			return (0);
		}
		safe_free(map->cmap[i]);
		map->cmap[i] = ft_strdup(tmp);
		free(tmp);
		if (!map->cmap[i])
			safe_free_fd_params_cmap(map, 0);
	}
	print_map(map->cmap);
	return (1);
}

#include "../inc/cub3d.h"

void	free_all_no_exit(t_map *map)
{
	safe_free_params(map);
	safe_free_map(map);
}

void	free_all_with_exit(t_map *map)
{
	safe_free_params(map);
	safe_free_map(map);
	exit (1);
}

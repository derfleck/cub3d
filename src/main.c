#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	static t_map	map;
	static t_player	play;

	map.play = play;
	check_input(argc, argv, &map);


	return (0);
}

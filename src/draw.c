#include "../inc/cub3d.h"

//sets camera and looking vectors based on looking direction at start
void	set_direction(t_map *map)
{
	if (map->dir == 'N' || map->dir == 'S')
	{
		map->play.plane[X] = 0.66;
		map->play.plane[Y] = 0;
		map->play.look_dir[X] = 0;
		if (map->dir == 'N')
			map->play.look_dir[Y] = -1;
		else if (map->dir == 'S')
			map->play.look_dir[Y] = 1;
	}
	else if (map->dir == 'E' || map->dir == 'W')
	{
		map->play.plane[X] = 0;
		map->play.plane[Y] = 0.66;
		map->play.look_dir[Y] = 0;
		if (map->dir == 'E')
			map->play.look_dir[X] = 1;
		else if (map->dir == 'W')
			map->play.look_dir[X] = -1;
	}
}

//draws floor and ceiling
void	draw_background(t_map *map)
{
	int	x;
	int	y;
	int	col;

	x = 0;
	y = 0;
	col = map->ceiling;
	while (y <= HEIGHT)
	{
		if (col == map->ceiling && y >= HEIGHT / 2)
			col = map->floor;
		while (x <= WIDTH)
			ft_mlx_pixel_put(map->mlx.img, x++, y, col);
		x = 0;
		y++;
	}
}

void	draw_wall(t_map *map, int x)
{
	int	wall_height;
	int	start_end[2];

	wall_height = (int)(HEIGHT / map->play.perpwalldist);
	start_end[0] = -wall_height / 2 + HEIGHT / 2;
	if (start_end[0] < 0)
		start_end[0] = 0;
	start_end[1] = wall_height / 2 + HEIGHT / 2;
	if (start_end[1] >= HEIGHT)
		start_end[1] = HEIGHT - 1;
	while (start_end[0] <= start_end[1])
	{
		if (map->play.side == 0)
			ft_mlx_pixel_put(map->mlx.img, x, start_end[0]++, YELLOW);
		else
			ft_mlx_pixel_put(map->mlx.img, x, start_end[0]++, GREEN);
	}
}

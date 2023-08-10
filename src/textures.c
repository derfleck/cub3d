#include "../inc/cub3d.h"

//loads textures from given path, malloc protected for both
//initializing pointers as well as loading xpm files
void	load_textures(t_map *map)
{
	int	i;
	int	tex;

	i = 0;
	tex = TEX;
	while (i < 4)
	{
		map->tex[i].img = mlx_xpm_file_to_image(map->mlx->mlx, map->path[i], \
		&tex, &tex);
		if (map->tex[i].img == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(map->mlx->mlx, map->tex[i].img);
			return ;
		}
		map->tex[i].addr = mlx_get_data_addr(map->tex[i].img, &map->tex[i].bpp, \
		&map->tex[i].line_len, &map->tex[i].endian);
		if (map->tex[i].addr == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(map->mlx->mlx, map->tex[i].img);
			return ;
		}
		i++;
	}
}

void	draw_wall_textured(t_map *map, int x)
{
	int			wall_height;
	int			start_end[2];
	t_player	*play;
	int			coordinates[2];
	int			color;

	wall_height = (int)(HEIGHT / map->play->perpwalldist);
	start_end[0] = -wall_height / 2 + HEIGHT / 2;
	if (start_end[0] < 0)
		start_end[0] = 0;
	start_end[1] = wall_height / 2 + HEIGHT / 2;
	if (start_end[1] >= HEIGHT)
		start_end[1] = HEIGHT - 1;

	play = map->play;
	if (play->side)
		play->wall_x = play->player[X] + play->perpwalldist * play->raydir[X];
	else
		play->wall_x = play->player[Y] + play->perpwalldist * play->raydir[Y];
	play->wall_x -= floor(play->wall_x);
	coordinates[X] = (int)(play->wall_x * (double)TEX);
	//if ((play->side == 1 && play->raydir[X] > 0) || \
	//(play->side == 0 && play->raydir[Y] < 0))
	if (!(play->side && play->raydir[Y] < 0))
		coordinates[X] = TEX - coordinates[X] - 1;
	play->tex_step = 1.0 * ((double)TEX / (double)wall_height);
	play->tex_pos = (start_end[0] - HEIGHT / 2 + \
	wall_height / 2) * play->tex_step;
	//printf("wall_x: %0.10f tex_step: %0.10f tex_pos: %0.10f ", play->wall_x, play->tex_step, play->tex_pos);
	while (start_end[0] <= start_end[1])
	{
		coordinates[Y] = (int)play->tex_pos & (TEX - 1);
		play->tex_pos += play->tex_step;
		if (!play->side && play->raydir[X] < 0)
		{
			color = get_color_value(map, coordinates[X], coordinates[Y], EAST);
			ft_mlx_pixel_put(map->mlx->img, x, start_end[0], color);
		}
		else if (!play->side && play->raydir[X] > 0)
		{
			color = get_color_value(map, coordinates[X], coordinates[Y], WEST);
			ft_mlx_pixel_put(map->mlx->img, x, start_end[0], color);
		}
		else if (play->side && play->raydir[Y] < 0)
		{
			color = get_color_value(map, coordinates[X], coordinates[Y], NORTH);
			ft_mlx_pixel_put(map->mlx->img, x, start_end[0], color);
		}
		else if (play->side && play->raydir[Y] > 0)
		{
			color = get_color_value(map, coordinates[X], coordinates[Y], SOUTH);
			ft_mlx_pixel_put(map->mlx->img, x, start_end[0], color);
		}
		//printf("%d\n", color);
		start_end[0]++;
	}
	//printf("%f\n", play->tex_pos);
}

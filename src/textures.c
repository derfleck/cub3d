/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:16:29 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/16 16:16:29 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//loads textures from given path, malloc protected
void	load_textures(t_map *map)
{
	int	i;
	int	tex;

	i = 0;
	tex = TEX;
	while (i < 4)
	{
		map->tex[i].img = mlx_xpm_file_to_image(map->mlx.mlx, map->path[i], \
		&tex, &tex);
		if (map->tex[i].img == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(map->mlx.mlx, map->tex[i].img);
			return ;
		}
		map->tex[i].addr = mlx_get_data_addr(map->tex[i].img, &map->tex[i].bpp, \
		&map->tex[i].line_len, &map->tex[i].endian);
		if (map->tex[i].addr == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(map->mlx.mlx, map->tex[i].img);
			return ;
		}
		i++;
	}
}

//helper, gets color from texture position and draws pixel on image
static void	draw_texture(t_map *map, int *screen_i, int tex)
{
	int	color;

	color = get_color_value(map, map->play.tex_i[X], map->play.tex_i[Y], tex);
	ft_mlx_pixel_put(map->mlx.img, screen_i[X], screen_i[Y], color);
}

//calculates height of wall on screen based on raycast
static void	calc_wall_height(t_player *play, int x)
{
	play->wall_height = (int)(HEIGHT / play->perpwalldist);
	play->screen_pos[X] = x;
	play->screen_pos[Y] = -play->wall_height / 2 + HEIGHT / 2;
	if (play->screen_pos[Y] < 0)
		play->screen_pos[Y] = 0;
	if (play->side)
		play->wall_x = play->player[X] + play->perpwalldist * play->raydir[X];
	else
		play->wall_x = play->player[Y] + play->perpwalldist * play->raydir[Y];
	play->wall_x -= floor(play->wall_x);
	play->tex_step = 1.0 * ((double)TEX / (double)play->wall_height);
	play->tex_i[X] = (int)(play->wall_x * (double)TEX);
	if ((play->side == 0 && play->raydir[X] < 0) || \
	(play->side == 1 && play->raydir[Y] > 0))
		play->tex_i[X] = TEX - play->tex_i[X] - 1;
	play->tex_pos = (play->screen_pos[Y] - HEIGHT / 2 + \
	play->wall_height / 2) * play->tex_step;
}

//performs calculation of position on texture to draw
//fallback to draw single colored walls if no textures loaded
void	draw_wall_textured(t_map *map, int x)
{
	int			end;
	t_player	*play;

	if (!map->tex[0].img)
		return (draw_wall(map, x));
	play = &map->play;
	calc_wall_height(play, x);
	end = play->wall_height / 2 + HEIGHT / 2;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	while (play->screen_pos[Y] <= end)
	{
		play->tex_i[Y] = (int)play->tex_pos & (TEX - 1);
		play->tex_pos += play->tex_step;
		if (!play->side && play->raydir[X] < 0)
			draw_texture(map, play->screen_pos, WEST);
		else if (!play->side && play->raydir[X] > 0)
			draw_texture(map, play->screen_pos, EAST);
		else if (play->side && play->raydir[Y] < 0)
			draw_texture(map, play->screen_pos, NORTH);
		else if (play->side && play->raydir[Y] > 0)
			draw_texture(map, play->screen_pos, SOUTH);
		play->screen_pos[Y]++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:17:10 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:14:41 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

//draws cube in the size of len on pos[X/Y]
static void	draw_cube(t_img *img, int *pos, int len)
{
	int	x;
	int	y;

	y = 0;
	while (y < len)
	{
		x = 0;
		while (x < len)
		{
			ft_mlx_pixel_put(img, (pos[X] * len) + x, (pos[Y] * len) + y, RED);
			x++;
		}
		y++;
	}
}

//checks dimensions of map and creates indexes for minimap
static void	get_minimap(t_map *map)
{
	int	start[2];

	start[X] = (int)round(map->play.player[X] - ((double)map->mini_max[X] / 2));
	if (map->max[X] == map->mini_max[X])
		start[X] = 0;
	start[Y] = (int)round(map->play.player[Y] - ((double)map->mini_max[Y] / 2));
	if (map->max[Y] == map->mini_max[Y])
		start[Y] = 0;
	if (start[X] < 0)
		map->mini_start[X] = 0;
	else
		map->mini_start[X] = start[X];
	if (start[Y] < 0)
		map->mini_start[Y] = 0;
	else
		map->mini_start[Y] = start[Y];
	map->mini_end[X] = map->mini_start[X] + map->mini_max[X];
	if (map->mini_end[X] > map->max[X])
		map->mini_end[X] = map->max[X];
	map->mini_end[Y] = map->mini_start[Y] + map->mini_max[Y];
	if (map->mini_end[Y] > map->max[Y])
		map->mini_end[Y] = map->max[Y];
}

//takes current dimensions of map, sets minimap dimensions
//values are capped at 30 for x and 15 for y axis
static void	set_dimensions(t_map *map)
{
	if (map->max[X] > 30)
		map->mini_max[X] = 30;
	else
		map->mini_max[X] = map->max[X];
	if (map->max[Y] > 24)
		map->mini_max[Y] = 24;
	else
		map->mini_max[Y] = map->max[Y];
}

static void	draw_player(t_map *map)
{
	int		pos[2];

	pos[X] = (int)(GRID * (map->play.player[X] - map->mini_start[X]));
	pos[Y] = (int)(GRID * (map->play.player[Y] - map->mini_start[Y]));
	mini_raycast(map, pos);
	ft_mlx_pixel_put(map->mlx.img, pos[X], pos[Y], BLACK);
}

//minimap only draws a 30 x 20 item snapshot of the map
//this ensures that also huge maps can be loaded and the
//viewspace is never blocked by the minimap (max 240 x 160 px)
//checks if map array exists or has size
void	draw_minimap(t_map *map)
{
	int	pos[2];
	int	**mini;
	int	draw[2];

	if (!map->map || map->max[X] == 0 || map->max[Y] == 0)
		return ;
	mini = map->map;
	set_dimensions(map);
	get_minimap(map);
	draw_player(map);
	pos[Y] = map->mini_start[Y];
	while (pos[Y] < map->mini_end[Y])
	{
		pos[X] = map->mini_start[X];
		while (pos[X] < map->mini_end[X])
		{
			draw[X] = pos[X] - map->mini_start[X];
			draw[Y] = pos[Y] - map->mini_start[Y];
			if (mini && mini[pos[Y]][pos[X]] > 0)
				draw_cube(map->mlx.img, draw, GRID);
			pos[X]++;
		}
		pos[Y]++;
	}
}

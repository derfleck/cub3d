/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:16:22 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:17:34 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

//checks the direction and size of X/Y steps for DDA
static void	calc_steps(t_player	*ptr)
{
	double	diff[2];

	diff[X] = ptr->player[X] - (int)ptr->player[X];
	diff[Y] = ptr->player[Y] - (int)ptr->player[Y];
	if (ptr->raydir[X] < 0)
	{
		ptr->step[X] = -1;
		ptr->sidedist[X] = diff[X] * ptr->deltadist[X];
	}
	else
	{
		ptr->step[X] = 1;
		ptr->sidedist[X] = (1 - diff[X]) * ptr->deltadist[X];
	}
	if (ptr->raydir[Y] < 0)
	{
		ptr->step[Y] = -1;
		ptr->sidedist[Y] = diff[Y] * ptr->deltadist[Y];
	}
	else
	{
		ptr->step[Y] = 1;
		ptr->sidedist[Y] = (1 - diff[Y]) * ptr->deltadist[Y];
	}
}

//helper, calculates perpendicular distance from player plane
static void	calc_perpwalldist(t_player *ptr)
{
	if (ptr->side)
		ptr->perpwalldist = ptr->sidedist[Y] - ptr->deltadist[Y];
	else
		ptr->perpwalldist = ptr->sidedist[X] - ptr->deltadist[X];
	if (ptr->perpwalldist <= 0)
		ptr->perpwalldist = DBL_MIN;
}

//performs the DDA algorithm to find the next wall hit by ray
static void	check_hit(t_player *ptr)
{
	int	hit;
	int	map[2];

	hit = 0;
	map[X] = (int)ptr->player[X];
	map[Y] = (int)ptr->player[Y];
	while (hit == 0)
	{
		if (ptr->sidedist[X] < ptr->sidedist[Y])
		{
			ptr->sidedist[X] += ptr->deltadist[X];
			map[X] += ptr->step[X];
			ptr->side = 0;
		}
		else
		{
			ptr->sidedist[Y] += ptr->deltadist[Y];
			map[Y] += ptr->step[Y];
			ptr->side = 1;
		}
		if (map[Y] < 0 || map[X] < 0 || \
		ptr->map->map[map[Y]][map[X]] == 1)
			hit = 1;
	}
	calc_perpwalldist(ptr);
}

//raycasting using vectors, when direction is 0, delta is set to double max
void	raycast(t_map *map)
{
	int			x;
	t_player	*ptr;

	ptr = &map->play;
	x = 0;
	while (x < WIDTH)
	{
		ptr->camera_x = 2 * x / (double)WIDTH - 1;
		ptr->raydir[X] = ptr->look_dir[X] + (ptr->plane[X] * ptr->camera_x);
		ptr->raydir[Y] = ptr->look_dir[Y] + (ptr->plane[Y] * ptr->camera_x);
		if (ptr->raydir[X] == 0)
			ptr->deltadist[X] = DBL_MAX;
		else
			ptr->deltadist[X] = fabs(1.0 / ptr->raydir[X]);
		if (ptr->raydir[Y] == 0)
			ptr->deltadist[Y] = DBL_MAX;
		else
			ptr->deltadist[Y] = fabs(1.0 / ptr->raydir[Y]);
		calc_steps(ptr);
		check_hit(ptr);
		draw_wall_textured(map, x);
		x++;
	}
}

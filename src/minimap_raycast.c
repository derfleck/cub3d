/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:16:11 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/17 18:26:45 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	mini_check_hit(t_ray *ptr)
{
	int	hit;

	hit = 0;
	ptr->mini_map[X] = (int)ptr->player[X];
	ptr->mini_map[Y] = (int)ptr->player[Y];
	while (hit == 0)
	{
		if (ptr->sidedist[X] < ptr->sidedist[Y])
		{
			ptr->sidedist[X] += ptr->deltadist[X];
			ptr->mini_map[X] += ptr->step[X];
			ptr->side = 0;
		}
		else
		{
			ptr->sidedist[Y] += ptr->deltadist[Y];
			ptr->mini_map[Y] += ptr->step[Y];
			ptr->side = 1;
		}
		if (ptr->mini_map[Y] < 0 || ptr->mini_map[X] < 0 || \
		ptr->map[ptr->mini_map[Y]][ptr->mini_map[X]] == 1)
			hit = 1;
	}
}

static void	mini_calc_steps(t_ray	*ptr)
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

static void	mini_set(t_ray *ray, t_player *play, int x)
{
	ray->camera_x = 2 * x / (double)8 - 1;
	ray->raydir[X] = play->look_dir[X] + play->plane[X] * ray->camera_x;
	ray->raydir[Y] = play->look_dir[Y] + play->plane[Y] * ray->camera_x;
	if (ray->raydir[X] == 0)
		ray->deltadist[X] = DBL_MAX;
	else
		ray->deltadist[X] = fabs(1.0 / ray->raydir[X]);
	if (ray->raydir[Y] == 0)
		ray->deltadist[Y] = DBL_MAX;
	else
		ray->deltadist[Y] = fabs(1.0 / ray->raydir[Y]);
}

void	mini_raycast(t_map *map, int *pos)
{
	t_ray		ray;
	t_player	*play;
	int			x;
	int			end[2];

	x = 0;
	play = &map->play;
	ray.player[X] = play->player[X];
	ray.player[Y] = play->player[Y];
	ray.map = map->map;
	while (x < 8)
	{
		mini_set(&ray, play, x);
		mini_calc_steps(&ray);
		mini_check_hit(&ray);
		end[X] = (int)(GRID * (ray.mini_map[X] - map->mini_start[X]));
		end[Y] = (int)(GRID * (ray.mini_map[Y] - map->mini_start[Y]));
		ft_mlx_line(map->mlx.img, pos, end, GREEN);
		x++;
	}
}

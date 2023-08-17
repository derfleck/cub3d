/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:16:51 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/16 16:16:54 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_line	set_values(int *start, int *end)
{
	t_line	tmp;

	tmp.dx = abs(end[X] - start[X]);
	tmp.dy = abs(end[Y] - start[Y]);
	if (start[X] < end[X])
		tmp.sx = 1;
	else
		tmp.sx = -1;
	if (start[Y] < end[Y])
		tmp.sy = 1;
	else
		tmp.sy = -1;
	tmp.err = tmp.dx - tmp.dy;
	return (tmp);
}

//simple implementation of bresenham algorithm to quickly draw a line
void	ft_mlx_line(t_img *img, int *start, int *end, int color)
{
	t_line	tmp;
	int		e2;
	int		x0;
	int		y0;

	x0 = start[X];
	y0 = start[Y];
	tmp = set_values(start, end);
	while (x0 != end[X] || y0 != end[Y])
	{
		ft_mlx_pixel_put(img, x0, y0, color);
		e2 = 2 * tmp.err;
		if (e2 > -tmp.dy)
		{
			tmp.err -= tmp.dy;
			x0 += tmp.sx;
		}
		if (e2 < tmp.dx)
		{
			tmp.err += tmp.dx;
			y0 += tmp.sy;
		}
	}
}

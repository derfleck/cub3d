/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:17:04 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:12:23 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

//writes pixel on image
//requires img struct, coordinates and color code
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

//converts degrees to radian
double	deg_to_rad(double deg)
{
	return (deg * M_PI / (double) 180.0);
}

//helper for 2D matrix multiplication
void	mat_mul(double *val, t_mat mat)
{
	double	tmp[2];

	tmp[X] = val[X] * mat.c1r1 + val[Y] * mat.c2r1;
	tmp[Y] = val[X] * mat.c1r2 + val[Y] * mat.c2r2;
	val[X] = tmp[X];
	val[Y] = tmp[Y];
}

int	get_color_value(t_map *map, int x, int y, int i)
{
	return (*(int *)(map->tex[i].addr
		+ (y * map->tex[i].line_len + x * (map->tex[i].bpp / 8))));
}

//creates image struct
t_img	*create_img(int x, int y, void *mlx)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx, x, y);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
	&img->line_len, &img->endian);
	return (img);
}

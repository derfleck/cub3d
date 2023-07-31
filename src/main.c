/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:46:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/07/31 19:16:58 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//requires img struct, coordinates and color code
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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
			ft_mlx_pixel_put(map->mlx_ptr->img, x++, y, col);
		x = 0;
		y++;
	}
}

/*
//supposed to draw square for minimap
//TODO: check coordinate system
void	square(int x, int y, int len, t_map *map)
{
	int	x1;
	int	y1;

	y1 = y + len;
	while (y < y1)
	{
		x1 = x;
		while (x1 < x + len)
			ft_mlx_pixel_put(map->mlx_ptr->img, x1++, y, map->mini_col);
		y++;
	}
}

//executed when hook is not called
int	loop_draw(t_map *map)
{
	t_mlx	*mlx;

	mlx = map->mlx_ptr;
	draw_background(map);
	draw_map(map, mlx->img);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	return (0);
}
*/

void	create_window(t_map	*map)
{
	map->mlx_ptr = malloc(sizeof(t_mlx));
	if (!map->mlx_ptr)
		return ;
	map->mlx_ptr->mlx = mlx_init();
	map->mlx_ptr->win = mlx_new_window(map->mlx_ptr->mlx, WIDTH, HEIGHT, "cub3d");
	map->mlx_ptr->img = create_img(WIDTH, HEIGHT, map->mlx_ptr->mlx);
	map->ceiling = GREEN;
	map->floor = RED;
	draw_background(map);
	mlx_put_image_to_window(map->mlx_ptr->mlx, map->mlx_ptr->win, map->mlx_ptr->img->img, 0, 0);
	mlx_loop(map->mlx_ptr->mlx);
	//mlx_loop_hook(map->mlx_ptr, loop_draw, map);
}

/*
t_map	*create_map(void)
{
	int	dummy[8][8] = {{0, 0, 1, 1, 1, 0, 0, 1},
						{1, 1, 0, 0, 0, 1, 1, 1},
						{1, 0, 0, 0, 0, 0, 1, 0},
						{1, 0, 1, 0, 0, 1, 1, 1},
						{1, 1, 0, 0, 0, 0, 1, 0},
						{0, 1, 0, 0, 0, 0, 1, 1},
						{1, 1, 0, 0, 0, 0, 1, 0},
						{1, 1, 1, 1, 1, 1, 1, 1}};
	t_map	*map;
	map = malloc(sizeof(t_map));
	map->x_max = sizeof(dummy[0]) / sizeof(int);
	map->y_max = sizeof(dummy) / (sizeof(int) * map->x_max);
	
}
*/

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	static t_map	map;

	create_window(&map);
}

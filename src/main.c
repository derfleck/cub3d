/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:46:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/07 17:11:17 by mleitner         ###   ########.fr       */
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

//draw single line for wall in raycaster
void	draw_straight(t_map *map, int x, int y, int len)
{
	int	y1;

	y1 = y + len;
	while (y < y1)
		ft_mlx_pixel_put(map->mlx->img, x, y++, RED);
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
			ft_mlx_pixel_put(map->mlx->img, x++, y, col);
		x = 0;
		y++;
	}
}

/*
//supposed to draw square for minimap
//always use top left position to start (e.g. 0/0)
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
	map->mlx = malloc(sizeof(t_mlx));
	if (!map->mlx)
		return ;
	map->mlx->mlx = mlx_init();
	map->mlx->win = mlx_new_window(map->mlx->mlx, WIDTH, HEIGHT, "cub3d");
	map->mlx->img = create_img(WIDTH, HEIGHT, map->mlx->mlx);
	draw_background(map);
	draw_minimap(map);
	mlx_put_image_to_window(map->mlx->mlx, map->mlx->win, map->mlx->img->img, 0, 0);
	mlx_loop(map->mlx->mlx);
	//mlx_loop_hook(map->mlx_ptr, loop_draw, map);
}


int	main(int argc, char **argv)
{
	static t_map	map;
	int				i;
	int				j;

	i = 0;
	map.map = get_int_array(8, 8);
	int map_data[8][8] = {{0, 0, 1, 1, 1, 0, 0, 1},
	{1, 1, 0, 0, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0},
	{1, 0, 1, 0, 0, 1, 1, 1},
	{1, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 1},
	{1, 1, 0, 0, 2, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1, 1}};
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			map.map[i][j] = map_data[i][j];
			j++;
		}
		i++;
	}
	map.ceiling = BLUE;
	map.floor = BLACK;
	map.max[X] = 8;
	map.max[Y] = 8;
	map.player[X] = 4;
	map.player[Y] = 6;

	(void)argc;
	(void)argv;

	create_window(&map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:46:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/17 13:13:44 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//frees int array up to a certain specified size
void	free_int_arr(int **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	if (arr)
		free(arr);
}

//mallocs int** array, has enough protection
int	**get_int_array(int x, int y)
{
	int	j;
	int	**arr;

	j = 0;
	arr = malloc(sizeof(int *) * y);
	if (!arr)
		return (NULL);
	while (j < y)
	{
		arr[j] = ft_calloc(x, sizeof(int));
		if (!arr[j])
			return (free_int_arr(arr, j), NULL);
		j++;
	}
	return (arr);
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

static void	movement(t_map *map)
{
	if (map->play.walk == 1)
		walk(map, NORTH);
	else if (map->play.walk == 2)
		walk(map, SOUTH);
	if (map->play.strafe == 1)
		strafe(map, WEST);
	else if (map->play.strafe == 2)
		strafe(map, EAST);
	if (map->play.rotate == 1)
		rotate(map, deg_to_rad(map->rot_speed));
	else if (map->play.rotate == 2)
		rotate(map, deg_to_rad(-map->rot_speed));
}

static int	loop_draw(t_map *map)
{
	t_mlx	*ptr;

	ptr = &map->mlx;
	calc_speed(&map->play);
	movement(map);
	draw_background(map);
	raycast(map);
	draw_minimap(map);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->img, 0, 0);
	return (0);
}

static void	create_window(t_map	*map)
{
	map->mlx.mlx = mlx_init();
	if (!map->mlx.mlx)
		return ;
	map->mlx.win = mlx_new_window(map->mlx.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!map->mlx.win)
		return ;
	map->mlx.img = create_img(WIDTH, HEIGHT, map->mlx.mlx);
	if (!map->mlx.img)
		return ;
	load_textures(map);
	mlx_loop_hook(map->mlx.mlx, loop_draw, map);
	set_hooks(map);
	mlx_loop(map->mlx.mlx);
	mlx_do_sync(map->mlx.mlx);
}


int	main(int argc, char **argv)
{
	static t_map	map;

	map.play.map = &map;
	check_input(argc, argv, &map);
	set_direction(&map);
	create_window(&map);
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:46:36 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:14:35 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static void	movement(t_map *map)
{
	if (map->play.walk == 1)
		walk(map, NORTH);
	else if (map->play.walk == 2)
		walk(map, SOUTH);
	if (map->play.strafe == 1)
		strafe(map, WEST);
	if (map->play.strafe == 2)
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
		return (perror("Error initializing display\n"), free_and_exit(map, 1));
	map->mlx.win = mlx_new_window(map->mlx.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!map->mlx.win)
		return (perror("Error initializing window\n"), free_and_exit(map, 1));
	map->mlx.img = create_img(WIDTH, HEIGHT, map->mlx.mlx);
	if (!map->mlx.img)
		return (perror("Error initializing image\n"), free_and_exit(map, 1));
	load_textures(map);
	mlx_loop_hook(map->mlx.mlx, loop_draw, map);
	set_hooks(map);
	mlx_loop(map->mlx.mlx);
	mlx_do_sync(map->mlx.mlx);
}

void	free_and_exit(t_map *map, int code)
{
	int	i;

	i = 0;
	if (map->mlx.img)
	{
		mlx_destroy_image(map->mlx.mlx, map->mlx.img->img);
		free(map->mlx.img);
	}
	if (map->mlx.win)
		mlx_destroy_window(map->mlx.mlx, map->mlx.win);
	while (i < 4 && &map->tex[i] && map->tex[i].img)
		mlx_destroy_image(map->mlx.mlx, map->tex[i++].img);
	if (map->mlx.mlx)
	{
		mlx_destroy_display(map->mlx.mlx);
		free(map->mlx.mlx);
	}
	i = 0;
	while (i < 4 && map->path[i])
		free(map->path[i++]);
	if (map->path)
		free(map->path);
	if (map->map)
		free_int_arr(map->map, map->max[Y]);
	exit(code);
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

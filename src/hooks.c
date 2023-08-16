/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:16:34 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/16 18:43:38 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//resets values to 0 after key release
static int	check_keyrelease(int keycode, t_map *map)
{
	if (keycode == XK_W || keycode == XK_w)
		map->play.walk = 0;
	else if (keycode == XK_S || keycode == XK_s)
		map->play.walk = 0;
	else if (keycode == XK_A || keycode == XK_a)
		map->play.strafe = 0;
	else if (keycode == XK_D || keycode == XK_d)
		map->play.strafe = 0;
	else if (keycode == XK_Left || keycode == XK_KP_Left)
		map->play.rotate = 0;
	else if (keycode == XK_Right || keycode == XK_KP_Right)
		map->play.rotate = 0;
	return (0);
}

//helper to check which button has been pressed
static int	check_keypress(int keycode, t_map *map)
{
	if (keycode == XK_W || keycode == XK_w)
		map->play.walk = 1;
	else if (keycode == XK_S || keycode == XK_s)
		map->play.walk = 2;
	else if (keycode == XK_A || keycode == XK_a)
		map->play.strafe = 1;
	else if (keycode == XK_D || keycode == XK_d)
		map->play.strafe = 2;
	else if (keycode == XK_Left || keycode == XK_KP_Left)
		map->play.rotate = 1;
	else if (keycode == XK_Right || keycode == XK_KP_Right)
		map->play.rotate = 2;
	return (0);
}

//rotates player when mouse is moved to either end of the window
//mouse will always be moved to the middle of the screen to keep it hidden
static int	mouse_rotate(int x, int y, t_map *map)
{
	(void)y;
	if (x > (WIDTH / 1.5))
	{
		rotate(map, deg_to_rad(-map->rot_speed) * 4);
		mlx_mouse_move(map->mlx.mlx, map->mlx.win, HEIGHT / 2, WIDTH / 2);
	}
	else if (x < (WIDTH / 4))
	{
		rotate(map, deg_to_rad(map->rot_speed) * 4);
		mlx_mouse_move(map->mlx.mlx, map->mlx.win, HEIGHT / 2, WIDTH / 2);
	}
	return (0);
}

static int	close_cubed(t_map *map)
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
	while (i < 4)
		free(map->path[i++]);
	if (map->path)
		free(map->path);
	if (map->map)
		free_int_arr(map->map, map->max[Y]);
	exit(0);
}

void	set_hooks(t_map *map)
{
	mlx_hook(map->mlx.win, 2, 1L << 0, check_keypress, map);
	mlx_hook(map->mlx.win, 3, 1L << 1, check_keyrelease, map);
	mlx_hook(map->mlx.win, 6, 1L << 6, mouse_rotate, map);
	mlx_hook(map->mlx.win, 33, 1L << 17, close_cubed, map);
	//mlx_mouse_hide(map->mlx.mlx, map->mlx.win);
	mlx_mouse_move(map->mlx.mlx, map->mlx.win, HEIGHT / 2, WIDTH / 2);
}

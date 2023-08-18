/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:16:34 by mleitner          #+#    #+#             */
/*   Updated: 2023/08/18 12:03:54 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

static int	close_cubed(t_map *map)
{
	free_and_exit(map, 0);
	return (0);
}

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
	else if (keycode == XK_Escape)
		close_cubed(map);
	return (0);
}

void	set_hooks(t_map *map)
{
	mlx_hook(map->mlx.win, 2, 1L << 0, check_keypress, map);
	mlx_hook(map->mlx.win, 3, 1L << 1, check_keyrelease, map);
	mlx_hook(map->mlx.win, 33, 1L << 17, close_cubed, map);
	mlx_mouse_move(map->mlx.mlx, map->mlx.win, HEIGHT / 2, WIDTH / 2);
}

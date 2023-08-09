#include "../inc/cub3d.h"

//calculates the time that has elapsed since the last call
clock_t	calc_speed(t_player *play)
{
	clock_t	diff;

	if (play->prev_time == 0)
		play->prev_time = clock();
	diff = (clock() - play->prev_time) / CLOCKS_PER_SEC;
	play->prev_time = clock();
	return (diff);
}

void	walk(t_map *map, int dir)
{
	t_player	*play;
	double		speed[2];
	int			next[2];

	play = map->play;
	speed[X] = map->walk_speed * play->look_dir[X];
	speed[Y] = map->walk_speed * play->look_dir[Y];
	if (dir == SOUTH)
	{
		speed[X] = -speed[X];
		speed[Y] = -speed[Y];
	}
	next[X] = (int)(play->player[X] + speed[X]);
	next[Y] = (int)(play->player[Y] + speed[Y]);
	if (map->map[next[Y]][next[X]] == 0)
	{
		play->player[X] += speed[X];
		play->player[Y] += speed[Y];
	}
}

//function for moving sideways
void	strafe(t_map *map, int dir)
{
	t_player	*play;
	double		speed[2];
	int			next[2];
	double		look_side[2];
	double		ang;

	play = map->play;
	if (dir == WEST)
		ang = deg_to_rad(-90);
	else
		ang = deg_to_rad(90);
	look_side[X] = play->look_dir[X] * cos(ang) - play->look_dir[Y] * sin(ang);
	look_side[Y] = play->look_dir[X] * sin(ang) + play->look_dir[Y] * cos(ang);
	speed[X] = map->walk_speed * look_side[X];
	speed[Y] = map->walk_speed * look_side[Y];
	next[X] = (int)(play->player[X] + speed[X]);
	next[Y] = (int)(play->player[Y] + speed[Y]);
	if (map->map[next[Y]][next[X]] != 1)
	{
		play->player[X] += speed[X];
		play->player[Y] += speed[Y];
	}
}

//performing matrix multiplication using a transformation matrix
//to rotate the users viewing direction (on both looking_dir and
//camera plane vector)
void	rotate(t_map *map, double ang)
{
	t_mat	rot_mat;

	rot_mat = (t_mat){cos(ang), -sin(ang), sin(ang), cos(ang)};
	mat_mul(&map->play->look_dir[0], rot_mat);
	mat_mul(&map->play->plane[0], rot_mat);
}


int		check_button(int keycode, t_map *map)
{
	//printf("%i\n", keycode);
	printf("_________________________________________________\n");
	printf("before: look_dir: %f %f, camera: %f %f, player: %f %f\n", map->play->look_dir[X], map->play->look_dir[Y], map->play->plane[X], map->play->plane[Y], map->play->player[X], map->play->player[Y]);
	
	if (keycode == XK_W || keycode == XK_w)
	{
		printf("Forward pressed\n");
		walk(map, NORTH);
	}
	else if (keycode == XK_S || keycode == XK_s)
	{
		printf("Back pressed\n");
		walk(map, SOUTH);
	}
	else if (keycode == XK_A || keycode == XK_a)
	{
		printf("Left pressed\n");
		strafe(map, WEST);
	}
	else if (keycode == XK_D || keycode == XK_d)
	{
		printf("Right pressed\n");
		strafe(map, EAST);
	}
	else if (keycode == XK_Left)
	{
		printf("Turn left\n");
		rotate(map, deg_to_rad(5));
	}
	else if (keycode == XK_Right)
	{
		printf("Turn right\n");
		rotate(map, deg_to_rad(-5));
	}
	printf("raydir: %f %f camerax: %f\n", map->play->raydir[X], map->play->raydir[Y], map->play->camera_x);
	printf("deltadist: %f %f sidedist: %f %f perpwalldist: %f step: %d %d\n", map->play->deltadist[X], map->play->deltadist[Y], map->play->sidedist[X], map->play->sidedist[Y], map->play->perpwalldist, map->play->step[X], map->play->step[Y]);
	printf("current position: %f %f\n", map->play->player[X], map->play->player[Y]);
	printf("after: look_dir: %f %f, camera: %f %f, player: %f %f\n", map->play->look_dir[X], map->play->look_dir[Y], map->play->plane[X], map->play->plane[Y], map->play->player[X], map->play->player[Y]);
	return (0);
}

int		close_cubed(t_map *map)
{
	(void)map;
	exit(0);
}

void	set_hooks(t_map *map)
{
	mlx_hook(map->mlx->win, 2, 1L << 0, check_button, map);
	mlx_hook(map->mlx->win, 33, 1L << 17, close_cubed, map);
}

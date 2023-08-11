#include "../inc/cub3d.h"

//calculates the time that has elapsed since the last call
//adapts the walking and rotation speed to the fps
//also displays fps in terminal and caps frame rate, if set
void	calc_speed(t_player *play)
{
	double	diff;
	double	target_frame_time;
	double	time_elapsed;
	clock_t	start_time;

	target_frame_time = 1.0 / TARGET_FPS;
	if (play->prev_time == 0)
		play->prev_time = clock();
	diff = (double)(clock() - play->prev_time) / CLOCKS_PER_SEC;
	play->prev_time = clock();
	if (TARGET_FPS && diff < target_frame_time)
	{
		start_time = clock();
		time_elapsed = target_frame_time - diff;
		while ((double)(clock() - start_time) / CLOCKS_PER_SEC < time_elapsed)
			;
		diff = target_frame_time;
	}
	play->map->walk_speed = diff * 20;
	play->map->rot_speed = diff * 300;
	if (PRINT_FPS)
		printf("%d fps\r", (int)(1 / diff));
}

//function called when W or S are pressed, moves player forward/backward
void	walk(t_map *map, int dir)
{
	t_player	*play;
	double		speed[2];
	int			next[2];

	play = &map->play;
	speed[X] = map->walk_speed * play->look_dir[X];
	speed[Y] = map->walk_speed * play->look_dir[Y];
	if (dir == SOUTH)
	{
		speed[X] = -speed[X];
		speed[Y] = -speed[Y];
	}
	next[X] = (int)(play->player[X] + speed[X]);
	next[Y] = (int)(play->player[Y] + speed[Y]);
	if (next[X] < map->max[X] && next[Y] < map->max[Y] && \
	map->map[next[Y]][next[X]] == 0)
	{
		play->player[X] += speed[X];
		play->player[Y] += speed[Y];
	}
}

//function called when A or D are pressed, for moving sideways (strafing)
void	strafe(t_map *map, int dir)
{
	t_player	*play;
	double		speed[2];
	int			next[2];
	double		look_side[2];
	double		ang;

	play = &map->play;
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
	if (next[X] < map->max[X] && next[Y] < map->max[Y] && \
	map->map[next[Y]][next[X]] == 0)
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
	mat_mul(&map->play.look_dir[0], rot_mat);
	mat_mul(&map->play.plane[0], rot_mat);
}

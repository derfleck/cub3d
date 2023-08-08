#include "../inc/cub3d.h"

/*
#define WIDTH 8
#define HEIGHT 8
#define X 0
#define Y 1
#include <math.h>
#include <stdio.h>

int map[WIDTH][HEIGHT] = {
{1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,1,1},
{1,0,0,0,0,0,0,1},
{1,1,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,1,0,1,1},
{1,1,1,1,1,1,1,1}
};
*/

//sets camera and looking vectors based on looking direction at start
void	set_direction(t_map *map)
{
	if (map->dir == 'N' || map->dir == 'S')
	{
		map->play->plane[X] = 0.66;
		map->play->plane[Y] = 0;
		map->play->look_dir[X] = 0;
		if (map->dir == 'N')
			map->play->look_dir[Y] = -1;
		else if (map->dir == 'S')
			map->play->look_dir[Y] = 1;
	}
	else if (map->dir == 'E' || map->dir == 'W')
	{
		map->play->plane[X] = 0;
		map->play->plane[Y] = 0.66;
		map->play->look_dir[Y] = 0;
		if (map->dir == 'E')
			map->play->look_dir[X] = 1;
		else if (map->dir == 'W')
			map->play->look_dir[X] = -1;
	}
}

//checks the direction and size of X/Y steps for DDA
void	calc_steps(t_player	*ptr)
{
	double	diff[2];

	diff[X] = ptr->player[X] - (int)ptr->player[X];
	diff[Y] = ptr->player[Y] - (int)ptr->player[Y];
	if (ptr->raydir[X] < 0)
	{
		ptr->step[X] = -1;
		ptr->sidedist[X] = diff[X] * ptr->deltadist[X];
	}
	else
	{
		ptr->step[X] = 1;
		ptr->sidedist[X] = diff[X] - 1;
	}
	if (ptr->raydir[Y] < 0)
	{
		ptr->step[Y] = -1;
		ptr->sidedist[Y] = diff[Y] * ptr->deltadist[Y];
	}
	else
	{
		ptr->step[Y] = 1;
		ptr->sidedist[Y] = diff[Y] - 1;
	}
}

void	calc_perpwalldist(t_player *ptr, int side)
{
	if (side)
		ptr->perpwalldist = ptr->sidedist[Y] - ptr->deltadist[Y];
	else
		ptr->perpwalldist = ptr->sidedist[X] - ptr->deltadist[X];
}

//performs the DDA algorithm to find the next wall hit by ray
void	check_hit(t_player *ptr)
{
	int	hit;
	int	side;
	int	map[2];

	hit = 0;
	map[X] = (int)ptr->player[X];
	map[Y] = (int)ptr->player[Y];
	while (!hit)
	{
		if (ptr->sidedist[X] < ptr->sidedist[Y])
		{
			ptr->sidedist[X] += ptr->deltadist[X];
			map[X] += ptr->step[X];
			side = 0;
		}
		else
		{
			ptr->sidedist[Y] += ptr->deltadist[Y];
			map[Y] += ptr->step[Y];
			side = 1;
		}
		if (ptr->map->map[map[Y]][map[X]] == 1)
			hit = 1;
	}
	calc_perpwalldist(ptr, side);
}

void	raycast(t_map *map)
{
	int			x;
	t_player	*ptr;

	ptr = map->play;
	while (x < WIDTH)
	{
		ptr->camera_x = ((2.0 * x) / (double) WIDTH) - 1.0;
		ptr->raydir[X] = ptr->look_dir[X] + (ptr->plane[X] * ptr->camera_x);
		ptr->raydir[Y] = ptr->look_dir[Y] + (ptr->plane[Y] * ptr->camera_x);
		if (ptr->raydir[X] == 0)
			ptr->deltadist[X] = 1e30;
		else
			ptr->deltadist[X] = fabs(1.0 / ptr->raydir[X]);
		if (ptr->raydir[Y] == 0)
			ptr->deltadist[Y] = 1e30;
		else
			ptr->deltadist[Y] = fabs(1.0 / ptr->raydir[Y]);
		calc_steps(ptr);
		check_hit(ptr);
		x++;
	}
}

/*
int main(void)
{
	double player[2] = {4.0,1.5};
	double direction[2] = {0,1};
	double plane[2] = {0.66,0};
	int x = 0;
	int rays = 10;

	double sideDistX;
	double sideDistY;
	double perpWallDist;
	
	printf("starting: x %f y %f\n", player[X], player[Y]);
	printf("looking: x %f y %f\n", direction[X], direction[Y]);
	
	while (x < rays)
	{
		double cameraX = ((2.0 * x)/(double)rays) - 1.0;
		double rayDirX = direction[X] + (plane[X] * cameraX);
		double rayDirY = direction[Y] + (plane[Y] * cameraX);
		int mapX = (int)player[X];
		int mapY = (int)player[Y];

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

		int stepX;
		int stepY;

		int side = 0;
		int hit = 0;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player[X] - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player[X]) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player[Y] - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player[Y]) * deltaDistY;
		}
		printf("rayDirX: %f, rayDirY: %f\n", rayDirX, rayDirY);
		printf("stepX: %i, stepY: %i, sideDistX: %f, sideDistY: %f\n", stepX, stepY, sideDistX, sideDistY);
		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			printf("step: map[%i][%i]\n", mapX, mapY);
			if (map[mapY][mapX] == 1)
				hit = 1;
		}
		printf("Ray %i: Wall hit on %i/%i\n", x, mapX, mapY);
		if (side)
			perpWallDist = sideDistY - deltaDistY;
		else
			perpWallDist = sideDistX - deltaDistX;
		printf("PerpWallDist: %f\n", perpWallDist);
		x++;
	}
	return (0);
}
*/

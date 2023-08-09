#include "../inc/cub3d.h"

//checks the direction and size of X/Y steps for DDA
static void	calc_steps(t_player	*ptr)
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
		ptr->sidedist[X] = (1 - diff[X]) * ptr->deltadist[X];
	}
	if (ptr->raydir[Y] < 0)
	{
		ptr->step[Y] = -1;
		ptr->sidedist[Y] = diff[Y] * ptr->deltadist[Y];
	}
	else
	{
		ptr->step[Y] = 1;
		ptr->sidedist[Y] = (1 - diff[Y]) * ptr->deltadist[Y];
	}
}

static void	calc_perpwalldist(t_player *ptr)
{
	if (ptr->side)
		ptr->perpwalldist = ptr->sidedist[Y] - ptr->deltadist[Y];
	else
		ptr->perpwalldist = ptr->sidedist[X] - ptr->deltadist[X];
	if (ptr->perpwalldist <= 0)
		ptr->perpwalldist = DBL_MIN;
}

//performs the DDA algorithm to find the next wall hit by ray
static void	check_hit(t_player *ptr)
{
	int	hit;
	int	map[2];

	hit = 0;
	map[X] = (int)ptr->player[X];
	map[Y] = (int)ptr->player[Y];
	while (hit == 0)
	{
		if (ptr->sidedist[X] < ptr->sidedist[Y])
		{
			ptr->sidedist[X] += ptr->deltadist[X];
			map[X] += ptr->step[X];
			ptr->side = 0;
		}
		else
		{
			ptr->sidedist[Y] += ptr->deltadist[Y];
			map[Y] += ptr->step[Y];
			ptr->side = 1;
		}
		if (ptr->map->map[map[Y]][map[X]] == 1)
			hit = 1;
	}
	calc_perpwalldist(ptr);
}

//raycasting using vectors, when direction is 0, delta is set to double max
void	raycast(t_map *map)
{
	int			x;
	t_player	*ptr;

	ptr = map->play;
	x = 0;
	while (x < WIDTH)
	{
		ptr->camera_x = 2 * x / (double)WIDTH - 1;
		ptr->raydir[X] = ptr->look_dir[X] + (ptr->plane[X] * ptr->camera_x);
		ptr->raydir[Y] = ptr->look_dir[Y] + (ptr->plane[Y] * ptr->camera_x);
		if (ptr->raydir[X] == 0)
			ptr->deltadist[X] = DBL_MAX;
		else
			ptr->deltadist[X] = fabs(1.0 / ptr->raydir[X]);
		if (ptr->raydir[Y] == 0)
			ptr->deltadist[Y] = DBL_MAX;
		else
			ptr->deltadist[Y] = fabs(1.0 / ptr->raydir[Y]);
		calc_steps(ptr);
		check_hit(ptr);
		draw_wall(map, x);
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

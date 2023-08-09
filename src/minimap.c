#include "../inc/cub3d.h"

//draws cube in the size of len on pos[X/Y]
//void	draw_cube(t_img *img, int pos_x, int pos_y, int len)
void	draw_cube(t_img *img, int *pos, int len)
{
	int	x;
	int	y;

	y = 0;
	while (y < len)
	{
		x = 0;
		while (x < len)
		{
			ft_mlx_pixel_put(img, (pos[X] * len) + x, (pos[Y] * len) + y, RED);
			x++;
		}
		y++;
	}
}

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

//should only be called if map is larger than 30 items
static int	**get_minimap(t_map *map)
{
	int	start[2];
	int	**mini;
	int	x;
	int	y;

	start[X] = (int)map->play->player[X] - (map->max[X] / 2);
	start[Y] = (int)map->play->player[Y] - (map->max[Y] / 2);
	y = 0;
	mini = get_int_array(map->mini_max[X], map->mini_max[Y]);
	if (start[X] < 0)
		start[X] = 0;
	if (start[Y] < 0)
		start[Y] = 0;
	while (mini != NULL && y < map->mini_max[Y])
	{
		x = 0;
		while (x < map->mini_max[X])
		{
			mini[y][x] = map->map[start[Y] + y][start[X] + x];
			x++;
		}
		y++;
	}
	return (mini);
}

//takes current dimensions of map, sets minimap dimensions
//values are capped at 30 in both directions
static void	set_dimensions(t_map *map)
{
	if (map->max[X] > 30)
		map->mini_max[X] = 30;
	else
		map->mini_max[X] = map->max[X];
	if (map->max[Y] > 30)
		map->mini_max[Y] = 30;
	else
		map->mini_max[Y] = map->max[Y];
}

void	draw_player(t_map *map)
{
	int	pos[2];

	pos[X] = (int)(GRID * map->play->player[X]);
	pos[Y] = (int)(GRID * map->play->player[Y]);
	ft_mlx_pixel_put(map->mlx->img, pos[X], pos[Y], GREEN);
}

//minimap only draws a 30 x 30 item snapshot of the map
//this ensures that also huge maps can be loaded and the
//viewspace is never blocked by the minimap (max 240 x 240 px)
//should be well enough protected, doesn't draw when malloc fails
//TODO: could be improved by removing the need to malloc altogether
//malloc uses a lot of CPU cycles per call, so maybe rework to
//using only indexes at a later time
void	draw_minimap(t_map *map)
{
	int	pos[2];
	int	**mini;

	set_dimensions(map);
	if (map->max[X] <= 30 && map->max[Y] <= 30)
		mini = map->map;
	else
		mini = get_minimap(map);
	if (mini == NULL)
		return ;
	pos[Y] = 0;
	while (pos[Y] < map->mini_max[Y])
	{
		pos[X] = 0;
		while (pos[X] < map->mini_max[X])
		{
			if (mini && mini[pos[Y]][pos[X]] > 0)
				draw_cube(map->mlx->img, pos, GRID);
			pos[X]++;
		}
		pos[Y]++;
	}
	if (mini != map->map)
		free_int_arr(mini, map->mini_max[Y]);
	draw_player(map);
}

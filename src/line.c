#include "../inc/cub3d.h"

//check slope of line
static int	slope_chk(int v1, int v2)
{
	if (v1 < v2)
		return (1);
	else
		return (-1);
}

//check direction of line
static int	dir_chk(float_t dx, float_t dy)
{
	if (dx > dy)
		return (dx / 2);
	else
		return (-dy / 2);
}

//TODO: Check if function can be simplified (no struct)
static t_line	*set_line(t_pt beg, t_pt end)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->x0 = beg.x;
	line->x1 = end.x;
	line->y0 = beg.y;
	line->y1 = end.y;
	line->dx = abs((int)end.x - (int)beg.x);
	line->dy = abs((int)end.y - (int)beg.y);
	line->sx = slope_chk(beg.x, end.x);
	line->sy = slope_chk(beg.y, end.y);
	line->err = dir_chk(line->dx, line->dy);
	return (line);
}

//draws line from one point to another (Bresenham)
void	line(t_pt beg, t_pt end, t_img *img, t_map *map)
{
	int		e2;
	t_line	*l;

	l = set_line(beg, end);
	while (1)
	{
		ft_mlx_pixel_put(img, l->x0 + map->off_x, \
		l->y0 + map->off_y, map->pt_col);
		if (l->x0 == l->x1 && l->y0 == l->y1)
			break ;
		e2 = l->err;
		if (e2 > -(l->dx))
		{
			l->err -= l->dy;
			l->x0 += l->sx;
		}
		if (e2 < l->dy)
		{
			l->err += l->dx;
			l->y0 += l->sy;
		}
	}
	free(l);
}

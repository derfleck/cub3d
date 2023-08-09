#include "../inc/cub3d.h"

//writes pixel on image
//requires img struct, coordinates and color code
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

//converts degrees to radian
double	deg_to_rad(double deg)
{
	return (deg * M_PI / (double) 180.0);
}

//helper for 2D matrix multiplication
void	mat_mul(double *val, t_mat mat)
{
	double	tmp[2];

	tmp[X] = val[X] * mat.c1r1 + val[Y] * mat.c2r1;
	tmp[Y] = val[X] * mat.c1r2 + val[Y] * mat.c2r2;
	val[X] = tmp[X];
	val[Y] = tmp[Y];
}

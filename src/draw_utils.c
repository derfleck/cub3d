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
float_t	deg_to_rad(float_t deg)
{
	return (deg * (float_t) M_PI / (float_t) 180.0);
}

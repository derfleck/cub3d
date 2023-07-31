/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleitner <mleitner@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:38:57 by mleitner          #+#    #+#             */
/*   Updated: 2023/07/31 18:51:37 by mleitner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <errno.h>
# define WIDTH 800
# define HEIGHT 600
# define GRID 10
# define BLACK 0x00000000
# define BLUE  0x000000FF
# define GREEN 0x0000FF00
# define RED 0x00FF0000
# define YELLOW 0x00FFFF00
# define WHITE 0x00FFFFFF
# define BUFFER_SIZE 1000

//structure for coordinates, using 2D single linked list
typedef struct s_pt {
	float_t		x;
	float_t		y;
	struct s_pt	*right;
	struct s_pt	*up;
}	t_pt;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_mlx;

typedef struct s_map {
	int		x_max;
	int		y_max;
	char	*str;
	t_mlx	*mlx_ptr;
	int		floor;
	int		ceiling;
	int		mini_col;
}	t_map;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	double	prev_time;
}	t_player;

//struct for line points
typedef struct s_line {
	int	x0;
	int	x1;
	int	y0;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif